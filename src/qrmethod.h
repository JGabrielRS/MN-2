#ifndef QRMETHOD
#define QRMETHOD

#include "matrix/matrix.h"
#include "qrdecomposition.h"
#include <utility>
#include <vector>

namespace qrmethod{
    using namespace Mat;

    pair<Matrix, VecDouble> qr_method(Matrix A, int n, double error){
        Matrix I = Matrix::get_indentity(n);
        Matrix P, Q, R, Anew, Aold, Al;
        VecDouble lamb;
        double val = 100;
        P = I;
        Aold = A;
        while (val > error) {
            pair<Matrix, Matrix> result = qrdecomposition::qr_decomposition(Aold, n);
            Q = result.first;
            R = result.second;
            Anew = R * Q;
            Aold = Anew;
            P = P * Q;
            // REVISAR!!! isso tava assim, não sei o que era pra ser
            //val = 
            double sum = 0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (i > j){
                        sum = sum + Anew.at(i, j);
                    }
                }  
            }
            val = sum;
        }
        for (int i; i < n; i++){
            lamb.push_back(Anew.at(i, i));
        }
        pair<Matrix, VecDouble> result = {P, lamb};
        return result;
    }
}

#endif //QRMETHOD