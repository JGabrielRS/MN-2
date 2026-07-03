#include "matrix.h"
#include <cstddef>

namespace Mat{
    Matrix::Matrix(int s){
        matrix = vector<VecDouble>(s+1, VecDouble(s+1));
        matrix_size = {s, s};
    }
    Matrix::Matrix(int s, int t){
        // TODO revisar isso, acho que tá errado
        matrix = vector<VecDouble>(s+1, VecDouble(t+1));
        matrix_size = {s, t};
    }
    Matrix::Matrix(vector<VecDouble> matrix_){
        matrix = matrix_;
    
        // Assumindo que o vetor recebido é uma matriz, obviamente
        matrix_size = {matrix.size(), matrix.at(0).size()};
    }
    
    Matrix::Matrix(){
        matrix = vector<VecDouble>();
        matrix_size = {0, 0};
    }

    void Matrix::switch_row(int x, int y){
        size_t c = matrix_size.second;

        Matrix aux(1, c);

        for (size_t i = 0; i < c; i++) {
            aux.set(0, i, at(x, i));
            set(x, i, at(y, i));
            set(y, i, aux.at(0, i));
        }
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
        m.resize(vec.size(), 1);
        for(int i = 0; i < vec.size(); i++){
            m.set(i,0, vec.at(i));
        }
        return m;
    }

    // Supondo que m é uma matriz coluna
    VecDouble Matrix::to_vector(Matrix m){
        VecDouble v{};
        v.resize(m.get_size().first, 1);
        for(int i = 0; i < m.get_size().first; i++){
            v.at(i) = m.at(i, 0);
        }
        return v;
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

    Matrix Matrix::get_inverse(){
        // TODO fazer
    }
    
    double Matrix::at(int x, int y){
        return matrix.at(x).at(y);
    }
    
    void Matrix::print(int precision, int spacing) {
        cout << fixed << setprecision(precision);
        for (int i = 0; i < matrix_size.first; i++) {
            cout << "{";
            for (int j = 0; j < matrix_size.second; j++) {
                double val = at(i, j);
                val = (abs(val) < 1/pow(10, precision+1))?0:val;
                cout << setw(spacing) << val;
                if(j < matrix_size.second-1) cout << "," + (spacing!=0)?" ":"";
            }
            cout << "}";
            if(i < matrix_size.first-1) cout << ",";
            cout << endl;
        }
    }

    void Matrix::print_latex(int precision){
        cout << fixed << setprecision(precision);
        cout << "\\begin{bmatrix}";
        for(int i = 0; i < matrix_size.first; i++){
            for(int j = 0; j< matrix_size.second; j++){
                double val = at(i, j);
                val = (abs(val) < 1/pow(10, precision+1))?0:val;
                cout << val;
                if(j != matrix_size.second-1) cout << " & ";
            }
            if(i != matrix_size.first-1) cout << "\\\\ ";
        }
        cout << "\\end{bmatrix}";
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
        if(m1.get_size().second != m2.get_size().first){
            // TODO erro se as matrizes não forem compativeis
            return 0;
        };
        Matrix m{m1.get_size().first, m2.get_size().second};

        for(size_t i = 0; i < m1.get_size().first; i++){
            for(size_t j = 0; j < m2.get_size().second; j++){
                double sum = 0;
                for(size_t k = 0; k < m1.get_size().second; k++){
                    sum+= m1.at(i, k) * m2.at(k, j);
                }
                m.set(i, j, sum);
            }
        }

        return m;
    }

    Matrix operator*(Matrix &m, VecDouble &v){
        // TODO
    }
}

