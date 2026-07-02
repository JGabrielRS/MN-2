#include "matrix/matrix.h"
#include "vec/vec.h"
#include "eigenvalues.h"
#include "qrmethod.h"
#include "svddecomposition.h"
#include "finitedifference.h"
#include "linearsystem.h"
#include "rungekuttaO4.h"
#include "derivation.h"

int main(){
    std::cout<< derivartion::derivada_foward(2, 0.001) << std::endl;
    return 0;
}