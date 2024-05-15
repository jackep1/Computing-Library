#include <DomainOfDefinition.h>
#include <Function1D.h>
#include <limits>
#include <memory>

namespace csc450lib_calc {

    #ifndef VECTORFUNCTION1D_H
    #define VECTORFUNCTION1D_H

    /**
     * An abstract class that represents a function of one variable
     * and returns multiple values.
    */
    class VectorFunction1D {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~VectorFunction1D() = default;
            VectorFunction1D(const VectorFunction1D& obj) = delete;
            VectorFunction1D(VectorFunction1D&& obj) = delete;
            VectorFunction1D& operator =(const VectorFunction1D& obj) = delete;
            VectorFunction1D& operator =(VectorFunction1D&& obj) = delete;

            /**
             * The constructor that sets the lower and upper bounds of the function.
             * 
             * @param xmin The lower bound of the function.
             * @param xmax The upper bound of the function.
            */
            VectorFunction1D(float xmin, float xmax);

            /**
             * The constructor that sets a unique domain of definition.
            */
            VectorFunction1D(DomainOfDefinition d);

            /**
             * Evaluates the function at the given x value.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the function at.
             * @return The value of the function at x.
            */
            virtual float func(float x) const = 0;

            /**
             * Evaluates the derivative of the function at the given x value using an approximation.
             * 
             * @param x The x value to evaluate the derivative at.
             * @return The derivative of the function at x.
            */
            virtual float dfunc(float x) const;

            /**
             * Evaluates the second derivative of the function at the given x value using an approximation.
             * 
             * @param x The x value to evaluate the second derivative at.
             * @return The second derivative of the function at x.
            */
            virtual float d2func(float x) const;

            /**
             * Evaluates the third derivative of the function at the given x value using an approximation.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the third derivative at.
             * @return The third derivative of the function at x.
            */
            virtual std::shared_ptr<std::string> getExpressionMMA() const = 0;

            /**
             * Checks if the function is defined at a given x value.
             * 
             * @param x The x value to check.
             * @return true if the function is defined at x, false otherwise.
            */
            bool isDefinedAt(float x) const;

            /**
             * Gets the lower bound of the function.
             * 
             * @return The lower bound of the function.
            */
            float getLowerBound(void) const;

            /**
             * Gets the upper bound of the function.
             * 
             * @return The upper bound of the function.
            */
            float getUpperBound(void) const;

            /**
             * Sets the domain of the function.
             * 
             * @param d the new domain of definition
            */
            void setDomain(DomainOfDefinition d);

            /**
             * Returns the derivative of the function at x using an approximation.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the derivative at.
             * @return The derivative of the function at x.
            */
            virtual bool derivativeIsExact() const = 0;

            /**
             * Returns the second derivative of the function at x using an approximation.
             * This is a pure virtual function that must be implemented by derived classes.
             * 
             * @param x The x value to evaluate the second derivative at.
             * @return The second derivative of the function at x.
            */
            virtual bool secondDerivativeIsExact() const = 0;

        protected:
            // The domain of definition of the function
            DomainOfDefinition domain;
    };

    #endif /// VECTORFUNCTION1D_H
}