#ifndef FUNCTION1D_H
#define FUNCTION1D_H

#include <DomainOfDefinition.h>
#include <limits>
#include <memory>

namespace csc450lib_calc {
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
			Function1D() = default;
			Function1D(float xmin, float xmax);
			Function1D(std::shared_ptr<DomainOfDefinition> d);
			// Function1D(std::shared_ptr<float> d);
			virtual float func(float x) const = 0;
			virtual float dfunc(float x) const;
			virtual float d2func(float x) const;
			virtual std::shared_ptr<std::string> getExpressionMMA() const = 0;

			// A few methods that get properties of a function
			bool isDefinedAt(float x) const;
			float getLowerBound(void) const;
			float getUpperBound(void) const;
			virtual bool derivativeIsExact() const = 0;
			virtual bool secondDerivativeIsExact() const = 0;
		
		private:
			float lowerBound = std::numeric_limits<float>::infinity() * -1;
			float upperBound = std::numeric_limits<float>::infinity();
			std::shared_ptr<DomainOfDefinition> domain;
	};
}


#endif /// FUNCTION1D_H