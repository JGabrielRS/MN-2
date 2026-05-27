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

    double A, B, C, D, E, F;
    A = 5; B = 6; C = 7; D = 9; E = 9; F = 1;

    Mat::Matrix M = {{
        {A+10, B+1, C+1, D+1, E+1, F+1, 1, 2, 3, 4},
        {B+1, B+12, D+1, E+1, F+1, A+1, 2, 3, 4, 5},
        {C+1, D+1, C+14, F+1, A+1, B+1, 3, 4, 5, 6},
        {D+1, E+1, F+1, D+16, B+1, C+1, 4, 5, 6,7},
        {E+1, F+1, A+1, B+1, E+18, D+1, 5, 6, 7, 8},
        {F+1, A+1, B+1, C+1, D+1, F+20, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, A+22, B+1, C+1, D+1},
        {2, 3, 4, 5, 6, 7, B+1, B+24, E+1, F+1},
        {3, 4, 5, 6, 7, 8, C+1, E+1, C+26, A+1},
        {4, 5, 6, 7, 8,9, D+1, F+1, A+1, D+28}
    }};

    std::pair<Mat::Matrix, Mat::Matrix> res = eigenvalues::householder_method(M);
    std::pair<Mat::Matrix, Mat::Matrix> resT = {res.first.get_transposed(), res.second.get_transposed()};
    //res.first.print();
    
    Mat::Matrix Q = res.second;
    Mat::Matrix MQ = M*Q;
    Mat::Matrix QMQ = resT.second * MQ;

    res.first.print();
    std::cout << std::endl;
    //res.second.print();

    return 0;
}