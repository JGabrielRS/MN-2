#ifndef INTEGRATION
#define INTEGRATION

#include <math.h>
#include <iostream>
#include <vector>

namespace integration {
    using namespace std;
    typedef pair<vector<double>, double> CotesWeight;

    double f(double x){
        return exp(x);
        
        // pro gauss hermite
        // return exp(-pow(x, 2));
    }

    // === Newton-Cotes Fechado ===
    
    double integrate_cotes(double x0, double xf, int p, CotesWeight& points){
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
    
    double closed_newton_cotes(double a, double b, double n, int p){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_closed_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate_cotes(xi, xf, p, points);
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

    double open_newton_cotes(double a, double b, double n, int p){
        double delta = (b - a)/n;
        double as = 0;

        CotesWeight points = get_open_cotes_weigth(p);

        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate_cotes(xi, xf, p+1, points);
        }
        return as;
    }

    // === Gauss-Legendre ===
    typedef pair<vector<double>, vector<double>> GaussWeights;

    GaussWeights get_legendre_weights(int n){
        double p1, p2, w1, w2;
        switch (n)
        {
        case 1:
            return {{0}, {2}};
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

    double gauss_legendre(double a, double b, int n){
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
        double p1, p2, w1, w2;
        switch (n)
        {
        case 1:
            return {{0}, {1.77245}};
        case 2:
            p1 = 0.707107;
            return {{-p1, p1}, {1.46114, 1.46114}};
        case 3:
            p1 = 1.22474;
            return {{-p1, 0, p1}, {1.32393, 1.18164, 1.32393}};
        case 4:
            p1 = 1.65068;
            p2 = 0.524648;
            w1 = 1.24023;
            w2 = 1.05996;
            return {{-p1, -p2, p2, p1}, {w1, w2, w2, w1}};
        default:
            return {};
        }
    }

    double gauss_hermite(int n){
        GaussWeights points = get_hermite_weights(n);

        double sum = 0;
        for(int i = 0; i < n; i++){
            sum += f(points.first.at(i))*points.second.at(i);
        }

        return sum;
    }
}

#endif