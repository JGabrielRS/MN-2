#include "eigenvalues.h"
#include "matrix/matrix.h"
#include "vec/vec.h"
#include "qrmethod.h"

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
        {40, 8, 4, 2, 1},
        {8, 30, 12, 6, 2},
        {4, 12, 20, 1, 2},
        {2, 6, 1, 25, 4},
        {1, 2, 2, 4, 5}
    }};
    std::pair<Mat::Matrix, Vec::VecDouble> result = qrmethod::qr_method(m, m.get_size().first, 0.00000000000000000000000000000001);
    Mat::Matrix p = result.first;
    Vec::VecDouble lamb = result.second;
    p.print();
    Vec::print_vec(lamb);


    return 0;
}