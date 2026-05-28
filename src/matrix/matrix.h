#ifndef MN_MATRIX_H
#define MN_MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "../vec/vec.h"


namespace Mat{
    using namespace std;

    class Matrix {
        public:
            Matrix(int s);
            Matrix(int s, int t);
            // Copia todo o vetor de entrada
            Matrix(vector <vector <double>> matrix_);
    
            Matrix();

            void switch_row(int x, int y);
    
            static Matrix get_indentity(int n);
            static Matrix from_vector(Vec::VecDouble vec);
    
            pair<int, int> get_size();
    
            double at(int x, int y);
            void set(int x, int y, double val);
            void resize(int x, int y);
            Matrix get_transposed();
    
            void print(int precision = 3, int spacing = 8);
    
        protected:
            vector <vector <double>> matrix;
            pair<int, int> matrix_size;
    
    };
    
    Matrix operator-(Matrix &m1, Matrix &m2);
    Matrix operator*(Matrix &m1, double val);
    Matrix operator*(Matrix &m1, Matrix &m2);
};


#endif // MN_MATRIX_H