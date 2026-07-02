#ifndef INTEGRATION
#define INTEGRATION

#include <math.h>
#include <iostream>
#include <vector>

namespace integration {
    using namespace std;
    typedef pair<vector<double>, double> CotesWeight;

    double f(double x){
        return pow(x, 2);
    }

    double x(double xi, int i, double delta){
        return xi + i*delta;
    }

    CotesWeight get_closed_cotes_weigth(int p){
        switch (p)
        {
        case 1:
            return {{1, 1}, 1.0f/2};
            break;
        case 2:
            return {{1, 4, 1}, 1.0f/3};
            break;
        case 3:
            return {{1, 3, 3, 1}, 3.0f/8};
            break;
        case 4:
            return {{7, 32, 12, 32, 7}, 2.0f/45};
            break;
        default:
            return {};
            break;
        }
    }

    double integrate(double x0, double xf, int p, CotesWeight& points){
        double delta = (xf - x0)/p;

        double sumn = 0;
        for(int i = 0; i < points.first.size(); i++){
            double xi = x0 + delta*i;
            sumn+=points.first.at(i)*f(xi);
        }

        return (delta*points.second)*sumn;
    }
    
    double closed_newton_cotes(int a, int b, double n, int p){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_closed_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate(xi, xf, p, points);
        }
        return as;
    }

    CotesWeight get_open_cotes_weigth(int p){
        switch (p)
        {
        case 1:
            return {{0, 1}, 2.0f};
            break;
        case 2:
            return {{0, 1, 1}, 3.0f/2};
            break;
        case 3:
            return {{0, 2, -1, 2}, 4.0f/3};
            break;
        case 4:
            return {{0, 11, 1, 1, 11}, 5.0f/24};
            break;
        default:
            return {};
            break;
        }
    } 

    double open_newton_cotes(int a, int b, double n, int p){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_open_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate(xi, xf, p+1, points);
        }
        return as;
    }
}

#endif