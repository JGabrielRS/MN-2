#ifndef PROCESSAMENTO_IMAGEM
#define PROCESSAMENTO_IMAGEM

#include "filtro_gradiente.h"
#include "filtro_gaussiano.h"
#include "filtro_laplaciano.h"

namespace processamento_imagem {
    using namespace Vec;
    
    void processamento_imagem_Alg1(const char* imagem, int &w, int &h){
        int channels;
        
        VecDouble img = filtro_gaussiano::filtro_gaussiano(imagem, w, h);

        VecDouble imgA = filtro_gradiente::filtro_sobel_A("src/processamento_imagem/imagem_filtro_gaussiano.png", w, h);
        VecDouble imgB = filtro_gradiente::filtro_sobel_B("src/processamento_imagem/imagem_filtro_gaussiano.png", w, h);

        for (int i = 0; i < imgA.size(); ++i){
            imgA.at(i) = std::pow(imgA.at(i),2);
            imgB.at(i) = std::pow(imgB.at(i),2);
        }

        VecDouble imgC(imgA.size(),0);
        
        for (int i = 0; i < imgC.size(); ++i){
            double soma = imgA.at(i) + imgB.at(i);
            imgC.at(i) = std::sqrt(soma);
        }

        double threshold = 10.0;

        VecDouble imgD(imgC.size(), 0);

        for (int i = 0; i < imgD.size(); ++i){
            if (imgC.at(i) > threshold){
                imgD.at(i) = 1.0;
            } else {
                imgD.at(i) = 0.0;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(imgD.size(), 0);
        for(int i = 0; i < imgD.size(); ++i) {
            // Garante que valores fiquem estritamente entre 0 e 255 antes de converter
            double val = imgD[i] * 255.0;
            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/processamento_imagem_Alg1.png", w, h, 1, img_out_bytes.data(), w);
    }

    void processamento_imagem_Alg2(const char* imagem, int &w, int &h){
        int channels;
        
        VecDouble img = filtro_gaussiano::filtro_gaussiano(imagem, w, h);

        VecDouble imgA = filtro_laplaciano::filtro_laplace("src/processamento_imagem/imagem_filtro_gaussiano.png", w, h);
        VecDouble imgB(imgA.size(),0);

        double tolerancia = 0.0001;

        for (int i = 0; i < imgB.size(); ++i){
            if (std::abs(imgA.at(i)) > tolerancia){
                imgB.at(i) = 1.0;
            } else {
                imgB.at(i) = 0.0;
            }
        }

        std::vector<unsigned char> img_out_bytes(imgB.size(), 0);
        for(int i = 0; i < imgB.size(); ++i) {
            double val = imgB[i] * 255.0;
            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/processamento_imagem_Alg2.png", w, h, 1, img_out_bytes.data(), w);
    }
}

#endif //PROCESSAMENTO_IMAGEM