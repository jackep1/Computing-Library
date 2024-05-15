#include <DomainOfDefinition.h>
#include <vector>

namespace csc450lib_calc {

    #ifndef FUNCTIONND_H
    #define FUNCTIONND_H

    /**
     * The FunctionND class is an abstract class that represents a function of n variables.
    */
    class FunctionND {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~FunctionND() = default;
            FunctionND(const FunctionND& obj) = delete;
            FunctionND(FunctionND&& obj) = delete;
            FunctionND& operator =(const FunctionND& obj) = delete;
            FunctionND& operator =(FunctionND&& obj) = delete;

            /**
             * FunctionND constructor
             * 
             * @param n the number of dimensions
            */
            FunctionND(int n);

            /**
             * Evaluates the function at the given x value.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x the value of multiple variables at which to evaluate the function
            */
            virtual float func(const std::vector<float>& x) = 0;

            /**
             * Method for finding the partial derivatives of a function.
            */
            virtual std::vector<float> grad(const std::vector<float>& x) const;

            // Getter for the number of dimensions
            int getN() const { return N; }

        protected:
            // The number of dimensions of the function
            int N;
    };

    #endif /// FUNCTIONND_H
}