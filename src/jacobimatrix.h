#ifndef JACOBIMATRIX
#define JACOBIMATRIX

#include <math.h> 
#include "matrix/matrix.h"

namespace jacobimatrix{
    #define PI 3.1415926535897932384626433832795028841971693993751058209749445923

    using namespace Mat;

    Matrix jacobi_matrix(Matrix A, int i, int j, int n){
        Matrix I = Matrix::get_indentity(n);
        Matrix J = I;
        double teta;
        // erro ta hardcoded, dps se quiser mudar da pra passar como parametro
        double error = 0.000001;
        if (abs(A.at(i, j)) <= error){ return J.at(i, j); };
        if (abs(A.at(j, j)) <= error){
            if ((A.at(i, j)) < 0){
                teta = PI/2;
            } else {
                teta = -PI/2;
            }
        } else {
            teta = atan((-A.at(i, j))/A.at(j, j));
        }
        J.set(i, i, cos(teta));
        J.set(j, j, cos(teta));
        J.set(i, j, sin(teta));
        J.set(j, i, -sin(teta));

        return J;
    }
}

#endif //JACOBIMATRIX