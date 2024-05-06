#include <memory>
#include <limits>
#ifndef FUNCTION1D_H
#define FUNCTION1D_H

namespace csc450lib_calc {
	/**
	 * The Function1D class is an abstract class that represents a function of one variable.
	 * The class has a constructor that sets the lower and upper bounds of the function.
	 * The class has a constructor that takes a shared pointer to a DomainOfDefinition object.
	 * The class includes a method that evaluates the function at a given x value, this function must be defined by child classes.
	 * The class includes a method that returns a string representation of the function that can be evaluated by Mathematica, again must be defined by child classes.
	 * The class includes a method that checks if the function is defined at a given x value.
	 * The class has methods that return the lower and upper bounds of the function.
	 * The class also has default private members that represent the lower and upper bounds of the function.
	 * These lower and upper bounds are set to negative and positive infinity, respectively, but may be changed by the constructor.
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
			// Function1D(std::shared_ptr<DomainOfDefinition> d);  OR
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

// 		private:
// 
// 			// pre C++14 style
// 			Function1D(const Function1D& obj){};
// 			Function1D(Function1D&& obj){};
// 			Function1D& operator =(const Function1D& obj){};
// 			Function1D& operator =(Function1D&& obj){};
	};
}

#endif /// FUNCTION1D_H


// 
// class Rectangle {
// 
// 
// 	public:
// 
// 		void draw() const {
// 			callCount++;
// 		}
// 
// 		float getArea() const {
// //			return (xmax-xmin)*(ymax-ymin);
// 			if (!areaIsUpToDate) {
// 				area = (xmax-xmin)*(ymax-ymin);
// 				areaIsUpToDate = true;
// 			}
// 			
// 			return area;
// 		}
// 		
// 		float setxmin(float theXmin) {
// 			xmin = theXmin;
// 			areaIsUpToDate = false;
// //			area = (xmax-xmin)*(ymax-ymin);
// 		}
// 
// 	private:
// 	
// 		float xmin, xmax, ymin, ymax;
// 		
// 		
// 		mutable float area;
// 		mutable bool areaIsUpToDate;
// 		
// }
// 
// GraphicObject   obj;
// 
// 
// 
// 
// obj.draw();
// 
// 
// 
// // This function is only meant to "use" someObj, not to modify it
// void doStuff(const GraphicObject& someObj) {
// 
// 	someObj.draw();
// 
// 
// }
// 
// 
// 
// 
// 
