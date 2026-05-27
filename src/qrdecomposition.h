#ifndef QRDECOMPOSITION
#define QRDECOMPOSITION

#include "matrix/matrix.h"
#include "./jacobimatrix.h"
#include <utility>

namespace qrdecomposition{
    using namespace Mat;

    pair<Matrix, Matrix> qr_decomposition(Matrix A, int n){
        Matrix I = Matrix::get_indentity(n);
        Matrix QT, J, Rnew, Rold, R;
        QT = I;
        Rold = A;
        for (int j = 0; j < n; j++){
            for (int i = j+1; i <= n; i++){
                J = jacobimatrix::jacobi_matrix(Rold, i, j, n);
                Rnew = J * Rold;
                Rold = Rnew;
                QT = J * QT;
            }
        }
        // REVISAR!! isso tava assim antes
        // Q = Q.get_transposed()/
        // mudei pra não dar erro de sintaxe só, mas a semantica deve tá errada :)
        QT = QT.get_transposed();
        R = Rnew;
        pair<Matrix, Matrix> result = {QT, R};
        return result;
    }
}

#endif //QRDECOMPOSITION