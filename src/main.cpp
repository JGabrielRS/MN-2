#include "matrix/matrix.h"
#include "processamento_imagem/filtro_gradiente.h"
#include "vec/vec.h"
#include "eigenvalues.h"
#include "qrmethod.h"
#include "svddecomposition.h"
#include "finitedifference.h"
#include "linearsystem.h"
#include "rungekuttaO4.h"
#include "derivation.h"
#include "integration.h"
#include "processamento_imagem/filtro_gaussiano.h"
#include "processamento_imagem/processamento_imagem.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "processamento_imagem/stb_image.h"
#include "processamento_imagem/stb_image_write.h"

using namespace std;
using namespace Vec;
using namespace Mat;

void unidade01(){
    //cout<< derivation::derivada_foward(2, 0.001) << endl;
    int w = 452;
    int h = 678;
    //filtro_gaussiano::filtro_gaussiano("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel_A("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel_B("src/processamento_imagem/kanye.jpg", w, h);
    processamento_imagem::processamento_imagem_Alg1("src/processamento_imagem/kanye.jpg", w, h);
    processamento_imagem::processamento_imagem_Alg2("src/processamento_imagem/kanye.jpg", w, h);
}

void unidade02(){
    cout << "Integral de exp(x) de -3 a 3" << endl;
    double a = -3;
    double b = 3;
    double correct = exp(b) - exp(a);

    integration::NumFunc exp_f = [](double x){
        return exp(x);
    };

    cout << integration::open_newton_cotes(a, b, 10, 2, exp_f) << endl;
    cout << integration::closed_newton_cotes(a, b, 10, 2, exp_f) << endl;
    cout << integration::gauss_legendre(a, b, 4, exp_f) << endl;
    cout << "Valor real: " << correct << endl;

    cout << "------------------" << endl;

    cout << "Integral de 1/sqrt(x) de 0 a 1, que tem 0 como singularidade" << endl;
    integration::NumFunc sing_f = [](double x){
        return 1/sqrt(x);
    };

    cout << integration::simple_exponential_integration(0, 1, 0.0001, sing_f) << endl;
    cout << integration::double_exponential_integration(0, 1, 0.0001, sing_f) << endl;
    cout << "Valor real: " << 2 << endl;

    cout << "------------------" << endl;

    cout << integration::gauss_hermite(2, exp_f) << endl;
    cout << integration::gauss_laguerre(2, exp_f) << endl;
    cout << integration::gauss_chebyshev(2, exp_f) << endl;

    cout << "------------------" << endl;

    // Atividade da aula 15
    cout << "Atividade da aula 15: " << endl;
    cout << integration::integrate_area_ellipse_legendre(40, 40, 
        [](double x, double y){ return 0.2*(pow(x,2)-pow(y,2)); },
        [](double x, double y){ return 0.4*x; },
        [](double x, double y){ return -0.4*y; }, 3
    ) << " metros quadrados" << endl;

    // Atividade da aula 16
    cout << "Atividade da aula 16: " << endl;
    cout << integration::integrate_volume_ellipse_legendre(40, 20, 
        [](double x, double y){ return 0.2*(pow(x,2)-pow(y,2)); },
        [](double x, double y){ return 0.4*x; },
        [](double x, double y){ return -0.4*y; }, 3
    ) << " metros cubicos" << endl;
}

void unidade03(){
    
}

void unidade04(){
    
}

void unidade05(){
    // N é 20 para que delta seja 0.1: (b-a)/N = 0.1 -> (2-0/N) = 0.1 -> N = 20
    VecDouble res = finite_difference::finite_differente_order2(0, 2, 10, 1, 20, 1, 7, -1);
    
    VecDouble points;
    for(int i = 0; i <= 20; i++){
        points.push_back(0.1*i);
    }

    print_vec(res);
    print_vec(points);
}

int main(){
    cout << setprecision(15);

    unidade02();
}