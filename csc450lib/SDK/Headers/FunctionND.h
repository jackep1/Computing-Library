#ifndef FUNCTIONND_H
#define FUNCTIONND_H

#include <vector>

namespace csc450lib_calc {
    /**
     * The FunctionND class is an abstract class that represents a function of n variables.
    */
    class FunctionND {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~FunctionND() = default;
            FunctionND() = delete;
            FunctionND(const FunctionND& obj) = delete;
            FunctionND(FunctionND&& obj) = delete;
            FunctionND& operator =(const FunctionND& obj) = delete;
            FunctionND& operator =(FunctionND&& obj) = delete;

            // Public methods for the interface
            FunctionND(int n);
            virtual float func(const std::vector<float>& x) = 0;

            // The number of dimensions of the function
            int N;
   };
}


#endif /// FUNCTIONND_H