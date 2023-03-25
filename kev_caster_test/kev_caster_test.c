#include "kev_caster.h"
#include "kev_test.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>

kev_caster_grid grid;
kev_caster_material grid_data[36];

void create_grid();
void test_grid_creation();
void test_intersections();
void test_persistence();
void test_intersections_new();
void test_rotations();
void test_flipping();
void test_pos_x_pos_y_hit_y_running_immediately();
void test_pos_x_neg_y_hit_y_running_immediately();
void test_pos_x_pos_y_hit_x_running_immediately();
void test_pos_x_neg_y_hit_x_running_immediately();
void test_neg_x_pos_y_hit_y_running_immediately();
void test_neg_x_neg_y_hit_y_running_immediately();
void test_neg_x_pos_y_hit_x_running_immediately();
void test_neg_x_neg_y_hit_x_running_immediately();

void test_pos_x_pos_y_hit_y_running_after();
void test_pos_x_neg_y_hit_y_running_after();
void test_pos_x_pos_y_hit_x_running_after();
void test_pos_x_neg_y_hit_x_running_after();
void test_neg_x_pos_y_hit_y_running_after();
void test_neg_x_neg_y_hit_y_running_after();
void test_neg_x_pos_y_hit_x_running_after();
void test_neg_x_neg_y_hit_x_running_after();

void test_pos_x_pos_y_hit_y_running_after_diag();
void test_pos_x_neg_y_hit_y_running_after_diag();
void test_pos_x_pos_y_hit_x_running_after_diag();
void test_pos_x_neg_y_hit_x_running_after_diag();
void test_neg_x_pos_y_hit_y_running_after_diag();
void test_neg_x_neg_y_hit_y_running_after_diag();
void test_neg_x_pos_y_hit_x_running_after_diag();
void test_neg_x_neg_y_hit_x_running_after_diag();

void test_pos_x_pos_y_hit_corner_immediately();
void test_pos_x_neg_y_hit_corner_immediately();
void test_neg_x_pos_y_hit_corner_immediately();
void test_neg_x_neg_y_hit_corner_immediately();

void test_pos_x_pos_y_hit_corner_thru_corner();
void test_pos_x_neg_y_hit_corner_thru_corner();
void test_neg_x_pos_y_hit_corner_thru_corner();
void test_neg_x_neg_y_hit_corner_thru_corner();
void test_pos_x();
void test_neg_x();
void test_pos_y();
void test_neg_y();

int main(int argc, char **argv)
{

    create_grid();
    kev_test_run("Basic 3x3 grid sealed box", test_grid_creation);
    kev_test_run("Persistence of grid struct", test_persistence);
    kev_test_run("Rotations", test_rotations);
    kev_test_run("Flipping", test_flipping);

    kev_test_run("pos x, pos y hit y-running immediately", test_pos_x_pos_y_hit_y_running_immediately);
    kev_test_run("pos x, neg y hit y-running immediately", test_pos_x_neg_y_hit_y_running_immediately);

    kev_test_run("pos x, pos y hit x-running immediately", test_pos_x_pos_y_hit_x_running_immediately);

    kev_test_run("pos x, neg y hit x-running immediately", test_pos_x_neg_y_hit_x_running_immediately);

    kev_test_run("neg x, pos y hit y-running immediately", test_neg_x_pos_y_hit_y_running_immediately);
    kev_test_run("neg x, neg y hit y-running immediately", test_neg_x_neg_y_hit_y_running_immediately);
    kev_test_run("neg x, pos y hit x-running immediately", test_neg_x_pos_y_hit_x_running_immediately);
    kev_test_run("neg x, neg y hit x-running immediately", test_neg_x_neg_y_hit_x_running_immediately);



    kev_test_run("pos x, pos y hit y-running after", test_pos_x_pos_y_hit_y_running_after);
    kev_test_run("pos x, neg y hit y-running after", test_pos_x_neg_y_hit_y_running_after);
    kev_test_run("pos x, pos y hit x-running after", test_pos_x_pos_y_hit_x_running_after);
    kev_test_run("pos x, neg y hit x-running after", test_pos_x_neg_y_hit_x_running_after);
    kev_test_run("neg x, pos y hit y-running after", test_neg_x_pos_y_hit_y_running_after);
    kev_test_run("neg x, neg y hit y-running after", test_neg_x_neg_y_hit_y_running_after);
    kev_test_run("neg x, pos y hit x-running after", test_neg_x_pos_y_hit_x_running_after);
    kev_test_run("neg x, neg y hit x-running after", test_neg_x_neg_y_hit_x_running_after);

    kev_test_run("pos x, pos y hit y-running after diag", test_pos_x_pos_y_hit_y_running_after_diag);
    kev_test_run("pos x, neg y hit y-running after diag", test_pos_x_neg_y_hit_y_running_after_diag);
    kev_test_run("pos x, pos y hit x-running after diag", test_pos_x_pos_y_hit_x_running_after_diag);
    kev_test_run("pos x, neg y hit x-running after diag", test_pos_x_neg_y_hit_x_running_after_diag);
    kev_test_run("neg x, pos y hit y-running after diag", test_neg_x_pos_y_hit_y_running_after_diag);
    kev_test_run("neg x, neg y hit y-running after diag", test_neg_x_neg_y_hit_y_running_after_diag);
    kev_test_run("neg x, pos y hit x-running after diag", test_neg_x_pos_y_hit_x_running_after_diag);
    kev_test_run("neg x, neg y hit x-running after diag", test_neg_x_neg_y_hit_x_running_after_diag);


    kev_test_run("pos x, pos y hit corner immediately", test_pos_x_pos_y_hit_corner_immediately);

    kev_test_run("pos x, neg y hit corner immediately", test_pos_x_neg_y_hit_corner_immediately);

    kev_test_run("neg x, pos y hit corner immediately", test_neg_x_pos_y_hit_corner_immediately);
    kev_test_run("neg x, neg y hit corner immediately", test_neg_x_neg_y_hit_corner_immediately);

    kev_test_run("pos x, pos y hit corner thru corner", test_pos_x_pos_y_hit_corner_thru_corner);
    kev_test_run("pos x, neg y hit corner thru corner", test_pos_x_neg_y_hit_corner_thru_corner);
    kev_test_run("neg x, pos y hit corner thru corner", test_neg_x_pos_y_hit_corner_thru_corner);
    kev_test_run("neg x, neg y hit corner thru corner", test_neg_x_neg_y_hit_corner_thru_corner);

    kev_test_run("pos x", test_pos_x);

    kev_test_run("neg x", test_neg_x);
    kev_test_run("pos y",test_pos_y);
    kev_test_run("neg y", test_neg_y);





    puts(kev_test_get_report());

    return 0;
}

