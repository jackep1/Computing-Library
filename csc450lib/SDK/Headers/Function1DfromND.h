#include <FunctionND.h>
#include <Function1D.h>
#include <memory>

namespace csc450lib_calc {

    #ifndef FUNCTION1DFROMND_H
    #define FUNCTION1DFROMND_H

    /**
     * A class which represents a function of one variable that is derived from a function of N variables.
    */
    class Function1DfromND : public Function1D {

        public:
            /**
             * The constructor for the Function1DfromND class that sets the function, the point x0, and direction vector uvect.
             * 
             * @param fn the function of N variables
             * @param x0 the point x0
             * @param uvect the direction vector uvect
             * @throws CSC450Exception if x0 and uvect are not the same size as the number of variables in fn
            */
            Function1DfromND(std::shared_ptr<FunctionND> fn, const std::vector<float>& x0, const std::vector<float>& uvect);

            /**
             * Evaluates the function at the given u value.
             * 
             * @param u the u value to evaluate the function at
             * @return the value of the function at u
            */
            float func(float u);

        protected:
            // The multi-variable function
            std::shared_ptr<FunctionND> f;
            // The point x0
            std::vector<float> x0;
            // The direction vector uvect
            std::vector<float> uvect;
    };

    #endif /// FUNCTION1DFROMND_H
}