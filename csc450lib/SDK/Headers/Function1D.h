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
		
			// Public methods for the interface
			Function1D();
			Function1D(float xmin, float xmax);
			Function1D(DomainOfDefinition d);
			virtual float func(float x) const = 0;
			virtual float dfunc(float x) const;
			virtual float d2func(float x) const;
			virtual std::shared_ptr<std::string> getExpressionMMA() const = 0;

			// A few methods that get properties of a function
			bool isDefinedAt(float x) const;
			float getLowerBound(void) const;
			float getUpperBound(void) const;
			void setDomain(DomainOfDefinition d);
			virtual bool derivativeIsExact() const = 0;
			virtual bool secondDerivativeIsExact() const = 0;
		
		protected:
			DomainOfDefinition domain;
	};

	#endif /// FUNCTION1D_H



	#ifndef A1_POLYNOMIALFUNCTION1D_H
	#define A1_POLYNOMIALFUNCTION1D_H

	/**
	 * An abstract class that can represent a polynomial function.
	*/
	class PolynomialFunction1D : public csc450lib_calc::Function1D {
	public:
		std::vector<float> coefficients;
		std::vector<float> hornerCoefficients;
		float func(float x) const;
		float dfunc(float x) const;
		float d2func(float x) const;
		float funcHorner(float x) const;
		PolynomialFunction1D derivativeFunc(const PolynomialFunction1D &func) const;
		bool derivativeIsExact() const;
		bool secondDerivativeIsExact() const;
		PolynomialFunction1D(const float* a, unsigned int n);
		PolynomialFunction1D(std::vector<float> coefficients);
		PolynomialFunction1D(const float* a, unsigned int n, float lowerBound, float upperBound);
		PolynomialFunction1D(std::vector<float> coefficients, float lowerBound, float upperBound);
		std::shared_ptr<std::string> getExpressionMMA() const;
		bool derivativeExact = true;
		bool secondDerivativeExact = true;
	};

	#endif //A1_POLYNOMIALFUNCTION1D_H
}