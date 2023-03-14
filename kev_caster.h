#include <stddef.h>

typedef struct {
	unsigned texture_id;
	float x_scale;
	float y_scale;
	float offset;
} kev_caster_material;


typedef struct {
	size_t x_size;
	size_t y_size;
	kev_caster_material *data;
} kev_caster_grid;

typedef struct {
	float x_counter;
	float y_counter;
	float m;
	float c;
} kev_caster_ray;

float get_incidence(float x1, float y1, float x2, float y2, kev_caster_grid grid, kev_caster_material *mat);


#define kev_caster_x_running_front(grid, x, y) grid.data[y * (grid.x_size * 4) + (x * 4)]
#define kev_caster_x_running_back(grid, x, y) grid.data[y * (grid.x_size * 4) + (x * 4) + 1]
#define kev_caster_y_running_front(grid, x, y) grid.data[y * (grid.x_size * 4) + (x * 4) + 2]
#define kev_caster_y_running_back(grid, x, y) grid.data[y * (grid.x_size * 4) + (x * 4) + 3]