#ifndef FUNCTION1DFROMND_H
#define FUNCTION1DFROMND_H

#include <FunctionND.h>

namespace csc450lib_calc {
    /**
     * A class which represents a function of one variable that is derived from a function of N variables.
    */
    class Function1DfromND {
        public:
            Function1DfromND(const FunctionND& fn, const std::vector<float>& x0, const std::vector<float>& uvect);
            float func(float u);
    };
}

#endif /// FUNCTION1DFROMND_H