void create_grid()
{
    kev_caster_material mat0 = {0, 1, 1, 0};
    kev_caster_material mat1 = {1, 1, 1, 0};
    kev_caster_material mat2 = {2, 1, 1, 0};
    kev_caster_material mat3 = {3, 1, 1, 0};
    kev_caster_material mat4 = {4, 1, 1, 0};
    kev_caster_material mat5 = {5, 1, 1, 0};
    kev_caster_material mat6 = {6, 1, 1, 0};
    kev_caster_material mat7 = {7, 1, 1, 0};
    kev_caster_material mat8 = {8, 1, 1, 0};
    /*
    A box with a 2x2 volume but described with 9 points, each of which can
    have an edge running in a Y direction and in an X direction. Below 
    I describe the layout of points (not the material numbers!)
      N
    W   E
      S
    7 8 9
    4 5 6
    1 2 3

    And where the materials go (graphically)

        43
       5  2
       6  1  
        78    
    */

    memcpy(grid_data, (kev_caster_material[]){
        mat0, mat6, mat0, mat0,
        mat0, mat0, mat7, mat0,
        mat0, mat0, mat8, mat0,
        mat0, mat5, mat0, mat0,
        mat0, mat0, mat0, mat0,
        mat0, mat0, mat0, mat1,
        mat4, mat0, mat0, mat0,
        mat3, mat0, mat0, mat0,
        mat0, mat0, mat0, mat2
    }, sizeof(grid_data));
    // line box with increasing material numbers going anti-clockwise for testing
    // outer walls are all 9 (should never be seen by rays originating inside)
    

    grid = (kev_caster_grid){
        3,
        3,
        grid_data
    };
}

void test_grid_creation()
{
    kev_test_assert_int_equal(kev_caster_get_face(&grid, 0, 0, 1).texture_id, 6);

}

void test_persistence()
{
    kev_test_assert_int_equal(kev_caster_get_face(&grid, 0, 0, 1).texture_id, 6);
}


void test_rotations()
{
    kev_caster_line_segment seg;

    seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 1.5};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 0);

    seg = (kev_caster_line_segment){-1.5, -1.5, -0.5, 0.0};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 0);
    
    seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 0.0};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 1);

    seg = (kev_caster_line_segment){-1.5, 1.5, 0.0, 0.5};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 1);

    seg = (kev_caster_line_segment){1.5, 1.5, 0.5, 0.0};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 2);

    seg = (kev_caster_line_segment){1.5, 0.5, 0.5, 2.0};
    kev_test_assert_int_equal(rotate_to_ne_quadrant(&seg), 3);

    
}

void test_flipping()
{
    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 2.0, 1.0};
    kev_caster_line_segment flipped = flip(seg);
    kev_test_assert_float_equal(flipped.x1, 0.5);
    kev_test_assert_float_equal(flipped.y1, 1.5);
    kev_test_assert_float_equal(flipped.x2, 1.0);
    kev_test_assert_float_equal(flipped.y2, 2.0);
}
void test_pos_x_pos_y_hit_y_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 2.0, 1.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    int texture_id = inc.mat.texture_id;
    kev_test_assert_int_equal(inc.mat.texture_id, 2);
    kev_test_assert_float_equal(inc.dist, 0.509901951);
}


