#ifndef MN_FINITEDIFF
#define MN_FINITEDIFF

#include <math.h>
#include "matrix/matrix.h"
#include "linearsystem.h"

namespace finite_difference{
    using namespace Mat;
    using namespace Vec;

    // Em algum momento deveriamos fazer isso ser uma função anonima
    double f(double x){
        // return -9.8;
        // return 0;
        return 2;
    }

    // Problemas no formato c1*y''(x)+c2*y'(x)+c3y(x)=f(x)
    // y(a) = ya
    // y(b) = yb
    VecDouble finite_differences_order2(double a, double b, double ya, double yb, int N, double c1, double c2, double c3){
        double delta = (b-a)/N;
        double yPrev, yCur, yNext;
        double delta2 = pow(delta, 2);

        yPrev = c1/delta2 - c2/2*delta;
        yCur = (-2*c1)/delta2 + c3;
        yNext = c1/delta2 + c2/2*delta;

        VecDouble yValues(N+1);

        yValues.at(0) = ya;
        yValues.at(N) = yb;

        Matrix lin_system{N+1};
        lin_system.set(0, 0, 1);
        lin_system.set(N, N, 1);
        for(int i = 1; i < N; i++){
            double xCur = a + i*delta;
            yValues.at(i) = f(xCur);

            lin_system.set(i, i-1, yPrev);
            lin_system.set(i, i, yCur);
            lin_system.set(i, i+1, yNext);
        }

        return linear_system::solve_lu(lin_system, yValues);
    }
}

#endif // MN_FINITEDIFF