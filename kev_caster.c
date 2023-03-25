#include <math.h>
#include <stdio.h>
#include <float.h>
#include "kev_caster.h"


float calc_m(kev_caster_line_segment seg)
{
	return (seg.y1 - seg.y2) / (seg.x1 - seg.x2);
}

float calc_c(kev_caster_line_segment seg, float m)
{
	return seg.y1 - (m * seg.x1);
}

kev_caster_line_segment flip(kev_caster_line_segment seg)
{
	return (kev_caster_line_segment){seg.y1, seg.x1, seg.y2, seg.x2};
}

int rotate_to_ne_quadrant(kev_caster_line_segment *seg)
{
	int rotations = 0;
	while ((seg->x2 < seg->x1 || seg->y2 < seg->y1))
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

kev_caster_incidence get_incidence(kev_caster_line_segment seg, kev_caster_grid *grid)
{
	// rotate ray into the next clockwise quadrant till it has positive x
	// and positive or zero y movement
	int quarter_turns_amount = rotate_to_ne_quadrant(&seg);

	// the algorithm inverts x and y whenever a ray is going to hit
	// a whole value of y before it would hit a whole value of x
	// so we precalculate everything twice, once with our rotated
	// line segment, once with this rotated line segment "flipped"
	// (i.e. mirrored in a line going from 0, 0 to 1, 1)
	kev_caster_line_segment flipped_seg = flip(seg);
	kev_caster_ray_state ray[2];
	int x_counter = (int)(floorf(seg.x1));
	int y_counter = (int)(floorf(seg.y1));
	ray[0].x_counter = &x_counter; // pointers so flipped struct
	ray[0].y_counter = &y_counter; // can refer to the same pair of values
	ray[0].m = calc_m(seg);
	ray[0].c = calc_c(seg, ray[0].m);
	ray[0].face_to_check = 3;
	ray[0].grid_point_y_offset = 1;

	ray[1].x_counter = &y_counter; // order inverted from non-flipped struct
	ray[1].y_counter = &x_counter;
	ray[1].m = calc_m(flipped_seg);
	ray[1].c = calc_c(flipped_seg, ray[1].m);
	ray[1].face_to_check = 0;
	ray[1].grid_point_y_offset = 0;

	int is_flipped = 0;

	printf("Starting x_counter %d y_counter %d\n", x_counter, y_counter);

	// used for direct hits on a corner (where both x and y are whole numbers)
	int corner_checked = 0;

	while (1)
	{
		(*ray[is_flipped].x_counter)++;

		float y_at_crossing = ray[is_flipped].m * (*ray[is_flipped].x_counter) + ray[is_flipped].c;
		float x_displacement;
		float y_displacement;
		if (!is_flipped)
		{
			x_displacement = fabs((*ray[is_flipped].x_counter) - seg.x1);
			y_displacement = fabs(y_at_crossing - seg.y1);
		}
		else
		{
			x_displacement = fabs((*ray[is_flipped].x_counter) - seg.y1);
			y_displacement = fabs(y_at_crossing - seg.x1);
		}
		float y_delta = y_at_crossing - (*ray[is_flipped].y_counter);
		printf("Y delta %f, y_at crossing %f, x_counter %d, y_counter %d\n", y_delta, y_at_crossing, (*ray[is_flipped].x_counter), (*ray[is_flipped].y_counter));
		if (y_delta <= 1.0)
		{
			printf("Turns %d, Is flipped %d, x_counter %d y _counter %d\n", quarter_turns_amount, is_flipped, (*ray[is_flipped].x_counter), (*ray[is_flipped].y_counter));
			printf("Orig x_counter %d, y_counter %d\n", x_counter, y_counter);
			int trunc_x; 
			int trunc_y;	

			printf("Rotated & flipped x counter %d, y_counter %d, y offset %d, face to check %d\n",  (*ray[is_flipped].x_counter), (*ray[is_flipped].y_counter), ray[is_flipped].grid_point_y_offset, ray[is_flipped].face_to_check);
			printf("truncx %d, trunc_y %d, orig y_counter before offset added %d\n", trunc_x, trunc_y, (*ray[0].y_counter));
			printf("offset %d\n", ray[is_flipped].grid_point_y_offset);
			(*ray[is_flipped].y_counter) += (ray[is_flipped].grid_point_y_offset);
			trunc_x = (*ray[0].x_counter);
			trunc_y = (*ray[0].y_counter);
			printf("truncx %d, trunc_y %d, orig y_counter wth offset added %d\n", trunc_x, trunc_y, (*ray[0].y_counter));
			(*ray[is_flipped].y_counter) -= (ray[is_flipped].grid_point_y_offset);

			int turns = quarter_turns_amount;
			int face = (3 - quarter_turns_amount + is_flipped) % 4;

			printf("Rotated unflipped offset accounted for trunc_x %d, trunc_y %d, y offset &d, face offset %d\n", trunc_x, trunc_y, ray[is_flipped].grid_point_y_offset, face);

			while (turns)
			{
				int temp;
				temp = trunc_x;
				trunc_x = trunc_y;
				trunc_y = 0 - temp;
				turns--;
				printf("Unrotating trunc_x %d, trunc_y %d, y offset %d, face offset %d\n", trunc_x, trunc_y, ray[is_flipped].grid_point_y_offset, face);

			}
			printf("Unrotated trunc_x %d, trunc_y %d, y offset %d, face offset %d\n", trunc_x, trunc_y, ray[is_flipped].grid_point_y_offset, face);


			int i = kev_caster_get_face_index(grid, trunc_x, trunc_y, face);
			printf("Final index %d, trunc_x %d, y with offset %d, face offset %d\n", i, trunc_x, trunc_y, face);


			kev_caster_material mat = grid->data[i];
			if (mat.texture_id > 0)
			{
				printf("OFfset calc... face %d, y_delta %f\n", face, y_delta);
				if (!is_flipped)
				{
					y_delta = 1 - y_delta;
				}
				return (kev_caster_incidence){mat, y_delta, sqrt(x_displacement * x_displacement + y_displacement * y_displacement)};
			}
		}
		else
		{
			(*ray[is_flipped].x_counter)--;

			if (is_flipped) is_flipped = 0; else is_flipped = 1;
		}
		if (y_delta == 1.0) // direct hit on a corner (integral x and y)
		{
			if (corner_checked)
			{
				corner_checked = 0;
			}
			else
			{
				corner_checked++;
				(*ray[is_flipped].x_counter)--;
				if (is_flipped) is_flipped = 0; else is_flipped = 1;
			}
		}

	};
}