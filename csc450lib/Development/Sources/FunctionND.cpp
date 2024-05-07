#include <FunctionND.h>
#include <CSC450Exception.h>

using namespace csc450lib_calc;

/**
 * FunctionND constructor
 * 
 * @param n the number of dimensions
*/
FunctionND::FunctionND(int n) {
    this->N = n;
}