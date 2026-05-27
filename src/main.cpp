#include "eigenvalues.h"
#include "matrix/matrix.h"
#include "vec/vec.h"
#include "qrmethod.h"

int main(){
    double A, B, C, D, E, F;
    A = 5; B = 6; C = 7; D = 9; E = 9; F = 1;
    
    // Vec::VecDouble vec2{1, 2, 3};
    // Mat::Matrix matv = Mat::Matrix::from_vector(vec2);
    // Mat::Matrix matvt = matv.get_transposed();
    // matv.print();
    // std::cout << std::endl;
    // matvt.print();
    // std::cout << std::endl;
    // (matv*matvt).print();
    // Vec::print_vec(vec2);
    // Mat::Matrix m1{{
    //     {1, 2, 3}
    // }};

    // Mat::Matrix m2{{
    //     {1},
    //     {2},
    //     {3}
    // }};

    // Mat::Matrix m{{
    //     {40, 8, 4, 2, 1},
    //     {8, 30, 12, 6, 2},
    //     {4, 12, 20, 1, 2},
    //     {2, 6, 1, 25, 4},
    //     {1, 2, 2, 4, 5}
    // }};
    // Mat::Matrix m{{
    //     {1, 0, 0},
    //     {0, -3.0/5.0, -4.0/5.0},
    //     {0, -4.0/5.0, 3.0/5.0}
    // }};

    // std::pair<Mat::Matrix, Vec::VecDouble> result = qrmethod::qr_method(m, m.get_size().first, 0.01);
    // Mat::Matrix p = result.first;
    // Vec::VecDouble lamb = result.second;
    // p.print();
    // Vec::print_vec(lamb);

    // Q2

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
    
    Mat::Matrix Q = res.second;
    Mat::Matrix MQ = M*Q;
    Mat::Matrix QMQ = resT.second * MQ;

    std::pair<Mat::Matrix, Vec::VecDouble> resqr = qrmethod::qr_method(QMQ, QMQ.get_size().first, 0.0001);
    resqr.first.print();
    std::cout << std::endl;
    Vec::print_vec(resqr.second);

    // Q3
    // Mat::Matrix P = {{
    //     {A+1, 1, 0, 2},
    //     {B+1, 0, 1, 1},
    //     {C+1, 1, 1, 0},
    //     {D+1, 2, 0, 1},
    //     {E+1, 0, 2, 1},
    //     {F+1, 1, 0, 1}
    // }};
    // Mat::Matrix Q = {{
    //     {1, 0, A+1, 0, B+1, 0, C+1, 0, D+1, 1},
    //     {0, 1, 0, B+1, 0, C+1, 0, D+1, 0,1},
    //     {1, 1, 0, 0, E+1, 0, F+1, 0, 1, 0},
    //     {0, 0, 1, 1, 0, A+1, 0, B+1, 1, 1}
    // }};

    // Mat::Matrix M = P*Q;
    // Mat::Matrix MT = M.get_transposed();
    // Mat::Matrix MTM = M*MT;

    // std::pair<Mat::Matrix, Vec::VecDouble> result = qrmethod::qr_method(MTM, MTM.get_size().first, 0.0001);
    // Mat::Matrix p = result.first;
    // Vec::VecDouble lamb = result.second;
    // MTM.print(0, 0);
    // std::cout << std::endl;
    // p.print();
    // Vec::print_vec(lamb);

    return 0;
}