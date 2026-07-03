#ifndef MN_MATRIX_H
#define MN_MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "../vec/vec.h"


namespace Mat{
    using namespace std;
    using namespace Vec;

    class Matrix {
        public:
            Matrix(int s);
            Matrix(int s, int t);
            // Copia todo o vetor de entrada
            Matrix(vector<VecDouble> matrix_);
    
            Matrix();

            void switch_row(int x, int y);
    
            static Matrix get_indentity(int n);
            static Matrix from_vector(VecDouble vec);
            static VecDouble to_vector(Matrix m);
    
            pair<int, int> get_size();
    
            double at(int x, int y);
            void set(int x, int y, double val);
            void resize(int x, int y);
            Matrix get_transposed();
            Matrix get_inverse();
    
            void print(int precision = 3, int spacing = 8);
            void print_latex(int precision = 3);
    
        protected:
            vector <VecDouble> matrix;
            pair<int, int> matrix_size;
    
    };
    
    Matrix operator-(Matrix &m1, Matrix &m2);
    Matrix operator*(Matrix &m1, double val);
    Matrix operator*(Matrix &m1, Matrix &m2);
    Matrix operator*(Matrix &m, VecDouble &v);
};


#endif // MN_MATRIX_H