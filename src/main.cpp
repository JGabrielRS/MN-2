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
#include "processamento_imagem/filtro_gaussiano.h"
#include "processamento_imagem/processamento_imagem.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "processamento_imagem/stb_image.h"
#include "processamento_imagem/stb_image_write.h"

int main(){
    //std::cout<< derivartion::derivada_foward(2, 0.001) << std::endl;
    int w = 452;
    int h = 678;
    //filtro_gaussiano::filtro_gaussiano("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel_A("src/processamento_imagem/kanye.jpg", w, h);
    //filtro_gradiente::filtro_sobel_B("src/processamento_imagem/kanye.jpg", w, h);
    processamento_imagem::processamento_imagem_Alg1("src/processamento_imagem/kanye.jpg", w, h);
    processamento_imagem::processamento_imagem_Alg2("src/processamento_imagem/kanye.jpg", w, h);
    return 0;
}