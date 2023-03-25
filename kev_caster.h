#include <stddef.h>

typedef struct {
	unsigned texture_id;
	float x_scale;
	float y_scale;
	float offset;
} kev_caster_material;


typedef struct {
	int x_size;
	int y_size;
	kev_caster_material *data;
} kev_caster_grid;

typedef struct {
	float x_counter;
	float y_counter;
	float m;
	float c;
} kev_caster_ray;

typedef struct {
	kev_caster_material mat;
	float offset;
	float dist;
} kev_caster_incidence;

typedef struct {
	float x1;
	float y1;
	float x2;
	float y2;
} kev_caster_line_segment;

typedef struct {
	int *x_counter;
	int *y_counter;
	float m;
	float c;
	int face_to_check;
    int grid_point_y_offset;
} kev_caster_ray_state;

kev_caster_incidence get_incidence(kev_caster_line_segment seg, kev_caster_grid *grid);
kev_caster_line_segment flip(kev_caster_line_segment seg);
int rotate_to_ne_quadrant(kev_caster_line_segment *seg);

#define kev_caster_get_face_index(grid_ptr, x, y, face) (y) * ((grid_ptr)->x_size * 4) + ((x) * 4) + face
#define kev_caster_get_face(grid_ptr, x, y, face) (grid_ptr)->data[y * ((grid_ptr)->x_size * 4) + (x * 4) + face]