#ifndef QRMETHOD
#define QRMETHOD

#include "matrix/matrix.h"
#include <math.h>
#include <utility>
#include <vector>

namespace qrmethod{
    using namespace Mat;
    using namespace Vec;

    #define PI 3.1415926535897932384626433832795028841971693993751058209749445923

    Matrix jacobi_matrix(Matrix A, int i, int j, int n){
        Matrix I = Matrix::get_indentity(n);
        Matrix J = I;
        double teta;
        // erro ta hardcoded, dps se quiser mudar da pra passar como parametro
        double error = 0.000001;
        if (abs(A.at(i, j)) <= error){ return J; };
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

    pair<Matrix, Matrix> qr_decomposition(Matrix A, int n){
        Matrix I = Matrix::get_indentity(n);
        Matrix QT, Rnew, Rold, R;
        Matrix J {n};
        QT = I;
        Rold = A;
        
        for (int j = 0; j < n-1; j++){
            for (int i = j+1; i < n; i++){
                J = jacobi_matrix(Rold, i, j, n);
                Rnew = J * Rold;
                Rold = Rnew;
                QT = J * QT;
            }
        }
        QT = QT.get_transposed();
        R = Rnew;
        pair<Matrix, Matrix> result = {QT, R};
        return result;
    }
    
    pair<Matrix, VecDouble> qr_method(Matrix A, int n, double error){
        Matrix I = Matrix::get_indentity(n);
        Matrix P, Q, R, Anew, Aold, Al;
        VecDouble lamb;
        double val = 100;
        P = I;
        Aold = A;
        while (val > error) {
            pair<Matrix, Matrix> result = qr_decomposition(Aold, n);
            
            Q = result.first;
            R = result.second;
            Anew = R * Q;
            Aold = Anew;
            P = P * Q;
            // std::cout<<("------------------Anew----------------")<<endl;
            // Anew.print();
            // std::cout<<("--------------------------------------")<<endl; 
            double sum = 0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (i != j){
                        sum = sum + std::pow(Anew.at(i, j), 2);
                    }
                }  
            
            }
            val = sum;
        }
        for (int i = 0; i < n; i++){
            lamb.push_back(Anew.at(i, i));
        }
        pair<Matrix, VecDouble> result = {P, lamb};
        return result;
    }
}

#endif //QRMETHOD