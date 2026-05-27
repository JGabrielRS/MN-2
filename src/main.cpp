#include "eigenvalues.h"
#include "matrix/matrix.h"
#include "vec/vec.h"

int main(){
    // Vec::VecDouble vec2{1, 2, 3, 4};
    // Vec::print_vec(vec2);
    // Mat::Matrix m1{{
    //     {1, 2, 3}
    // }};

    // Mat::Matrix m2{{
    //     {1},
    //     {2},
    //     {3}
    // }};

    Mat::Matrix m{{
        {3, 1, 0, 0, 0},
        {1, 4, 3, 0, 0},
        {0, 3, 5, 2, 1},
        {0, 0, 2, 6, 3},
        {0, 0, 1, 3, 8}
    }};
    m = eigenvalues::householder_method_aux(m, 0);
    m.print();

    return 0;
}