#include <vector>

namespace csc450lib_calc {

    #ifndef VECTORFUNCTIONND_H
    #define VECTORFUNCTIONND_H

    class VectorFunctionND {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~VectorFunctionND() = default;
            VectorFunctionND(const VectorFunctionND& obj) = delete;
            VectorFunctionND(VectorFunctionND&& obj) = delete;
            VectorFunctionND& operator =(const VectorFunctionND& obj) = delete;
            VectorFunctionND& operator =(VectorFunctionND&& obj) = delete;

            /**
             * The constructor that sets the number of dimensions of the function.
             * 
             * @param n The number of dimensions of the function.
            */
            VectorFunctionND(int n);

            /**
             * Evaluates the function at the given x value.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the function at.
             * @return The a vector of values found using x.
            */
            virtual std::vector<float> func(const std::vector<float>& x) const = 0;

            /**
             * Evaluates the gradient of the function at the given x value.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the gradient at.
             * @return The gradient of the function at x.
            */
            virtual std::vector<std::vector<float>> grad(const std::vector<float>& x) const = 0;

        protected:
            // The number of dimensions of the function
            int N;
    };

    #endif /// VECTORFUNCTIONND_H
}