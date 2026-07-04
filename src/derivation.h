#ifndef DERIVATION
#define DERIVATION

#include <math.h>

namespace derivation{
    using namespace std;
    double f(double x){
        return pow((sin(2*x) + 4*pow(x, 2) + 3*x), 2);
    }

    // derivadas foward
    double derivada_foward(double x, double delta){
        return (f(x+delta)-f(x))/delta;
    }

    double derivada_foward(unsigned char* img, int x, int y, int w){
        return static_cast<double>(img[y*w+(x+1)]-img[y*w+x]);
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
     
    double derivada_foward_segundaOrdem_erroO2(double x, double delta){
        return (2*f(x)-5*f(x+delta)+4*f(x+2*delta)-f(x+3*delta))/std::pow(delta, 2);
    }

    double derivada_foward_segundaOrdem_erroO3(double x, double delta){
        return (35*f(x)-104*f(x+delta)+114*f(x+2*delta)-56*f(x+3*delta)+11*f(delta+4*delta))/(12*std::pow(delta,2));
    }

    double derivada_foward_terceiraOrdem(double x, double delta){
        return (f(x+3*delta)-3*f(x+2*delta)+3*f(x+delta)-f(x))/(std::pow(delta, 3));
    }
    
    double derivada_foward_terceiraOrdem_erroO2(double x, double delta){
        return (-2.5*f(x)+9*f(x+delta)-12*f(x+2*delta)+7*f(x+3*delta)-1.5*f(x+4*delta))/std::pow(delta,3);
    }

    double derivada_foward_terceiraOrdem_erroO3(double x, double delta){
        return (-23*f(x)+95*f(x+delta)-154*f(x+2*delta)+122*f(x+3*delta)-47*f(x+4*delta)+7*f(x+5*delta))/(4*std::pow(delta, 3));
    }

    // derivadas backward
    double derivada_backward(double x, double delta){
        return (f(x)-f(x-delta))/delta;
    }

    double derivada_backward(unsigned char* img, int x, int y, int w){
        return static_cast<double>(img[y*w+x]-img[y*w+(x-1)]);
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

    double derivada_backward_segundaOrdem_erroO2(double x, double delta){
        return (2*f(x)-5*f(x-delta)+4*f(x-2*delta)-f(x-3*delta))/std::pow(delta, 2);
    }   

    double derivada_backward_segundaOrdem_erroO3(double x, double delta){
        return (35*f(x)-104*f(x-delta)+114*f(x-2*delta)-56*f(x-3*delta)+11*f(x-4*delta))/(12*std::pow(delta, 2));
    }

    double derivada_backward_terceiraOrdem(double x, double delta){
        return (-f(x-3*delta)+3*f(x-2*delta)-3*f(x-delta)+f(x))/std::pow(delta, 3);
    }

    double derivada_backward_terceiraOrdem_erroO2(double x, double delta){
        return (2.5*f(x)-9*f(x-delta)+12*f(x-2*delta)-7*f(x-3*delta)+1.5*f(x-4*delta))/std::pow(delta, 3);
    }

    double derivada_backward_terceiraOrdem_erroO3(double x, double delta){
        return (23*f(x)-95*f(x-delta)+154*f(x-2*delta)-122*f(x-3*delta)+47*f(x-4*delta)-7*f(x-5*delta))/(4*std::pow(delta, 3));
    }

    // derivadas central
    double derivada_central(double x, double delta){
        return (f(x+0.5*delta)-f(x-0.5*delta))/delta;
    }

    double derivada_central_erroO2(double x, double delta){
        return (f(x+delta)-f(x-delta))/(2*delta);
    }

    double derivada_central_erroO2_X(unsigned char* img, int x, int y, int w){
        return static_cast<double>(img[y*w+(x+1)]-img[y*w+(x-1)])/2.0;
    }

    double derivada_central_erroO2_Y(unsigned char* img, int x, int y, int w) {
    return static_cast<double>(img[(y + 1) * w + x] - img[(y - 1) * w + x]) / 2.0;
}

    double derivada_central_erroO3(double x, double delta){
        return (-f(x+2*delta)+8*f(x+delta)-8*f(x-delta)+f(x-2*delta))/(12*delta);
    }

    double derivada_central_segundaOrdem(double x, double delta){
        return (f(x+2*delta)-2*f(x)+f(x-2*delta))/(4*(std::pow(delta, 2)));
    }

    double derivada_central_segundaOrdem_erroO2(double x, double delta){
        return (f(x+delta)-2*f(x)+f(x-delta))/std::pow(delta, 2);
    }
        
    double derivada_central_segundaOrdem_erroO3(double x, double delta){
        return (f(x-delta)-2*f(x)+f(x+delta))/std::pow(delta, 2);
    }

    double derivada_central_terceiraOrdem(double x, double delta){
        return (f(x+2*delta)-2*f(x+delta)+2*f(x-delta)-f(x-2*delta))/(2*delta);
    }

    double derivada_central_terceiraOrdem_erroO2(double x, double delta){
        return (f(x+2*delta)-2*f(x+delta)+2*f(x-delta)-f(x-2*delta))/(2*std::pow(delta, 3));
    }

    double derivada_central_terceiraOrdem_erroO3(double x, double delta){
        return (-11*f(x-2.5*delta)+35*f(x-1.5*delta)-38*f(x-0.5*delta)+14*f(x+0.5*delta)+f(x+1.5*delta)-f(x+2.5*delta))/(8*std::pow(delta, 3));
    }

}

#endif