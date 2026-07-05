#ifndef EIGENVALUES
#define EIGENVALUES

#include "matrix/matrix.h"
#include "vec/vec.h"
#include <math.h>
#include <utility>

namespace eigenvalues{
    using namespace Mat;
    using namespace Vec;

    // TODO testar isso aqui
    // método da potencia regular, não sei o nome em ingles :P
    pair<double, VecDouble> regular_p(Matrix A, VecDouble v, double epsilon){
        VecDouble vold = vec_normalize(v);
        double d_old = 0;
        double error = 1;
        while (error > epsilon) {
            Matrix vold_m = Matrix::from_vector(vold);
            Matrix vnew = A*vold_m;
            Matrix vold_m_t = vold_m.get_transposed();

            double d_new = (vold_m_t*vnew).at(0, 0);
            error = abs((d_new - d_old)/d_new);

            VecDouble vnew_m = Matrix::to_vector(vnew);
            vold = vec_normalize(vnew_m);

            d_old = d_new;
        }

        return {d_old, vold};
    }

    // TODO terminar e testar
    pair<double, VecDouble> inverse_p(Matrix A, VecDouble v, double epsilon){
        Matrix A_i = A.get_inverse();
        pair<double, VecDouble> res = regular_p(A_i, v, epsilon);
        return {1.0/res.first, res.second};
    }

    // TODO testar
    pair<double, VecDouble> desloc_p(Matrix A, VecDouble v, double epsilon, double mi){
        Matrix I = Matrix::get_indentity(A.get_size().first);
        I = I*mi;
        Matrix A_desloc = A - I;
        pair<double, VecDouble> res = inverse_p(A_desloc, v, epsilon);
        return {res.first + mi, res.second};
    }

    // === householder ===

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