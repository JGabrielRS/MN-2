#include "matrix/matrix.h"
#include "vec/vec.h"
#include "eigenvalues.h"
#include "qrmethod.h"
#include "svddecomposition.h"
#include "finitedifference.h"
#include "linearsystem.h"

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

    // Mat::Matrix M = {{
    //     {A+10, B+1, C+1, D+1, E+1, F+1, 1, 2, 3, 4},
    //     {B+1, B+12, D+1, E+1, F+1, A+1, 2, 3, 4, 5},
    //     {C+1, D+1, C+14, F+1, A+1, B+1, 3, 4, 5, 6},
    //     {D+1, E+1, F+1, D+16, B+1, C+1, 4, 5, 6,7},
    //     {E+1, F+1, A+1, B+1, E+18, D+1, 5, 6, 7, 8},
    //     {F+1, A+1, B+1, C+1, D+1, F+20, 6, 7, 8, 9},
    //     {1, 2, 3, 4, 5, 6, A+22, B+1, C+1, D+1},
    //     {2, 3, 4, 5, 6, 7, B+1, B+24, E+1, F+1},
    //     {3, 4, 5, 6, 7, 8, C+1, E+1, C+26, A+1},
    //     {4, 5, 6, 7, 8,9, D+1, F+1, A+1, D+28}
    // }};

    // std::pair<Mat::Matrix, Mat::Matrix> res = eigenvalues::householder_method(M);
    // std::pair<Mat::Matrix, Mat::Matrix> resT = {res.first.get_transposed(), res.second.get_transposed()};
    
    // Mat::Matrix Q = res.second;
    // Mat::Matrix MQ = M*Q;
    // Mat::Matrix QMQ = resT.second * MQ;

    // std::pair<Mat::Matrix, Vec::VecDouble> resqr = qrmethod::qr_method(QMQ, QMQ.get_size().first, 0.0001);
    // resqr.first.print();
    // std::cout << std::endl;
    // Vec::print_vec(resqr.second);

    //Q3
    Mat::Matrix P = {{
        {A+1, 1, 0, 2},
        {B+1, 0, 1, 1},
        {C+1, 1, 1, 0},
        {D+1, 2, 0, 1},
        {E+1, 0, 2, 1},
        {F+1, 1, 0, 1}
    }};
    Mat::Matrix Q = {{
        {1, 0, A+1, 0, B+1, 0, C+1, 0, D+1, 1},
        {0, 1, 0, B+1, 0, C+1, 0, D+1, 0,1},
        {1, 1, 0, 0, E+1, 0, F+1, 0, 1, 0},
        {0, 0, 1, 1, 0, A+1, 0, B+1, 1, 1}
    }};

    Mat::Matrix M = P*Q;
    Mat::Matrix MT = M.get_transposed();
    Mat::Matrix MMT = M*MT;
    Mat::Matrix MTM = MT*M;
    //M.print(0, 0);

    std::pair<Mat::Matrix, Vec::VecDouble> resultU = qrmethod::qr_method(MMT, MMT.get_size().first, 0.0001);
    std::pair<Mat::Matrix, Vec::VecDouble> resultV = qrmethod::qr_method(MTM, MTM.get_size().first, 0.0001);
    Mat::Matrix U = resultU.first;
    Mat::Matrix V = resultV.first;

    //Vec::VecDouble lambU = resultU.second;
    //Vec::VecDouble lambV = resultV.second;
    // MTM.print(0, 0);
    // std::cout << std::endl;
    // U.print();
    // std::cout << std::endl;
    // V.print();
    // std::cout << std::endl;
    // Vec::print_vec(lambU);
    // std::cout << std::endl;
    // Vec::print_vec(lambV);

    // Consegui testar essa no wolfram, deu certo o resultado :)
    Vec::VecDouble sigma = svd_decomposition::svd_decomposition(M, 0.0001);
    std::cout << "--- Valores singulares ---" << std::endl;
    Vec::print_vec(sigma);

    Mat::Matrix bigSigma{MMT.get_size().first, MTM.get_size().second};
    for(int i = 0; i < sigma.size(); i++){
        bigSigma.set(i, i, sigma.at(i));
    }
    std::cout << "--- U ---" << std::endl;
    U.print();
    std::cout << "--- bigSigma ---" << std::endl;
    bigSigma.print();
    std::cout << "--- V ---" <<  std::endl;
    V.print();
    
    // Calculando M de volta a partir da decomposição
    // M = U*BigSigma*Vt
    Mat::Matrix Vt = V.get_transposed();
    Mat::Matrix sig_vt = bigSigma*Vt;
    Mat::Matrix M_rec = U*sig_vt;
    
    std::cout << "--- M ---" << std::endl;
    M.print();
    std::cout << "--- Reconstrucao de M ---" << std::endl;
    M_rec.print();

    // Q5
    // Problema abaixo foi apresentado na aula 27, testei e o programa resolveu corretamente :)
    // f(x) = 0 nesse problema, tem que mudar lá no arquivo
    // Vec::VecDouble res = finite_difference::finite_differente_order2(0, 1, 0, 1, 4, 1, 0, -1, false, false);
    
    // Problema abaixo foi apresentado aqui: https://pythonnumericalmethods.studentorg.berkeley.edu/notebooks/chapter23.03-Finite-Difference-Method.html
    // Testei e o programa também resolveu corretamente
    // f(x) = -9.8 nesse problema, tem que mudar lá no arquivo
    // Vec::VecDouble res = finite_difference::finite_differente_order2(0, 5, 0, 50, 10, 1, 0, 0, false, false);
    
    // Problema da prova, a unica parte que não consigo dar certeza que tá certa é se tou calculando certo a condição de neumann
    // Acho que pra testar se tá certo tem que ir ponto a ponto e checar se as condições batem
    // IMPORTANTE!! f(x) = (D+1)*exp(-x) nesse problema, tem que mudar lá no arquivo
    // Vec::VecDouble res = finite_difference::finite_differente_order2(0, 1, A, C, 10, A+1, B+1, C+1, false, true);
    
    // Vec::print_vec(res);

    return 0;
}