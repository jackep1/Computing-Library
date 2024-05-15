#include <Function1DfromND.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;

Function1DfromND::Function1DfromND(std::shared_ptr<FunctionND> fn, const std::vector<float>& x0, const std::vector<float>& uvect)
: f(fn), x0(x0), uvect(uvect) {
    if (x0.size() != uvect.size() || x0.size() != fn.get()->getN()) {
        throw CSC450Exception(ErrorCode::UNKNOWN_ERROR, "x0 and uvect must be the same size");
    }
}

float Function1DfromND::func(float u) {
    std::vector<float> x = this->x0;
    for (int i = 0; i < this->x0.size(); i++) {
        x[i] += x0[i] + u*uvect[i];
    }
    return this->f->func(x);
}


