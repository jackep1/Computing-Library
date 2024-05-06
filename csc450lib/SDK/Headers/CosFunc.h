/*   Classes implementing x --> cos(0.01x^2 + 1) / x   */

#ifndef CosFunc_H
#define CosFunc_H

#include "Function1D.h"

/**
 * The CosFunc class is a class that represents the function x --> cos(0.01x^2 + 1) / x.
 * The function is defined for all real numbers except x = 0, and is continuous on its domain.
 * The class includes a default constructor and a constructor which sets the lower and upper bounds of the function.
 * The class also includes a method that evaluates the function at a given x value, and a method that returns a string
 * representation of the function that can be evaluated by Mathematica.
*/
class CosFunc : public csc450lib_calc::Function1D {
public:
		CosFunc();
		CosFunc(float lowerBound, float upperBound);
		float func(float x) const;
		float dfunc(float x) const;
		float d2func(float x) const;
		bool derivativeIsExact() const;
		bool secondDerivativeIsExact() const;
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFunc_H


