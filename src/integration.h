#ifndef INTEGRATION
#define INTEGRATION

#include "qrmethod.h"
#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <numbers>

namespace integration {
    using namespace std;
    typedef pair<vector<double>, double> CotesWeight;
    typedef pair<vector<double>, vector<double>> GaussWeights;
    typedef function<double(double)> NumFunc;
    typedef function<double(double, double)> NumFunc2;

    // double f(double x){
    //     return exp(x);

    //     // pro gauss hermite
    //     // return cos(x);
    // }

    // === Auxiliares ===

    double sum_gauss(GaussWeights points, int n, NumFunc f){
        double sum = 0;
        for(int i = 0; i < n; i++){
            sum += f(points.first.at(i))*points.second.at(i);
        }

        return sum;
    }

    // === Newton-Cotes Fechado ===
    
    double integrate_cotes(double x0, double xf, int p, CotesWeight& points, NumFunc f){
        double delta = (xf - x0)/p;

        double sum = 0;
        for(int i = 0; i < points.first.size(); i++){
            double xi = x0 + delta*i;
            sum+=points.first.at(i)*f(xi);
        }

        return (delta*points.second)*sum;
    }

    CotesWeight get_closed_cotes_weigth(int p){
        switch (p)
        {
        case 1:
            return {{1, 1}, 1.0/2};
        case 2:
            return {{1, 4, 1}, 1.0/3};
        case 3:
            return {{1, 3, 3, 1}, 3.0/8};
        case 4:
            return {{7, 32, 12, 32, 7}, 2.0/45};
        default:
            return {};
        }
    }
    
