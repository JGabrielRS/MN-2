#ifndef JACOBIMATRIX
#define JACOBIMATRIX

#include <math.h> 
#include "matrix/matrix.h"

namespace jacobimatrix{
    using namespace std;

    Matrix jacobi_matrix(Matrix A, int i, int j, int n){
        Matrix I = Matrix::get_indentity(n);
        Matrix J = I;
        double teta;
        // erro ta hardcoded, dps se quiser mudar da pra passar como parametro
        double error = 0.000001;
        if (abs(A.at(i).at(j)) <= error){return J.at(i).at(j)};
        if (abs(A.at(j).at(j)) <= error){
            if ((A.at(i).at(j)) < 0){
                teta = PI/2;
            } else {
                teta = -PI/2;
            }
        } else {
            teta = atan((-A.at(i).at(j))/A.at(j).at(j));
        }
        J.at(i).(i) = cos(teta);
        J.at(j).(j) = cos(teta);
        J.at(i).(j) = sin(teta);
        J.at(j).(i) = -sin(teta);

        return J;
    }
}

#endif //JACOBIMATRIX