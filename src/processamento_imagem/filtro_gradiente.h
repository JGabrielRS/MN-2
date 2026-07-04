#ifndef FILTRO_GRADIENTE
#define FILTRO_GRADIENTE

#include <iostream>
#include <vector>
#include <cmath>
#include "../matrix/matrix.h"
#include "../derivation.h"

#include "stb_image.h"
#include "stb_image_write.h"

namespace filtro_gradiente {
    using namespace Vec;
    
    VecDouble filtro_sobel(const char* imagem, int &w, int &h) {
        int channels;
        unsigned char* img = stbi_load(imagem, &w, &h, &channels, 1);
        
        if (img == nullptr){
            std::cout << "Erro ao carregar a imagem" << std::endl; 
            return {};
        }
        
        VecDouble output(w * h, 0);
        
        double Kx[3][3] = {
            {-1.0,  0.0,  1.0},
            {-2.0,  0.0,  2.0},
            {-1.0,  0.0,  1.0}
        };

        double Ky[3][3] = {
            {-1.0, -2.0, -1.0},
            { 0.0,  0.0,  0.0},
            { 1.0,  2.0,  1.0}
        };

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                
                double Gx = 0.0;
                double Gy = 0.0;

                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int pixel = img[(y + ky) * w + (x + kx)];
                        
                        Gx += pixel * Kx[ky + 1][kx + 1];
                        Gy += pixel * Ky[ky + 1][kx + 1];
                    }
                }
                
                double magnitude = std::sqrt((Gx * Gx) + (Gy * Gy));
                output[y * w + x] = magnitude;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(w * h, 0);
        for(int i = 0; i < w * h; ++i) {
            double val = output[i];

            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/imagem_gradiente_sobel.png", w, h, 1, img_out_bytes.data(), w);
        
        stbi_image_free(img);
        return output;
    }

    VecDouble filtro_sobel_A(const char* imagem, int &w, int &h) {
        int channels;
        unsigned char* img = stbi_load(imagem, &w, &h, &channels, 1);
        
        if (img == nullptr){
            std::cout << "Erro ao carregar a imagem" << std::endl; 
            return {};
        }
        
        VecDouble output(w * h, 0);

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                
                double Gx = 0.0;

                double derivada = derivation::derivada_central_erroO2_X(img, x, y, w);
                
                output[y * w + x] = derivada;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(w * h, 0);
        for(int i = 0; i < w * h; ++i) {
            double val = std::abs(output[i]);;

            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/imagem_gradiente_sobel_A.png", w, h, 1, img_out_bytes.data(), w);
        
        stbi_image_free(img);
        return output;
    }

    VecDouble filtro_sobel_B(const char* imagem, int &w, int &h) {
        int channels;
        unsigned char* img = stbi_load(imagem, &w, &h, &channels, 1);
        
        if (img == nullptr){
            std::cout << "Erro ao carregar a imagem" << std::endl; 
            return {};
        }
        
        VecDouble output(w * h, 0);
        
        double Ky[3][3] = {
            {-1.0,  0.0,  1.0},
            {-2.0,  0.0,  2.0},
            {-1.0,  0.0,  1.0}
        };

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                
                double Gx = 0.0;

                double derivada = derivation::derivada_central_erroO2_Y(img, x, y, w);
                
                output[y * w + x] = derivada;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(w * h, 0);
        for(int i = 0; i < w * h; ++i) {
            double val = std::abs(output[i]);;

            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/imagem_gradiente_sobel_B.png", w, h, 1, img_out_bytes.data(), w);
        
        stbi_image_free(img);
        return output;
    }
}

#endif //FILTRO_GRADIENTE