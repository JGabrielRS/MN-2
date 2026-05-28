#ifndef RUNGEKUTAAO4
#define RUNGEKUTAAO4

#include <cmath>
#include <math.h>
#include <utility>
#include "vec/vec.h"

namespace rungekuttaO4 {
    using namespace std;
    using namespace Vec;

    // usar a matricula
    double a = 5; 
    double b = 6;
    double c = 5;
    double d = 4;
    double e = 1;
    double f = 4;
    
    // gerar o sistema de equacao
    VecDouble system_equations(VecDouble s, double t){
        double x1 = s.at(0);
        double x2 = s.at(1);
        double x3 = s.at(2);

        VecDouble derivative(3);
        derivative.at(0) = x2;
        derivative.at(1) = x3;
        derivative.at(2) = ((d+1)*cos(t)-(a+1)*x3-(b+2)*x2-(c+3)*x1);

        return derivative;

    }

    VecDouble runge_kuttaO4_one(VecDouble s_current, double t_current, double dt){
        // range é um vetor com o intervalo do problema
        VecDouble f1(3), f2(3), f3(3), f4(3);
        VecDouble s2(3), s3(3), s4(3), s_next(3);

        f1 = system_equations(s_current, t_current);

        for (int i = 0; i < 3; i++){
            s2.at(i) = s_current.at(i) + (dt/2) * f1.at(i);
        }
        
        f2 = system_equations(s2, t_current + dt/2);

        for (int i = 0; i < 3; i++){
            s3.at(i) = s_current.at(i) + (dt/2) * f2.at(i);
        }

        f3 = system_equations(s3, t_current + dt/2);

        for (int i = 0; i < 3; i++){
            s4.at(i) = s_current.at(i) + (dt) * f3.at(i);
        }

        f4 = system_equations(s4, t_current + dt);

        for (int i = 0; i < 3; i++){
            s_next.at(i) = s_current.at(i) + (dt/6) * (f1.at(i) + 2 * f2.at(i) + 2 * f3.at(i) + f4.at(i));
        }

        return s_next;
    }

    // n vai mais usar
    /*
    double runge_kuttaO4(double y0, VecDouble range, double dt){
        int n = int((range.at(1) - range.at(0))/dt);
        double y = y0;
        
        for (int i = 0; i < n; i++){
            y = runge_kuttaO4_one(y, dt);
        }
        return y;
    }
    */

    VecDouble adams_bashfortO4(VecDouble range, double dt){
        int n = int((range.at(1) - range.at(0))/dt);
        double t = range.at(0);

        // vetor pros estados iniciais, os metodos n tao generico, mas isso é problema pro eu do futuro
        VecDouble s0(3);
        s0.at(0) = a+1;
        s0.at(1) = b+1;
        s0.at(2) = c+1;

        VecDouble s1 = runge_kuttaO4_one(s0, t, dt); t+=dt;
        VecDouble s2 = runge_kuttaO4_one(s1, t, dt); t+=dt;
        VecDouble s3 = runge_kuttaO4_one(s2, t, dt); t+=dt;
        VecDouble s_current = s3;
        
        // utilizar os passos p/ range discreto
        VecDouble f0 = system_equations(s0, 0);
        VecDouble f1 = system_equations(s1, 0.1);
        VecDouble f2 = system_equations(s2, 0.2);
        VecDouble f3 = system_equations(s3, 0.3);

        for (int i = 3; i < n; i++){
            VecDouble s_next(3);

            for (int j = 0; j < 3; j++){
                s_next.at(j) = s_current.at(j) + (dt/24) * (55  * f3.at(j) -59 * f2.at(j) + 37 * f1.at(j) -9 * f0.at(j));
            }
            s_current = s_next;
            t+=dt;

            f0 = f1;
            f1 = f2;
            f2 = f3;
            f3 = system_equations(s_next, t);
        }

        return s_current;
    }
}

#endif // RUGFEKUTAAO4