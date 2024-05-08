#include <Function1DfromND.h>
#include <CSC450Exception.h>
//#include <cmath>

using namespace csc450lib;
using namespace csc450lib_calc;

Function1DfromND::Function1DfromND(const FunctionND& fn, const std::vector<float>& x0, const std::vector<float>& uvect) {
    if (x0.size() != uvect.size() || x0.size() != fn.N) {
        throw CSC450Exception(ErrorCode::UNKNOWN_ERROR, "x0 and uvect must be the same size");
    }
    this->f = std::make_shared<FunctionND>(fn);
    this->x0 = x0;
    this->uvect = uvect;
}

float Function1DfromND::func(float u) {
    std::vector<float> x = this->x0;
    for (int i = 0; i < this->x0.size(); i++) {
        x[i] += u * cosf(theta);
    }
}