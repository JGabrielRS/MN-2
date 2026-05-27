#include "matrix.h"

namespace Mat{
    Matrix::Matrix(int s){
        matrix = vector<vector<double>>(s+1, vector<double>(s+1));
        matrix_size = {s, s};
    }
    Matrix::Matrix(int s, int t){
        matrix = vector<vector<double>>(s+1, vector<double>(t+1));
        matrix_size = {s, t};
    }
    Matrix::Matrix(vector<vector<double>> matrix_){
        matrix = matrix_;
    
        // Assumindo que o vetor recebido é uma matriz, obviamente
        matrix_size = {matrix.size(), matrix.at(0).size()};
    }
    
    Matrix::Matrix(){
        matrix = vector<vector<double>>();
        matrix_size = {0, 0};
    }
    
    Matrix Matrix::get_indentity(int n){
        Matrix matrix{n};
        for(int i = 0; i < n; i++){
            matrix.set(i, i, 1);
        }
        return matrix;
    }
    
    Matrix Matrix::from_vector(VecDouble vec){
        Matrix m{};
        m.resize(1, vec.size());
        m.set(0, 0, 1);
        for(int i = 0; i < vec.size(); i++){
            m.set(0,i, vec.at(i));
        }
        return m;
    }
    
    // first: linhas
    // second: colunas
    pair<int, int> Matrix::get_size(){
        return matrix_size;
    }
    
    void Matrix::set(int x, int y, double val){
        matrix.at(x).at(y) = val;
    }
    
    void Matrix::resize(int x, int y){
        matrix.resize(x);
        for(int i = 0; i < matrix.size(); i++){
            matrix.at(i).resize(y);
        }
        matrix_size = {x, y};
    }
    
    Matrix Matrix::get_transposed(){
        Matrix m{max(get_size().first, get_size().second)};
        for(int x = 0; x < get_size().first; x++){
            for(int y = 0; y < get_size().second; y++){
                m.set(y, x, at(x, y));
            }
        }
        m.resize(get_size().second, get_size().first);
        return m;
    }
    
    double Matrix::at(int x, int y){
        return matrix.at(x).at(y);
    }
    
    void Matrix::print() {
        cout << fixed << setprecision(PRINT_PRECISION_MATRIX);
        for (int i = 0; i < matrix_size.first; i++) {
            cout << "[";
            for (int j = 0; j < matrix_size.second; j++) {
                cout << setw(PRINT_W_VALUES) << at(i, j) << " "[j == matrix_size.second];
            }
            cout << "  ]" << endl;
        }
    }
    
    Matrix operator-(Matrix &m1, Matrix &m2){
        Matrix m{m1.get_size().first};
        for(int x = 0; x < m1.get_size().first; x++){
            for(int y = 0; y < m1.get_size().first; y++){
                m.set(x, y, m1.at(x,y) - m2.at(x,y));
            }
        }
        return m;
    }
    
    Matrix operator*(Matrix &m1, double val){
        Matrix m{m1.get_size().first};
        for(int x = 0; x < m1.get_size().first; x++){
            for(int y = 0; y < m1.get_size().first; y++){
                m.set(x, y, m1.at(x,y)*val);
            }
        }
        return m;
    }
    
    Matrix operator*(Matrix &m1, Matrix &m2){
        Matrix m{m1.get_size().first};
        // TODO
        return m;
    }
}

