#include "vec.h"

namespace Vec{
    VecDouble operator-(VecDouble &v1, VecDouble &v2){
        VecDouble result;
        // TODO dar erro se tamanho for diferente
        for(size_t i = 0; i < v1.size(); i++){
            result.push_back(v1.at(i) - v2.at(i));
        }
        return result;
    }
    
    double vec_length(VecDouble &vec){
        double length = 0;
        for(size_t k = 0; k < vec.size(); k++){
            length+=pow(vec.at(k), 2);
        }
        return sqrt(length);
    }
    
    VecDouble vec_normalize(VecDouble &vec){
        VecDouble result;
        double length = vec_length(vec);
        
        for(size_t i = 0; i < vec.size(); i++){
            // HACK não sei se isso é o ideal, mas tem que fazer algo nesse caso
            if(length == 0) result.push_back(0); 
            else result.push_back(vec.at(i)/length);
        }
        return result;
    }
    
    void print_vec(VecDouble &vec){
        cout << "( ";
        for(size_t i = 0; i < vec.size(); i++){
            cout << vec.at(i) << " ";
        }
        cout << ")" << endl;
    }

    void print_vec_latex(VecDouble &vec){
        cout << "\\begin{pmatrix}";
        for(size_t i = 0; i < vec.size(); i++){
            cout << vec.at(i);
            if(i != vec.size()-1)  cout << " \\\\ ";
        }
        cout << "\\end{pmatrix}" << endl;
    }
}
