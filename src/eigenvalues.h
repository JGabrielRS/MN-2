#ifndef EIGENVALUES
#define EIGENVALUES

#include "matrix/matrix.h"
#include <math.h>

namespace eigenvalues{
    using namespace std;



    vector<double> operator-(vector<double> &v1, vector<double> &v2){
        vector<double> result;
        // TODO dar erro se tamanho for diferente
        for(int i = 0; i < v1.size(); i++){
            result.at(i) = v1.at(i) - v2.at(i);
        }
        return result;
    }

    double vec_length(vector<double> &vec){
        double length = 0;
        for(int k = 0; k < vec.size(); k++){
            length+=pow(length, 2);
        }
        return sqrt(length);
    }

    vector<double> vec_normalize(vector<double> &vec){
        vector<double> result;
        double length = vec_length(vec);
        for(int i = 0; i < vec.size(); i++){
            result.at(i) = vec.at(i)/length;
        }
        return result;
    }

    Matrix householder_method_aux(Matrix A, int i){
        int n = A.get_size().first;
        Matrix I = Matrix::get_indentity(n);
        vector<double> w(n);
        vector<double> wl(n);
        vector<double> e(n);
        for(int k = 0;k < n; k++){
            w.at(k) = 0; wl.at(k) = 0; e.at(k) = 0;
        }
        for(int k = k+1; k < n; k++){
            w.at(k) = A.at(k, i);
        }

        for(int k = 0; k < w.size(); k++){
            wl.at(i+1)+=pow(w.at(k), 2);
        }
        wl.at(i+1) = sqrt(wl.at(i+1));

        vector<double> N = w - wl;
        N = vec_normalize(N);

        Matrix N_mat = Matrix::from_vector(N);
        Matrix N_transposed = N_mat.get_transposed();
        Matrix Nmult = N_mat*N_transposed;
        Matrix N2 = Nmult*2;

        Matrix H = I - N2;

        return H;
    }
}

#endif // EIGENVALUES