    double closed_newton_cotes(double a, double b, double n, int p, NumFunc f){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_closed_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate_cotes(xi, xf, p, points, f);
        }
        return as;
    }

    // === Newton-Cotes Aberto ===

    CotesWeight get_open_cotes_weigth(int p){
        switch (p)
        {
        case 1:
            return {{0, 1}, 2.0};
        case 2:
            return {{0, 1, 1}, 3.0/2};
        case 3:
            return {{0, 2, -1, 2}, 4.0/3};
        case 4:
            return {{0, 11, 1, 1, 11}, 5.0/24};
        default:
            return {};
        }
    } 

    double open_newton_cotes(double a, double b, double n, int p, NumFunc f){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_open_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate_cotes(xi, xf, p+1, points, f);
        }
        return as;
    }

    // === Gauss-Legendre ===

    GaussWeights get_legendre_weights(int n){
        double p1, p2, w1, w2;
        switch (n)
        {
        case 2:
            p1 = 1.0/sqrt(3);
            return {{-p1, p1}, {1, 1}};
        case 3:
            p1 = sqrt(3.0/5);
            return {{-p1, 0, p1}, {5.0/9, 8.0/9, 5.0/9}};
        case 4:
            p1 = sqrt((3.0/7)+(2.0/7)*sqrt(6.0/5));
            p2 = sqrt((3.0/7)-(2.0/7)*sqrt(6.0/5));
            w1 = (18-sqrt(30))/36;
            w2 = (18+sqrt(30))/36;
            return {{-p1, -p2, p2, p1}, {w1, w2, w2, w1}};
        default:
            return {};
        }
    }

    double gauss_legendre(double a, double b, int n, NumFunc f){
        GaussWeights points = get_legendre_weights(n);

        double sum = 0;
        for(int i = 0; i < n; i++){
            double x_alpha = (a+b)/2 + ((b-a)/2)*points.first.at(i);
            sum += f(x_alpha)*points.second.at(i);
        }

        return sum * ((b-a)/2);
    }

    // === Gauss Hermite === 
    GaussWeights get_hermite_weights(int n){
        // https://www.efunda.com/math/num_integration/findgausshermite.cfm
        double p1, p2, w1, w2;
        switch (n)
        {
        case 2:
            p1 = 0.707107;
            return {{-p1, p1}, {0.886227, 0.886227}};
        case 3:
            p1 = 1.22474;
            return {{-p1, 0, p1}, {0.295409, 1.18164, 0.295409}};
        case 4:
            p1 = 1.65068;
            p2 = 0.524648;
            w1 = 0.0813128;
            w2 = 0.804914;
            return {{-p1, -p2, p2, p1}, {w1, w2, w2, w1}};
        default:
            return {};
        }
    }

    double gauss_hermite(int n, NumFunc f){
        GaussWeights points = get_hermite_weights(n);
        return sum_gauss(points, n, f);
    }

    // === Gauss-Laguerre ===

    GaussWeights get_laguerre_weights(int n){
        // https://mathworld.wolfram.com/Laguerre-GaussQuadrature.html
        switch (n)
        {
        case 2:
            return {{0.585786, 3.41421}, {0.853553, 0.146447}};
        case 3:
            return {{0.415775, 2.29428, 6.28995}, {0.711093, 0.278518, 0.0103893}};
        case 4:
            return {{0.322548, 1.74576, 4.53662, 9.39507}, {0.603154, 0.357419, 0.0388879, 0.000539295}};
        default:
            return {};
        }
    }

    double gauss_laguerre(int n, NumFunc f){
        GaussWeights points = get_laguerre_weights(n);
        return sum_gauss(points, n, f);
    }

    // === Gauss-Chebyshev ===

    GaussWeights get_chebyshev_weights(int n){
        // https://mathworld.wolfram.com/Chebyshev-GaussQuadrature.html
        switch (n)
        {
        case 2:
            return {{-0.707107, 0.707107}, {1.5708, 1.5708}};
        case 3:
            return {{-0.866025, 0, 0.866025}, {1.0472, 1.0472, 1.0472}};
        case 4:
            return {{-0.92388, -0.382683, 0.382683, 0.92388}, {0.785398, 0.785398, 0.785398, 0.785398}};
        default:
            return {};
        }
    }

    double gauss_chebyshev(int n, NumFunc f){
        GaussWeights points = get_chebyshev_weights(n);
        return sum_gauss(points, n, f);
    }


    // === Exponencial ===
    // Serve pra resolver integral com singularidade nos limites

    double exp_integrate(double a, double b, double c, NumFunc f, NumFunc x, NumFunc dx){
        return closed_newton_cotes(-c, c, 10, 4, [f, x, dx](double s){
            return f(x(s))*dx(s);
        });
    }

    double exp_integral(double a, double b, double epsilon_C, NumFunc f, NumFunc x, NumFunc dx){
        double C = 1;
        double E = 1;
        double delta_C = 0.1;
        double I_old = 0;

        while (E > epsilon_C){
            C += delta_C;
            double I_new = exp_integrate(a, b, C, f, x, dx);
            E = abs((I_new - I_old)/I_new);
            I_old = I_new;
        }

        return I_old;
    }

    double simple_exponential_integration(double a, double b, double epsilon_C, NumFunc f){
        return exp_integral(a, b, epsilon_C, f,
            [a, b](double s){
                return (a+b)/2 + ((b-a)/2)*tanh(s);
            },
            [a, b](double s){
                return ((b-a)/2)*(1/pow(cosh(s), 2));
            }
        );
    }

    double double_exponential_integration(double a, double b, double epsilon_C, NumFunc f){
        return exp_integral(a, b, epsilon_C, f,
            [a, b](double s){
                return (a+b)/2 + ((b-a)/2)*tanh((PI/2)*sinh(s));
            },
            [a, b](double s){
                return ((b-a)/2)*((PI/2)*(cosh(s)/pow(cosh((PI/2)*sinh(s)), 2)));
            }
        );
    }

    // === Integral de área ===
    double integrate_area_square_legendre(double a, double b, NumFunc2 f, NumFunc2 dxdf, NumFunc2 dydf, int n){
        NumFunc2 x_ab = [a](double r, double s){
            return a*r;
        };
        NumFunc2 y_ab = [b](double r, double s){
            return b*s;
        };

        double jacobi = a*b;

        GaussWeights legendre_ws = get_legendre_weights(n);

        double sum = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                sum += (
                    legendre_ws.second.at(i)*legendre_ws.second.at(j) *
                    sqrt(
                        pow(dxdf(x_ab(legendre_ws.first.at(i), legendre_ws.first.at(j)), y_ab(legendre_ws.first.at(i), legendre_ws.first.at(j))), 2) +
                        pow(dydf(x_ab(legendre_ws.first.at(i), legendre_ws.first.at(j)), y_ab(legendre_ws.first.at(i), legendre_ws.first.at(j))), 2) +
                        1
                    )
                );
            }
        }

        return sum * jacobi;
    }

    // a: "largura máxima" da elipse; b: "altura máxima" da elipse
    double integrate_area_ellipse_legendre(double a, double b, NumFunc2 f, NumFunc2 dxdf, NumFunc2 dydf, int n){
        // Mudança de variável da elipse
        NumFunc g = [a, b](double x){
            return sqrt((1-pow(x/a, 2))*pow(b, 2));
        };
        NumFunc dg = [a, b](double x){
            return -((pow(b, 2)*x)/(pow(a, 2)*sqrt(pow(b, 2)*(1-pow(x/a, 2)))));
        };

        // Mudança de variável pro método de gauss legendre
        NumFunc2 x_ab = [a](double r, double s){
            return a*r;
        };
        NumFunc2 y_ab = [x_ab, g](double r, double s){
            return s*g(x_ab(r, s));
        };

        NumFunc2 jacobi = [a, g, x_ab](double r, double s){
            return a*g(x_ab(r, s));
        };

        GaussWeights legendre_ws = get_legendre_weights(n);

        double sum = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                double jacobi_i = jacobi(legendre_ws.first.at(i), legendre_ws.first.at(j));
                sum += (
                    legendre_ws.second.at(i)*legendre_ws.second.at(j) *
                    sqrt(
                        pow(dxdf(x_ab(legendre_ws.first.at(i), legendre_ws.first.at(j)), y_ab(legendre_ws.first.at(i), legendre_ws.first.at(j))), 2) +
                        pow(dydf(x_ab(legendre_ws.first.at(i), legendre_ws.first.at(j)), y_ab(legendre_ws.first.at(i), legendre_ws.first.at(j))), 2) +
                        1
                    ) * jacobi_i
                );
            }
        }

        return sum;
    };

    // === Integral de volume ===

    double integrate_volume_ellipse_legendre();
}

#endif