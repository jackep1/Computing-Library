#include <CosFunc.h>
#include <CSC450Exception.h>
#include <cmath>

using namespace csc450lib;

/**
 * The constructor for the CosFunc class that sets the lower and upper bounds of the function.
 * 
 * @param lowerBound the lower bound of the function
 * @param upperBound the upper bound of the function
*/
CosFunc::CosFunc(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

/**
 * Evaluates a the cosine function at the given x value.
 * The x value must be within the domain of the function, as defined by the lower
 * and upper bounds, where the bounds are exclusive. The function is evaluated
 * using single precision floating point arithmetic.
 * 
 * @param x the x value to evaluate the function at
 * @return the value of the function at x
 * @throws CSC450Exception if x is not in the domain of the function
 * @throws CSC450Exception if the function is undefined at x
*/
float CosFunc::func(float x) const
{
	if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
	float solution = cosf(0.01*x*x + 1.f) / x;
    if (solution == NAN || solution == INFINITY || solution == -INFINITY) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

/**
 * Evaluates the derivative of the cosine function at the given x value.
 * 
 * @param x the x value to evaluate the derivative at
 * @return the value of the derivative at x
*/
float CosFunc::dfunc(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    float solution = ( (-0.02 * x * x * sinf(0.01 * x * x + 1.f)) - cosf(0.01f * x * x + 1.f) )
                                            / (x * x);
    if (solution == NAN || solution == INFINITY || solution == -INFINITY) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

/**
 * Evaluates the second derivative of the cosine function at the given x value.
 * 
 * @param x the x value to evaluate the second derivative at
 * @return the value of the second derivative at x
*/
float CosFunc::d2func(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    float solution = (0.0004 *
                    ( (x * x * x * x * cosf(0.01 * x * x + 1.f)) - (50 * x * x * sinf(0.01 * x * x + 1.f)) - (5000 * cosf(0.01 * x * x + 1.f)) )
                        ) / (x * x * x);
    return solution;
}

/**
 * Returns whether the derivative of the cosine function is exact.
*/
bool CosFunc::derivativeIsExact() const
{
    return true;
}

/**
 * Returns whether the second derivative of the cosine function is exact.
*/
bool CosFunc::secondDerivativeIsExact() const
{
    return true;
}

/**
 * Creates a string representation of the cosine function.
 * This string representation is in the form of a mathematical expression that can be 
 * evaluated by Mathematica.
 * 
 * @return a string representation of the cosine function
*/
std::shared_ptr<std::string> CosFunc::getExpressionMMA() const
{
	return std::make_shared<std::string>("cos(x^2 + 1) / x");
}