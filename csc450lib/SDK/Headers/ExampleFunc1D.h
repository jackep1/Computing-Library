#include <Function1D.h>
#include <FunctionND.h>
#include <VectorFunction1D.h>
#include <VectorFunctionND.h>

#ifndef CosFunc_H
#define CosFunc_H

/**
 * The CosFunc class is a class that represents the function x --> cos(0.01x^2 + 1) / x.
 * The function is defined for all real numbers except x = 0, and is continuous on its domain.
*/
class CosFunc : public csc450lib_calc::Function1D {

	public:
		/**
		 * The constructor for the CosFunc class that sets the lower and upper bounds of the function.
		 * 
		 * @param lowerBound the lower bound of the function
		 * @param upperBound the upper bound of the function
		*/
		CosFunc(float lowerBound, float upperBound);

		/**
		 * Evaluates the cosine function at the given x value.
		 * 
		 * @param x the x value to evaluate the function at
		 * @return the value of the function at x
		 * @throws CSC450Exception if x is not in the domain of the function
		 * @throws CSC450Exception if the function is undefined at x
		*/
		float func(float x) const;

		/**
		 * Evaluates the derivative of the cosine function at the given x value.
		 * 
		 * @param x the x value to evaluate the derivative at
		 * @return the value of the derivative at x
		*/
		float dfunc(float x) const;

		/**
		 * Evaluates the second derivative of the cosine function at the given x value.
		 * 
		 * @param x the x value to evaluate the second derivative at
		 * @return the value of the second derivative at x
		*/
		float d2func(float x) const;

		/**
		 * Returns whether the derivative of the cosine function is exact.
		*/
		bool derivativeIsExact() const;

		/**
		 * Returns whether the second derivative of the cosine function is exact.
		*/
		bool secondDerivativeIsExact() const;

		/**
		 * Returns the expression of the function in Mathematica format.
		 * 
		 * @return the expression of the function in Mathematica format
		*/
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFunc_H



#ifndef CosFuncNoDerivative_H
#define CosFuncNoDerivative_H

/**
 * The CosFuncNoDerivative class is a class that represents the function x --> cos(0.01x^2 + 1) / x.
 * The function is defined for all real numbers except x = 0, and is continuous on its domain.
 * This class is the same as CosFunc, but it does not have a derivative.
*/
class CosFuncNoDerivative : public csc450lib_calc::Function1D {
	
	public:
		/**
		 * The constructor for the CosFuncNoDerivative class that sets the lower and upper bounds of the function.
		 * 
		 * @param lowerBound the lower bound of the function
		 * @param upperBound the upper bound of the function
		*/
		CosFuncNoDerivative(float lowerBound, float upperBound);

		/**
		 * Evaluates the cosine function at the given x value.
		 * 
		 * @param x the x value to evaluate the function at
		 * @return the value of the function at x
		 * @throws CSC450Exception if x is not in the domain of the function
		 * @throws CSC450Exception if the function is undefined at x
		*/
		float func(float x) const;

		/**
		 * Returns whether the derivative of the cosine function is exact.
		*/
		bool derivativeIsExact() const;

		/**
		 * Returns whether the second derivative of the cosine function is exact.
		*/
		bool secondDerivativeIsExact() const;

		/**
		 * Returns the expression of the function in Mathematica format.
		 * 
		 * @return the expression of the function in Mathematica format
		*/
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFuncNoDerivative_H



#ifndef SinFunc_H
#define SinFunc_H

/**
 * The SinFunc class is a class that represents the function x --> (sin(0.005x^2)) / (e^x - e*x).
 * The function is defined for all real numbers except x = 1, and is continuous on its domain.
*/
class SinFunc : public csc450lib_calc::Function1D {

    public:
		/**
		 * The default constructor for the SinFunc class.
		*/
        SinFunc();

		/**
		 * The constructor for the SinFunc class that sets the lower and upper bounds of the function.
		*/
        SinFunc(float lowerBound, float upperBound);

		/**
		 * Evaluates the sine function at the given x value.
		 * 
		 * @param x the x value to evaluate the function at
		 * @return the value of the function at x
		 * @throws CSC450Exception if x is not in the domain of the function
		 * @throws CSC450Exception if the function is undefined at x
		*/
        float func(float x) const;

		/**
		 * Evaluates the derivative of the sine function at the given x value.
		 * 
		 * @param x the x value to evaluate the derivative at
		 * @return the value of the derivative at x
		*/
        float dfunc(float x) const;
        // float d2func(float x) const;

		/**
		 * Returns whether the derivative of the sine function is exact.
		*/
        bool derivativeIsExact() const;

		/**
		 * Returns whether the second derivative of the sine function is exact.
		*/
        bool secondDerivativeIsExact() const;

		/**
		 * Returns the expression of the function in Mathematica format.
		 * 
		 * @return the expression of the function in Mathematica format
		*/
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //SinFunc_H