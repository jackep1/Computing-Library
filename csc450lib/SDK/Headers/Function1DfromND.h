#ifndef FUNCTION1DFROMND_H
#define FUNCTION1DFROMND_H

#include <FunctionND.h>
#include <Function1D.h>
#include <memory>

namespace csc450lib_calc {
    /**
     * A class which represents a function of one variable that is derived from a function of N variables.
    */
    class Function1DfromND : public Function1D {
        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~Function1DfromND() = default;
            Function1DfromND(const Function1DfromND& obj) = delete;
            Function1DfromND(Function1DfromND&& obj) = delete;
            Function1DfromND& operator =(const Function1DfromND& obj) = delete;
            Function1DfromND& operator =(Function1DfromND&& obj) = delete;

            Function1DfromND(std::shared_ptr<FunctionND> fn, const std::vector<float>& x0, const std::vector<float>& uvect);
            float func(float u);

            std::shared_ptr<FunctionND> f;
            std::vector<float> x0;
            std::vector<float> uvect;
    };
}

#endif /// FUNCTION1DFROMND_H