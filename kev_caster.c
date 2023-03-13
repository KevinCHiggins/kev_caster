#include <math.h>
#include <stdio.h>
#include "kev_caster.h"


float calc_m(float x1, float y1, float x2, float y2)
{
	return (y1 - y2) / (x1 - x2);
}

float calc_c(float x1, float y1, float m)
{
	return y1 - (m * x1);
}

float calc_tendency(float a1, float a2)
{
	if (a2 - a1 > 0)
	{
		return 1;		
	}
	else if (a2 - a1 == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

float round_against_tendency(float a, int tendency)
{
	if (tendency > 0)
	{
		return floorf(a);
	}
	else if (tendency == 0)
	{
		return a;
	}
	else if (tendency < 0)
	{
		return ceilf(a);
	}
	return 0;
}

int get_corner_incidence(int x_tendency, int y_tendency, float x, float y, kev_caster_grid grid, kev_caster_material *mat)
{
	if (x_tendency == 1 && y_tendency == 1)
	{

		kev_caster_edge e = kev_caster_point_at(grid, (int)x, (int)(y - 1)).y_running;
		printf("Testing y-running wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), e.vis);
		if (e.vis) { *mat = e.front; return 1; }
		e = kev_caster_point_at(grid, (int)x, (int)y).x_running;
		printf("Testing x-running wall vis at %d, %d... %d\n", (int)x, (int)y, e.vis);
		if (e.vis) { *mat = e.front; return 1; }
	}
	else if (x_tendency == 1 && y_tendency == -1)
	{

		kev_caster_edge e = kev_caster_point_at(grid, (int)(x - 1), (int)y).x_running;
		printf("Testing x-running wall vis at %d, %d... %d\n", (int)(x - 1), (int)y, e.vis);
		if (e.vis) { *mat = e.back ; return 1; }
		e = kev_caster_point_at(grid, (int)x, (int)(y - 1)).y_running;
		printf("Testing y-running wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), e.vis);
		if (e.vis) { *mat = e.front ; return 1; }
	}
	else if (x_tendency == -1 && y_tendency == 1)
	{

		kev_caster_edge e = kev_caster_point_at(grid, (int)(x), (int)y).x_running;
		printf("Testing x-running wall vis at %d, %d... %d\n", (int)x, (int)y, e.vis);
		if (e.vis) { *mat = e.front ; return 1; }
		e= kev_caster_point_at(grid, (int)x, (int)(y - 1)).y_running;
		printf("Testing y-running wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), e.vis);
		if (e.vis) { *mat = e.back ; return 1; }
	}
	else
	{
		kev_caster_edge e = kev_caster_point_at(grid, (int)(x), (int)y).y_running;
		printf("Testing x-running wall vis at %d, %d... %d\n", (int)x, (int)y, e.vis);
		if (e.vis) { *mat = e.back ; return 1; }
		e = kev_caster_point_at(grid, (int)(x - 1), (int)y).x_running;
		printf("Testing y-running wall vis at %d, %d... %d\n", (int)x, (int)y, e.vis);
		if (e.vis) { *mat = e.back ; return 1; }
	}
	return 0;
}

float get_incidence(float x1, float y1, float x2, float y2, kev_caster_grid grid, kev_caster_material *mat)
{
	float m = calc_m(x1, y1, x2, y2);
	printf("m = (%f - %f) / (%f - %f) = %f\n", y1, y2, x1, x2, m);
	float c = calc_c(x1, y1, m);
	printf("c = %f - (%f * %f) =  %f\n", x1, y1, m, c);
	int x_tendency = calc_tendency(x1, x2);
	printf("x tendency = %d\n", x_tendency);
	int y_tendency = calc_tendency(y1, y2);
	printf("y tendency = %d\n", y_tendency);
	float x_counter = round_against_tendency(x1, x_tendency);
	float y_counter = round_against_tendency(y1, y_tendency);
	printf("Counters start at %f, %f\n", x_counter, y_counter);
	int moving_zonal = 1;
	while (1)
	{
		if (moving_zonal)
		{
			x_counter += x_tendency;
			float y_at_crossing = m * x_counter + c;
			float y_delta = fabsf(y_counter - y_at_crossing);
			printf("y_delta = abs(%f - (%f * %f + %f) = %f\n", y_counter, m, x_counter, c, y_delta);
			if (y_delta < 1) 
			{
				kev_caster_edge e = kev_caster_point_at(grid, (int)x_counter, (int)y_at_crossing).y_running;
				printf("Testing y-running wall vis at %d, %d... %d\n", (int)x_counter, (int)y_at_crossing, e.vis);
				if (e.vis)
				{
					float offset = fmod(y_at_crossing, 1.0);
					*mat = e.back;
					if (x_tendency == 1)
					{
						offset = 1 - offset;
						*mat = e.front;
					}
					printf("Y remainder: %f\n", fmod(y_at_crossing, 1.0));
					printf("Offset: %f\n", offset);
					return offset;	
				}

			}
			else if (y_delta == 1)
			{
				if (get_corner_incidence(x_tendency, y_tendency, x_counter, y_at_crossing, grid, mat))
				{
					printf("Offset: 0.0\n");
					return 0.0;
				}
			}
			else
			{
				x_counter -= x_tendency;
				moving_zonal = 0;
			}
		}
		else
		{
			y_counter += y_tendency;
			float x_at_crossing = ((y_counter - c) / m);
			float x_delta = fabsf(x_counter - x_at_crossing);
			printf("x_delta = abs(%f - ((%f - %f) / %f) = %f\n", x_counter, y_counter, c, m, x_delta);
			if (x_delta < 1) 
			{
				kev_caster_edge e = kev_caster_point_at(grid, (int)x_at_crossing, (int)y_counter).x_running;
				printf("Testing x-running wall vis at %d, %d... %d\n", (int)x_at_crossing, (int)y_counter, e.vis);
				if (e.vis)
				{
					float offset = fmod(x_at_crossing, 1.0);
					*mat = e.front;
					if (y_tendency == -1)
					{
						offset = 1 - offset;
						*mat = e.back;
					}
					printf("X remainder: %f\n", fmod(x_at_crossing, 1.0));
					printf("Offset: %f\n", offset);
					return offset;	
				}
			}
			else if (x_delta == 1)
			{
				if (get_corner_incidence(x_tendency, y_tendency, x_at_crossing, y_counter, grid, mat))
				{
					printf("Offset: 0.0\n");
					return 0.0;
				}
			}
			else
			{
				y_counter -= y_tendency;
				moving_zonal = 1;
			}
		}
	};
}