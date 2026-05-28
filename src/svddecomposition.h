#ifndef MN_SVD
#define MN_SVD

#include "matrix/matrix.h"
#include "qrmethod.h"

namespace svd_decomposition{
    using namespace Mat;
    using namespace Vec;

    VecDouble svd_decomposition(Matrix A, double error){
        int m = A.get_size().first;
        int n = A.get_size().second;

        Matrix AT = A.get_transposed();
        Matrix A_bar = m<n?A*AT:AT*A;

        pair<Matrix, VecDouble> qr_result = qrmethod::qr_method(A_bar, A_bar.get_size().first, error);
        VecDouble values = qr_result.second;
        for(size_t i = 0; i < values.size(); i++){
            // FIXME o que faz se for negativo?
            if(values.at(i) < 0) values.at(i) = 0;
            else values.at(i) = sqrt(values.at(i));
        }
        return values;
    }
}


#endif // MN_SVD