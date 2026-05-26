#ifndef INTEGRATION
#define INTEGRATION

#include <math.h>
#include <iostream>
#include <vector>

namespace integration {
    using namespace std;
    double f(double x){
        return pow((sin(2*x) + 4*pow(x, 2) + 3*x), 2);
    }

    double x(double xi, int i, double delta){
        return xi + i*delta;
    }

    typedef pair<vector<double>, double> CotesWeight;
    pair<vector<double>, double> get_cotes_weigth(int p){
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
        default:
            return {};
            break;
        }
    }

    double integrate(double x0, double xf, int p){
        CotesWeight points = get_cotes_weigth(p);
        double delta = (xf - x0)/p;

        double sumn = 0;
        for(int i = 0; i < points.first.size(); i++){
            double xi = x0 + delta*i;
            sumn+=points.first.at(i)*f(xi);
        }

        return (delta*points.second)*sumn;
    }
    
    double newton_cotes(int a, int b, double n, int p){
        double delta = (b - a)/n;
        double as = 0;
        for (int i = 0; i < n; i++){
            double xi = a + i * delta;
            double xf = xi + delta;
            as += integrate(xi, xf, p);
        }
        return as;
    }
}

int main(){
    double result = integration::newton_cotes(0, 1, 1, 3);
    std::cout << result;
    
    return 0;
}

#endif