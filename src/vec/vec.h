#ifndef MN_VEC
#define MN_VEC

#include <vector>
#include <iostream>
#include <math.h>

namespace Vec{
    using namespace std;
    typedef vector<double> VecDouble;
    
    double vec_length(VecDouble &vec);
    VecDouble vec_normalize(VecDouble &vec);
    void print_vec(VecDouble &vec);
    void print_vec_latex(VecDouble &vec);
    
    VecDouble operator-(VecDouble &v1, VecDouble &v2);
};


#endif // MN_VEC