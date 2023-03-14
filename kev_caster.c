#include <math.h>
#include <stdio.h>
#include <float.h>
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

float get_corner_incidence(int x_tendency, int y_tendency, float x, float y, kev_caster_grid grid, kev_caster_material *mat)
{
	if (x_tendency == 1 && y_tendency == 1)
	{

		*mat = kev_caster_y_running_front(grid, (int)x, (int)(y - 1));
		printf("Testing y-running front wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), mat->texture_id);
		if (mat->texture_id) return 1;
		*mat = kev_caster_x_running_front(grid, (int)x, (int)y);
		printf("Testing x-running front wall vis at %d, %d... %d\n", (int)x, (int)y, mat->texture_id);
		if (mat->texture_id) return 1;
	}
	else if (x_tendency == 1 && y_tendency == -1)
	{
		*mat = kev_caster_x_running_back(grid, (int)(x - 1), (int)(y));
		printf("Testing x-running back wall vis at %d, %d... %d\n", (int)(x - 1), (int)y, mat->texture_id);
		if (mat->texture_id) return 1;
		*mat = kev_caster_y_running_front(grid, (int)x, (int)(y - 1));
		printf("Testing y-running front wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), mat->texture_id);
		if (mat->texture_id) return 1;
	}
	else if (x_tendency == -1 && y_tendency == 1)
	{

		*mat = kev_caster_x_running_front(grid, (int)(x), (int)y);
		printf("Testing x-running front wall vis at %d, %d... %d\n", (int)x, (int)y, mat->texture_id);
		if (mat->texture_id) return 1;
		*mat = kev_caster_y_running_back(grid, (int)x, (int)(y - 1));
		printf("Testing y-running back wall vis at %d, %d... %d\n", (int)x, (int)(y - 1), mat->texture_id);
		if (mat->texture_id) return 1;
	}
	else
	{
		*mat = kev_caster_y_running_back(grid, (int)(x), (int)y);
		printf("Testing y-running back wall vis at %d, %d... %d\n", (int)x, (int)y, mat->texture_id);
		if (mat->texture_id) return 1;
		*mat = kev_caster_x_running_back(grid, (int)(x - 1), (int)y);
		printf("Testing x-running back wall vis at %d, %d... %d\n", (int)x, (int)y, mat->texture_id);
		if (mat->texture_id) return 1;
	}
	return 0;
}

float get_incidence(float x1, float y1, float x2, float y2, kev_caster_grid grid, kev_caster_material *mat)
{
	kev_caster_ray ray;
	if (y1 - y2 == 0) y1 += 0.00001;
	if (x1 - x2 == 0) x1 += 0.00001;

	ray.m = calc_m(x1, y1, x2, y2);

	printf("m = (%f - %f) / (%f - %f) = %f\n", y1, y2, x1, x2, ray.m);
	ray.c = calc_c(x1, y1, ray.m);
	printf("c = %f - (%f * %f) =  %f\n", x1, y1, ray.m, ray.c);
	int x_tendency = calc_tendency(x1, x2);
	printf("x tendency = %d\n", x_tendency);
	int y_tendency = calc_tendency(y1, y2);
	printf("y tendency = %d\n", y_tendency);
	ray.x_counter = round_against_tendency(x1, x_tendency);
	ray.y_counter = round_against_tendency(y1, y_tendency);
	printf("Counters start at %f, %f\n", ray.x_counter, ray.y_counter);
	int moving_zonal = 1;
	while (1)
	{
		if (moving_zonal)
		{
			ray.x_counter += x_tendency;
			float y_at_crossing = ray.m * ray.x_counter + ray.c;
			float y_delta = fabsf(ray.y_counter - y_at_crossing);
			printf("y_delta = abs(%f - (%f * %f + %f) = %f\n", ray.y_counter, ray.m, ray.x_counter, ray.c, y_delta);
			if (y_delta < 1) 
			{
				if (x_tendency == -1)
				{
					*mat = kev_caster_y_running_back(grid, (int)ray.x_counter, (int)y_at_crossing);
					printf("Testing y-running back wall vis at %d, %d... %d\n", (int)ray.x_counter, (int)y_at_crossing, mat->texture_id);
					if (mat->texture_id) return fmod(y_at_crossing, 1.0);
				}
				else
				{
					*mat = kev_caster_y_running_front(grid, (int)ray.x_counter, (int)y_at_crossing);
					printf("Testing y-running front wall vis at %d, %d... %d\n", (int)ray.x_counter, (int)y_at_crossing, mat->texture_id);
					if (mat->texture_id)	return 1 - fmod(y_at_crossing, 1.0);
				}
			}
			else if (y_delta == 1)
			{
				if (get_corner_incidence(x_tendency, y_tendency, ray.x_counter, y_at_crossing, grid, mat))
				{
					return 0.0;
				}
			}
			else
			{
				ray.x_counter -= x_tendency;
				moving_zonal = 0;
			}
		}
		else
		{
			ray.y_counter += y_tendency;
			float x_at_crossing = ((ray.y_counter - ray.c) / ray.m);
			float x_delta = fabsf(ray.x_counter - x_at_crossing);
			printf("x_delta = abs(%f - ((%f - %f) / %f) = %f\n", ray.x_counter, ray.y_counter, ray.c, ray.m, x_delta);
			if (x_delta < 1) 
			{
				
				if (y_tendency == 1)
				{
					*mat = kev_caster_x_running_front(grid, (int)x_at_crossing, (int)ray.y_counter);
					printf("Testing x-running front wall vis at %d, %d... %d\n", (int)x_at_crossing, (int)ray.y_counter, mat->texture_id);
					if (mat->texture_id) return fmod(x_at_crossing, 1.0);
				}
				else
				{
					*mat = kev_caster_x_running_back(grid, (int)x_at_crossing, (int)ray.y_counter);
					printf("Testing x-running back wall vis at %d, %d... %d\n", (int)x_at_crossing, (int)ray.y_counter, mat->texture_id);
					if (mat->texture_id) return 1 - fmod(x_at_crossing, 1.0);
				}
			}
			else if (x_delta == 1)
			{
				if (get_corner_incidence(x_tendency, y_tendency, x_at_crossing, ray.y_counter, grid, mat))
				{
					return 0.0;
				}
			}
			else
			{
				ray.y_counter -= y_tendency;
				moving_zonal = 1;
			}
		}
	};
}