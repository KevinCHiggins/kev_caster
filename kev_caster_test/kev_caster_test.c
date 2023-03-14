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
    kev_caster_material mat9 = {9, 1, 1, 0};
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
    */

    memcpy(grid_data, (kev_caster_material[]){
        mat9, mat7, mat9, mat6,
        mat9, mat8, mat0, mat0,
        mat0, mat0, mat1, mat9,
        mat0, mat0, mat9, mat5,
        mat0, mat0, mat0, mat0,
        mat0, mat0, mat2, mat9,
        mat4, mat9, mat0, mat0,
        mat3, mat9, mat0, mat0,
        mat0, mat0, mat0, mat0
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
    // Sample some points
    kev_test_assert_true(kev_caster_x_running_front(grid, 0, 0).texture_id);
    kev_test_assert_true(kev_caster_y_running_front(grid, 0, 0).texture_id);
    kev_test_assert_true(!kev_caster_x_running_front(grid, 1, 1).texture_id);
    kev_test_assert_true(!kev_caster_y_running_front(grid, 1, 1).texture_id); 
    kev_test_assert_true(!kev_caster_x_running_front(grid, 2, 2).texture_id);
    kev_test_assert_true(!kev_caster_y_running_front(grid, 2, 2).texture_id); 
    kev_test_assert_true(!kev_caster_x_running_front(grid, 2, 1).texture_id);
    kev_test_assert_true(kev_caster_y_running_front(grid, 2, 1).texture_id); 

}

void test_persistence()
{
    // Sample some points
    kev_test_assert_true(kev_caster_x_running_front(grid, 0, 0).texture_id);
    kev_test_assert_true(kev_caster_y_running_front(grid, 0, 0).texture_id);
    kev_test_assert_true(!kev_caster_x_running_front(grid, 1, 1).texture_id);
    kev_test_assert_true(!kev_caster_y_running_front(grid, 1, 1).texture_id); 
    kev_test_assert_true(!kev_caster_x_running_front(grid, 2, 2).texture_id);
    kev_test_assert_true(!kev_caster_y_running_front(grid, 2, 2).texture_id); 
    kev_test_assert_true(!kev_caster_x_running_front(grid, 2, 1).texture_id);
    kev_test_assert_true(kev_caster_y_running_front(grid, 2, 1).texture_id); 

}


void test_pos_x_pos_y_hit_y_running_immediately()
{
    kev_caster_material mat;

    float offset = get_incidence(1.5, 1.5, 2.0, 1.6, grid, &mat);
    printf("%f\n", offset);
    kev_test_assert_float_equal(offset, 0.4);
    int texture_id = mat.texture_id;
    printf("%d\n", texture_id);
    kev_test_assert_int_equal(mat.texture_id, 2);
}

void test_pos_x_neg_y_hit_y_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 2.0, 0.2, grid, &mat), 0.8);
    kev_test_assert_int_equal(mat.texture_id, 1);
}


void test_pos_x_pos_y_hit_x_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 1.8, 2.0, grid, &mat), 0.8);
    kev_test_assert_int_equal(mat.texture_id, 3);
}

void test_pos_x_neg_y_hit_x_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 0.6, 0.0, grid, &mat), 0.4);
    kev_test_assert_int_equal(mat.texture_id, 7);
}


void test_neg_x_pos_y_hit_y_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 0.0, 1.6, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 5);
}

void test_neg_x_neg_y_hit_y_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 0.0, 0.2, grid, &mat), 0.2);
    kev_test_assert_int_equal(mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 1.3, 2.0, grid, &mat), 0.3);
    kev_test_assert_int_equal(mat.texture_id, 3);
}

void test_neg_x_neg_y_hit_x_running_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 0.4, 0.0, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 7);
} 


void test_pos_x_pos_y_hit_y_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 2.0, 0.6, grid, &mat), 0.4);
    kev_test_assert_int_equal(mat.texture_id, 1);
}
    

