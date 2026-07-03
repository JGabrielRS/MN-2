#ifndef FILTRO_LAPLACIANO
#define FILTRO_LAPLACIANO

#include <iostream>
#include <vector>
#include <cmath>
#include "../matrix/matrix.h"

#include "stb_image.h"
#include "stb_image_write.h"

namespace filtro_laplaciano {
    using namespace Vec;
    
    VecDouble filtro_laplace(const char* imagem, int &w, int &h) {
        int channels;
        unsigned char* img = stbi_load(imagem, &w, &h, &channels, 1);
        
        if (img == nullptr){
            std::cout << "Erro ao carregar a imagem no Laplaciano" << std::endl; 
            return {};
        }
        
        VecDouble output_A(w * h, 0);
        
        double Klaplace[3][3] = {
            { 1.0,  1.0,  1.0},
            { 1.0, -8.0,  1.0},
            { 1.0,  1.0,  1.0}
        };

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                
                double soma_laplace = 0.0;

                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int pixel = img[(y + ky) * w + (x + kx)];
                        soma_laplace += pixel * Klaplace[ky + 1][kx + 1];
                    }
                }
                
                output_A[y * w + x] = soma_laplace;
            }
        }
        
        std::vector<unsigned char> img_out_bytes(w * h, 0);
        for(int i = 0; i < w * h; ++i) {
            double val = std::abs(output_A[i]);
            if (val > 255.0) val = 255.0;
            if (val < 0.0) val = 0.0;
            img_out_bytes[i] = static_cast<unsigned char>(val);
        }
        stbi_write_png("src/processamento_imagem/imagem_laplaciano_A.png", w, h, 1, img_out_bytes.data(), w);
        
        stbi_image_free(img);
        return output_A;
    }
}

#endif //FILTRO_LAPLACIANO