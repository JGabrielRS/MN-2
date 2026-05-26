#include "eigenvalues.h"
#include "matrix/matrix.h"

int main(){
    Matrix m{{
        {3, 1, 0, 0, 0},
        {1, 4, 3, 0, 0},
        {0, 3, 5, 2, 1},
        {0, 0, 2, 6, 3},
        {0, 0, 1, 3, 8}
    }};
    m = eigenvalues::householder_method_aux(m, 0);
    m.print();

    return 0;
}