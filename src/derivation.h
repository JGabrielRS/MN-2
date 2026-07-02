#ifndef DERIVATION
#define DERIVATION

#include <math.h>

namespace derivartion{
    using namespace std;
    double f(double x){
        return pow((sin(2*x) + 4*pow(x, 2) + 3*x), 2);
    }

    // derivadas foward
    double derivada_foward(double x, double delta){
        return (f(x+delta)-f(x))/delta;
    }

    double derivada_foward_erroO2(double x, double delta){
        return (-f(x+2*delta)+4*(f(x+delta))-3*(f(x)))/(2*delta);
    }

    double derivada_foward_erroO3(double x, double delta){
        return (2*f(x+3*delta)-9*f(x+2*delta)+18*f(x+delta)-11*f(x))/(6*delta);
    }
        

    double derivada_foward_segundaOrdem(double x, double delta){
        return (f(x+2*delta)-2*f(x+delta)+f(x))/(std::pow(delta, 2));
    }
        

    double derivada_foward_terceiraOrdem(double x, double delta){
        return (f(x+3*delta)-3*f(x+2*delta)+3*f(x+delta)-f(x))/(std::pow(delta, 3));
    }
        

    // derivadas backward
    double derivada_backward(double x, double delta){
        return (f(x)-f(x-delta))/delta;
    }
        

    double derivada_backward_erroO2(double x, double delta){
        return (3*f(x)-4*f(x-delta)+f(x-2*delta))/(2*delta);
    }
        

    double derivada_backward_erroO3(double x, double delta){
        return (11*f(x)-18*f(x-delta)+9*f(x-2*delta)-2*f(x-3*delta))/(6*delta);
    }
        

    double derivada_backward_segundaOrdem(double x, double delta){
        return (f(x)-2*f(x-delta)+f(x-2*delta))/(std::pow(delta, 2));
    }
        

    // derivadas central
    double derivada_central_erroO2(double x, double delta){
        return (f(x+delta)-f(x-delta))/(2*delta);
    }
        

    double derivada_central_erroO3(double x, double delta){
        return (-f(x+2*delta)+8*f(x+delta)-8*f(x-delta)+f(x-2*delta))/(12*delta);
    }
        

    double derivada_central_segundaOrdem(double x, double delta){
        return (f(x+2*delta)-2*f(x)+f(x-2*delta))/(4*(std::pow(delta, 2)));
    }
        
}

#endif