void test_pos_x_neg_y_hit_y_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 2.0, 0.1, grid, &mat), 0.9);
    kev_test_assert_int_equal(mat.texture_id, 1);
}




    

void test_pos_x_pos_y_hit_x_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 1.8, 2.0, grid, &mat), 0.8);
    kev_test_assert_int_equal(mat.texture_id, 3);
}


    

void test_pos_x_neg_y_hit_x_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 0.6, 0.0, grid, &mat), 0.4);
    kev_test_assert_int_equal(mat.texture_id, 7);
}


    

void test_neg_x_pos_y_hit_y_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.0, 0.6, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 6);
}


void test_neg_x_neg_y_hit_y_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.0, 0.1, grid, &mat), 0.1);
    kev_test_assert_int_equal(mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 1.3, 2.0, grid, &mat), 0.3);
    kev_test_assert_int_equal(mat.texture_id, 3);
}


void test_neg_x_neg_y_hit_x_running_after()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 0.4, 0.0, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 7);
}





void test_pos_x_pos_y_hit_y_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 2.0, 1.6, grid, &mat), 0.4);
    kev_test_assert_int_equal(mat.texture_id, 2);
}
  


void test_pos_x_neg_y_hit_y_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 2.0, 0.1, grid, &mat), 0.9);
    kev_test_assert_int_equal(mat.texture_id, 1);
}


    

void test_pos_x_pos_y_hit_x_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 1.8, 2.0, grid, &mat), 0.8);
    kev_test_assert_int_equal(mat.texture_id, 3);
}


    

void test_pos_x_neg_y_hit_x_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 1.6, 0.0, grid, &mat), 0.4);
    kev_test_assert_int_equal(mat.texture_id, 8);
}


    

void test_neg_x_pos_y_hit_y_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.0, 1.6, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 5);
}


void test_neg_x_neg_y_hit_y_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 0.0, 0.1, grid, &mat), 0.1);
    kev_test_assert_int_equal(mat.texture_id, 6);
}

void test_neg_x_pos_y_hit_x_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.3, 2.0, grid, &mat), 0.3);
    kev_test_assert_int_equal(mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_x_running_after_diag()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 0.4, 0.0, grid, &mat), 0.6);
    kev_test_assert_int_equal(mat.texture_id, 7);
}



void test_pos_x_pos_y_hit_corner_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 1.2, 2.0, 2.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 2);
}

void test_pos_x_neg_y_hit_corner_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.2, 2.0, 0.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 8);
}

void test_neg_x_pos_y_hit_corner_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 0.0, 2.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_corner_immediately()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 0.0, 0.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 6);

}


void test_pos_x_pos_y_hit_corner_thru_corner()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 2.0, 2.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 2);
}

void test_pos_x_neg_y_hit_corner_thru_corner()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 1.5, 2.0, 0.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 8);
}

void test_neg_x_pos_y_hit_corner_thru_corner()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.0, 2.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 4);
}

void test_neg_x_neg_y_hit_corner_thru_corner()
{
    kev_caster_material mat;
    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 0.0, 0.0, grid, &mat), 0.0);
    kev_test_assert_int_equal(mat.texture_id, 6);   

}



void test_pos_x()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 2.0, 0.5, grid, &mat), 0.5);
    kev_test_assert_int_equal(mat.texture_id, 1);
}

void test_pos_y()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(0.5, 0.5, 0.5, 2.0, grid, &mat), 0.5);
    kev_test_assert_int_equal(mat.texture_id, 4);
}

void test_neg_x()
{
    kev_caster_material mat;

    kev_test_assert_float_equal(get_incidence(1.5, 0.5, 0.0, 0.5, grid, &mat), 0.5);
    kev_test_assert_int_equal(mat.texture_id, 6);
}

void test_neg_y()
{
    kev_caster_material mat;
    kev_test_assert_float_equal(get_incidence(1.5, 1.5, 1.5, 0.0, grid, &mat), 0.5);
    kev_test_assert_int_equal(mat.texture_id, 8);   

}

