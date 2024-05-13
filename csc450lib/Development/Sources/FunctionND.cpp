#include <FunctionND.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;

/**
 * FunctionND constructor
 * 
 * @param n the number of dimensions
*/
FunctionND::FunctionND(int n) : N(n) {}

/**
 * Method for finding the partial derivatives of a function.
*/
std::vector<float> FunctionND::grad(const std::vector<float>& x) const
{
    std::vector<float> gradient;
    for (auto& xi : x) {
        // if (!this->isDefinedAt(xi)) {
        //     throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "The function is not defined at the given x value.");
        // }
        // float h = xi * 0.001;
        // if (xi == 0) {
        //     h = 0.001;
        // }
        // float fxph = this->func({xi + h});

        // gradient.push_back((this->func(x+h) - this->func(x - h)) / h);
    }

    return gradient;
}