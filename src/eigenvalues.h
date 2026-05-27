#ifndef EIGENVALUES
#define EIGENVALUES

#include "matrix/matrix.h"
#include <math.h>

namespace eigenvalues{
    using namespace Mat;
    using namespace Vec;

    Matrix householder_method_aux(Matrix A, int i){
        int n = A.get_size().first;
        Matrix I = Matrix::get_indentity(n);
        VecDouble w(n);
        VecDouble wl(n);
        VecDouble e(n);

        for(int k = i+1; k < n; k++){
            w.at(k) = A.at(k, i);
        }

        wl.at(i+1) = vec_length(w);
        
        VecDouble N = w - wl;
        N = vec_normalize(N);

        Matrix N_mat = Matrix::from_vector(N);
        Matrix N_transposed = N_mat.get_transposed();
        Matrix Nmult = N_mat*N_transposed;
        Matrix N2 = Nmult*2;
        
        Matrix H = I - N2;

        return H;
    }

    pair<Matrix, Matrix> householder_method(Matrix A){
        int n = A.get_size().first;
        Matrix H, Acur;
        H = Matrix::get_indentity(n);
        Acur = A;

        for(int i = 0; i <= n-2; i++){
            Matrix Hi = householder_method_aux(Acur, i);

            Matrix AH = Acur*Hi;
            Matrix Hi_T = Hi.get_transposed();
            Acur = Hi_T*AH;

            H = H*Hi;
        }

        return {Acur, H};
    }
};

#endif // EIGENVALUES