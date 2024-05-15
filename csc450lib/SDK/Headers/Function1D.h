#include <DomainOfDefinition.h>
#include <memory>

namespace csc450lib_calc {
	
	#ifndef FUNCTION1D_H
	#define FUNCTION1D_H

	/**
	 * An abstract class that represents a function of one variable.
	*/
	class Function1D {

		public:
			// Don't need copy and move constructors and assignment operators
			virtual ~Function1D() = default;
			Function1D(const Function1D& obj) = delete;
			Function1D(Function1D&& obj) = delete;
			Function1D& operator =(const Function1D& obj) = delete;
			Function1D& operator =(Function1D&& obj) = delete;
		
			/**
			 * The default constructor for the Function1D class that sets the domain of definition to be all real numbers.
			*/
			Function1D();

			/**
			 * The constructor for the Function1D class that sets the lower and upper bounds of the function.
			 * 
			 * @param xmin the lower bound of the function
			 * @param xmax the upper bound of the function
			*/
			Function1D(float xmin, float xmax);

			/**
			 * The constructor for the Function1D class that sets a unique domain of definition.
			 * 
			 * @param d the domain of definition
			*/
			Function1D(DomainOfDefinition d);

			/**
			 * Evaluates the function at the given x value.
			 * This is a pure virtual function that must be implemented by derived classes.
			 * 
			 * @param x the x value to evaluate the function at
			 * @return the value of the function at x
			*/
			virtual float func(float x) const = 0;

			/**
			 * Returns the deriviative of the function at x using an approximation.
			 * 
			 * @param x the point at which to evaluate the derivative
			 * @return the derivative at x
			*/
			virtual float dfunc(float x) const;

			/**
			 * Returns the second derivative of the function at x using an approximation.
			 * 
			 * @param x the point at which to evaluate the second derivative
			 * @return the second derivative at x
			*/
			virtual float d2func(float x) const;

			/**
			 * Returns the expression of the function in Mathematica format.
			 * This is a pure virtual function that must be implemented by derived classes.
			 * 
			 * @return the expression of the function in Mathematica format
			*/
			virtual std::shared_ptr<std::string> getExpressionMMA() const = 0;

			/**
			 * Returns whether the function is defined at the given x value.
			 * 
			 * @param x the x value to check
			 * @return true if the function is defined at x, false otherwise
			*/
			bool isDefinedAt(float x) const;

			/**
			 * Gets the lower bound of the function.
			 * 
			 * @return the lower bound of the function
			*/
			float getLowerBound(void) const;

			/**
			 * Gets the upper bound of the function.
			 * 
			 * @return the upper bound of the function
			*/
			float getUpperBound(void) const;

			/**
			 * Sets the domain of definition of the function.
			 * 
			 * @param d the new domain of definition
			*/
			void setDomain(DomainOfDefinition d);

			/**
			 * Returns whether the derivative of the function is exact.
			 * This is a pure virtual function that must be implemented by derived classes.
			*/
			virtual bool derivativeIsExact() const = 0;

			/**
			 * Returns whether the second derivative of the function is exact.
			 * This is a pure virtual function that must be implemented by derived classes.
			*/
			virtual bool secondDerivativeIsExact() const = 0;
		
		protected:
			// The domain of the function
			DomainOfDefinition domain;
	};

	#endif /// FUNCTION1D_H



	#ifndef A1_POLYNOMIALFUNCTION1D_H
	#define A1_POLYNOMIALFUNCTION1D_H

	/**
	 * An abstract class that represents polynomial functions.
	*/
	class PolynomialFunction1D : public csc450lib_calc::Function1D {

		public:
			/**
			 * Evaluates a the polynomial function at the given x value.
			 * The x value must be within the domain of the function, as defined by the lower
			 * and upper bounds, where the bounds are exclusive. The function is evaluated
			 * using single precision floating point arithmetic.
			 * 
			 * @param x the x value to evaluate the function at
			 * @return the value of the function at x
			 * @throws CSC450Exception if x is not in the domain of the function
			 * @throws CSC450Exception if the function is undefined at x
			*/
			float func(float x) const;

