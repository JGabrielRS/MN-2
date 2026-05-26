#ifndef LINEARSYSTEM
#define LINEARSYSTEM

#include <vector>

namespace linear_system{
    using namespace std;
    
    typedef vector<vector<double>> Matrix;

    vector<double> solve_lu(Matrix matrix, vector<double> right_part, int n){
        Matrix lu;
        double sum = 0;
        for(int i = 0; i < n; i++){
            for (int j = i; j < n; j++){
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += lu.at(i).at(k) * lu.at(k).at(j);
                lu.at(i).at(j) = matrix.at(i).at(j) - sum;
            }
            for (int j = i + 1; j < n; j++){
                sum = 0;
                for (int k = 0; k < i; k++)
                    sum += lu.at(j).at(k) * lu.at(k).at(i);
                lu.at(j).at(i) = (1 / lu.at(i).at(i)) * (matrix.at(j).at(i) - sum);
            }
        }

        vector<double> y;
        for (int i = 0; i < n; i++){
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += lu.at(i).at(k) * y.at(k);
            y.at(i) = right_part.at(i) - sum;
        }
        // find solution of Ux = y
        vector<double> x;
        for (int i = n - 1; i >= 0; i--){
            sum = 0;
            for (int k = i + 1; k < n; k++)
                sum += lu.at(i).at(k) * x.at(k);
            x.at(i) = (1 / lu.at(i).at(i)) * (y.at(i) - sum);
        }
        return x;
    }
}

#endif // LINEARSYSTEM