void test_pos_x_neg_y_hit_y_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 2.0, 0.2};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    printf("Offset %f", inc.offset);
    kev_test_assert_float_equal(inc.offset, 0.8);
    kev_test_assert_int_equal(inc.mat.texture_id, 1);
    kev_test_assert_float_equal(inc.dist, 0.583095189);
}

// need to assert dist in all the rest (except the last five which I've done already)

void test_pos_x_pos_y_hit_x_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 1.8, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.8);
    kev_test_assert_int_equal(inc.mat.texture_id, 3);
}

void test_pos_x_neg_y_hit_x_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 0.6, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    kev_test_assert_int_equal(inc.mat.texture_id, 7);
}


void test_neg_x_pos_y_hit_y_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 0.0, 1.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 5);
}

void test_neg_x_neg_y_hit_y_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 0.0, 0.2};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.2);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 1.3, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.3);
    kev_test_assert_int_equal(inc.mat.texture_id, 3);
}

void test_neg_x_neg_y_hit_x_running_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 0.4, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 7);
} 


void test_pos_x_pos_y_hit_y_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 0.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    kev_test_assert_int_equal(inc.mat.texture_id, 1);
}
    

void test_pos_x_neg_y_hit_y_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 0.1};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.9);
    kev_test_assert_int_equal(inc.mat.texture_id, 1);
}


void test_pos_x_pos_y_hit_x_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 1.8, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.8);
    kev_test_assert_int_equal(inc.mat.texture_id, 3);
}

void test_pos_x_neg_y_hit_x_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 0.6, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    kev_test_assert_int_equal(inc.mat.texture_id, 7);
}


    

void test_neg_x_pos_y_hit_y_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.0, 0.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
}


void test_neg_x_neg_y_hit_y_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.0, 0.1};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.1);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 1.3, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.3);
    kev_test_assert_int_equal(inc.mat.texture_id, 3);
}


void test_neg_x_neg_y_hit_x_running_after()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 0.4, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 7);
}





void test_pos_x_pos_y_hit_y_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 1.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    kev_test_assert_int_equal(inc.mat.texture_id, 2);
}
  


void test_pos_x_neg_y_hit_y_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 2.0, 0.1};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.9);
    kev_test_assert_int_equal(inc.mat.texture_id, 1);
}


    

void test_pos_x_pos_y_hit_x_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 1.8, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.8);
    kev_test_assert_int_equal(inc.mat.texture_id, 3);
}


    

void test_pos_x_neg_y_hit_x_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 1.6, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.4);
    kev_test_assert_int_equal(inc.mat.texture_id, 8);
}


    

void test_neg_x_pos_y_hit_y_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.0, 1.6};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 5);
}


void test_neg_x_neg_y_hit_y_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 0.0, 0.1};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.1);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.3, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.3);
    kev_test_assert_int_equal(inc.mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_x_running_after_diag()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 0.4, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.6);
    kev_test_assert_int_equal(inc.mat.texture_id, 7);
}



void test_pos_x_pos_y_hit_corner_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.2, 2.0, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 2);
}

void test_pos_x_neg_y_hit_corner_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.2, 2.0, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 8);
}

void test_neg_x_pos_y_hit_corner_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 0.0, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_corner_immediately()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 0.0, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);

}


void test_pos_x_pos_y_hit_corner_thru_corner()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 2);
}

void test_pos_x_neg_y_hit_corner_thru_corner()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 1.5, 2.0, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 8);
}

void test_neg_x_pos_y_hit_corner_thru_corner()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.0, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_corner_thru_corner()
{
    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 0.0, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.0);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
    kev_test_assert_float_equal(inc.dist, 2.121320344);
}


void test_pos_x()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 2.0, 0.5};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.5);
    kev_test_assert_int_equal(inc.mat.texture_id, 1);
    kev_test_assert_float_equal(inc.dist, 1.5);
}

void test_pos_y()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){0.5, 0.5, 0.5, 2.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.5);
    kev_test_assert_int_equal(inc.mat.texture_id, 4);
    kev_test_assert_float_equal(inc.dist, 1.5);
}

void test_neg_x()
{

    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 0.5, 0.0, 0.5};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.5);
    kev_test_assert_int_equal(inc.mat.texture_id, 6);
kev_test_assert_float_equal(inc.dist, 1.5);
}

void test_neg_y()
{
    kev_caster_line_segment seg = (kev_caster_line_segment){1.5, 1.5, 1.5, 0.0};
    kev_caster_incidence inc = get_incidence(seg, &grid);
    kev_test_assert_float_equal(inc.offset, 0.5);
    kev_test_assert_int_equal(inc.mat.texture_id, 8);
    kev_test_assert_float_equal(inc.dist, 1.5);

}


