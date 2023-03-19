#include <math.h>
#include <stdio.h>
#include <float.h>
#include "kev_caster.h"


float calc_m(kev_caster_line_segment *seg)
{
	return (seg->y1 - seg->y2) / (seg->x1 - seg->x2);
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

int flip_if_slope_exceeds_one(kev_caster_line_segment *seg)
{
	if (calc_m(seg) > 1)
	{
		float temp;
		temp = seg->x1;
		seg->x1 = seg->y1;
		seg->y1 = temp;
		temp = seg->x2;
		seg->x2 = seg->y2;
		seg->y2 = temp;
		return 1;
	}
	return 0;

}
int rotate_to_ne_quadrant(kev_caster_line_segment *seg)
{
	int rotations = 0;
	if (!((seg->x2 > seg->x1) && (seg->y2 > seg->y1)))
	{
		float temp;
		temp = seg->x1;
		seg->x1 = 0 - seg->y1;
		seg->y1 = temp;
		temp = seg->x2;
		seg->x2 = 0 - seg->y2;
		seg->y2 = temp;
		rotations++;
	}
	return rotations;
}

kev_caster_incidence get_incidence(kev_caster_line_segment *seg, kev_caster_grid *grid)
{
	return (kev_caster_incidence){(kev_caster_material){0, 0.0, 0.0, 0.0}, 0.0, 0.0};
}