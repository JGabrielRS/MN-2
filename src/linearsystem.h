#ifndef LINEARSYSTEM
#define LINEARSYSTEM

#include "matrix/matrix.h"

namespace linear_system{
    using namespace Mat;
    using namespace Vec;

    VecDouble solve_lu(Matrix matrix, VecDouble right_part, int n){
        Matrix lu;
        double sum = 0;
        for(int i = 0; i < n; i++){
            for (int j = i; j < n; j++){
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += lu.at(i, k) * lu.at(k, j);
                lu.set(i, j, matrix.at(i, j) - sum);
            }
            for (int j = i + 1; j < n; j++){
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += lu.at(j, k) * lu.at(k, i);
                lu.set(j, i, (1 / lu.at(i, i)) * (matrix.at(j, i) - sum));
            }
        }

        VecDouble y;
        for (int i = 0; i < n; i++){
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(i, k) * y.at(k);
            y.at(i) = right_part.at(i) - sum;
        }
        
        VecDouble x;
        for (int i = n - 1; i >= 0; i--){
            sum = 0;
            for (int k = i + 1; k < n; k++)
                sum += lu.at(i, k) * x.at(k);
            x.at(i) = (1 / lu.at(i, i)) * (y.at(i) - sum);
        }
        return x;
    }
}

#endif // LINEARSYSTEM