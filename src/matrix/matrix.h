#ifndef MN_MATRIX_H
#define MN_MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "../vec/vec.h"


namespace Mat{
    #define PRINT_PRECISION_MATRIX 3
    #define PRINT_W_VALUES 8

    using namespace std;
    using namespace Vec;

    class Matrix {
        public:
            Matrix(int s);
            Matrix(int s, int t);
            // Copia todo o vetor de entrada
            Matrix(vector <vector <double>> matrix_);
    
            Matrix();
    
            static Matrix get_indentity(int n);
            static Matrix from_vector(VecDouble vec);
    
            pair<int, int> get_size();
    
            double at(int x, int y);
            void set(int x, int y, double val);
            void resize(int x, int y);
            Matrix get_transposed();
    
            void print();
    
        protected:
            vector <vector <double>> matrix;
            pair<int, int> matrix_size;
    
    };
    
    Matrix operator-(Matrix &m1, Matrix &m2);
    Matrix operator*(Matrix &m1, double val);
    Matrix operator*(Matrix &m1, Matrix &m2);
};


#endif // MN_MATRIX_H