#ifndef FILTRO_GAUSSIANO
#define FILTRO_GAUSSIANO

#include <iostream>
#include <vector>
#include <cmath>
#include "../matrix/matrix.h"

#include "stb_image.h"
#include "stb_image_write.h"

namespace filtro_gaussiano {
    using namespace Vec;
    
    VecDouble filtro_gaussiano(const char* imagem, int &w, int &h) {
        int channels;
        unsigned char* img = stbi_load(imagem, &w, &h, &channels, 1);
        
        if (img == nullptr){
            std::cout<<"Erro ao carregar a imagem"<<std::endl; 
        }
        VecDouble output(w*h,0);
        
        double GKernel[5][5];
        double sigma = 1.8;
        double r, s = 2.0 * sigma * sigma;
        double sum = 0.0;

        for (int x = -2; x <= 2; x++) {
            for (int y = -2; y <= 2; y++) {
                double r = sqrt(x * x + y * y);
                GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
                sum += GKernel[x + 2][y + 2];
            }
        }

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                GKernel[i][j] /= sum;
            }
        }

        for (int y = 2; y < h - 2; ++y) {
            for (int x = 2; x < w - 2; ++x) {
                
                double pixelSum = 0.0;

                for (int ky = -2; ky <= 2; ++ky) {
                    for (int kx = -2; kx <= 2; ++kx) {
                        int pixel = img[(y + ky) * w + (x + kx)];
                        pixelSum += pixel * GKernel[ky + 2][kx + 2];
                    }
                }
                
                output[y * w + x] = pixelSum;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(w * h, 0);
        for(int i = 0; i < w * h; ++i) {
            // Garante que valores fiquem estritamente entre 0 e 255 antes de converter
            double val = output[i];
            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }

        stbi_write_png("src/processamento_imagem/imagem_filtro_gaussiano.png", w, h, 1, img_out_bytes.data(), w);
        
        stbi_image_free(img);
        return output;
    }
}

#endif //FILTRO_GAUSSIANO