#ifndef RUNGEKUTAAO4
#define RUNGEKUTAAO4

#include <math.h>
#include <utility>
#include "vec/vec.h"

namespace rungekuttaO4 {
    using namespace std;
    using namespace Vec;

    double f(double x){
        return x;
    }
    
    double runge_kuttaO4(double y0, VecDouble range, double h){
        int n = int((range.at(1) - range.at(0))/h);
        double k1, k2, k3, k4, y;
        y = y0;
        for (int i = 0; i < n; i++){
            k1 = h * f(y0);
            k2 = f(y0 + h*k1/2);
            k3 = f(y0 + h*k2/2);
            k4 = f(y0 + h*k3);

            y = y + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
        }
        return y;
    }

    double adams_bashfortO4(double y0, double h){
        
        
        double y = y0 + h/24 / (55 * f())
    }
}

#endif // RUGFEKUTAAO4