			/**
			 * Returns the value of the first derivative of the function at the given x value.
			 * 
			 * @param x the x value to evaluate the first derivative at
			 * @return the value of the first derivative at x
			 * @throws CSC450Exception if x is not in the domain of the function
			*/
			float dfunc(float x) const;

			/**
			 * Returns the value of the second derivative of the function at the given x value.
			 * 
			 * @param x the x value to evaluate the second derivative at
			 * @return the value of the second derivative at x
			 * @throws CSC450Exception if x is not in the domain of the function
			*/
			float d2func(float x) const;

			/**
			 * Evaluates a the polynomial function at the given x value using Horner's method.
			 * The x value must be within the domain of the function, as defined by the lower
			 * and upper bounds, where the bounds are exclusive. The function is evaluated
			 * using single precision floating point arithmetic.
			 * 
			 * @param x the x value to evaluate the function at
			 * @return the value of the function at x
			 * @throws CSC450Exception if x is not in the domain of the function
			 * @throws CSC450Exception if the function is undefined at x
			*/
			float funcHorner(float x) const;

			/**
			 * Returns a new PolynomialFunction1D object that represents the derivative of the function.
			 * 
			 * @param func the function to take the derivative of
			 * @return the derivative of the function
			*/
			PolynomialFunction1D derivativeFunc(const PolynomialFunction1D &func) const;

			/**
			 * Returns whether the derivative of the polynomial function is exact.
			 * 
			 * @return true if the derivative is exact, false otherwise
			*/
			bool derivativeIsExact() const;

			/**
			 * Returns whether the second derivative of the polynomial function is exact.
			 * 
			 * @return true if the second derivative is exact, false otherwise
			*/
			bool secondDerivativeIsExact() const;

			/**
			 * Creates a new 1-dimensional polynomial function with n coefficients that are
			 * stored in the array a. This constructor uses the default lower and upper bounds (none).
			 * 
			 * @param a the array of coefficients
			 * @param n the number of coefficients
			*/
			PolynomialFunction1D(const float* a, unsigned int n);

			/**
			 * Creates a new 1-dimensional polynomial function with coefficients that are
			 * stored in the vector a. This constructor uses the default lower and upper bounds (none).
			 * 
			 * @param a the vector of coefficients
			*/
			PolynomialFunction1D(std::vector<float> coefficients);

			/**
			 * Creates a new 1-dimensional polynomial function with n coefficients that are
			 * stored in the array a. This constructor uses the specified lower and upper bounds.
			 * 
			 * @param a the array of coefficients
			 * @param n the number of coefficients
			 * @param lowerBound the lower bound of the function
			 * @param upperBound the upper bound of the function
			*/
			PolynomialFunction1D(const float* a, unsigned int n, float lowerBound, float upperBound);

			/**
			 * Creates a new 1-dimensional polynomial function with coefficients that are
			 * stored in the vector a. This constructor uses the specified lower and upper bounds.
			 * 
			 * @param a the vector of coefficients
			 * @param lowerBound the lower bound of the function
			 * @param upperBound the upper bound of the function
			*/
			PolynomialFunction1D(std::vector<float> coefficients, float lowerBound, float upperBound);

			/**
			 * Uses the coefficients of the polynomial to create a string representation of the function.
			 * This string representation is in the form of a mathematical expression that can be 
			 * evaluated by Mathematica.
			 * 
			 * @return a shared pointer to a string representation of the function
			*/
			std::shared_ptr<std::string> getExpressionMMA() const;

		protected:
			// Derivative is exact for polynomial functions
			bool derivativeExact = true;
			// Second derivative is exact for polynomial functions
			bool secondDerivativeExact = true;
			// The coefficients of the polynomial
			std::vector<float> coefficients;
			// The coefficients of the polynomial in Horner form
			std::vector<float> hornerCoefficients;
	};

	#endif //A1_POLYNOMIALFUNCTION1D_H
}