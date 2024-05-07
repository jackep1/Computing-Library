#include <SinFunc.h>
#include <CSC450Exception.h>
#include <cmath>

using namespace csc450lib;

/**
 * The default constructor for the SinFunc class.
*/
SinFunc::SinFunc() {}

/**
 * The constructor for the SinFunc class that sets the lower and upper bounds of the function.
*/
SinFunc::SinFunc(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

/**
 * Evaluates a the sine function at the given x value.
 * The x value must be within the domain of the function, as defined by the lower
 * and upper bounds, where the bounds are exclusive. The function is evaluated
 * using single precision floating point arithmetic.
 * 
 * @param x the x value to evaluate the function at
 * @return the value of the function at x
 * @throws CSC450Exception if x is not in the domain of the function
 * @throws CSC450Exception if the function is undefined at x
*/
float SinFunc::func(float x) const
{
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float solution = sin(0.005 * x * x) / (exp(x) - exp(1)*x);
    if (solution == NAN || solution == INFINITY || solution == -INFINITY) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

/**
 * Evaluates the derivative of the sine function at the given x value.
 * 
 * @param x the x value to evaluate the derivative at
 * @return the value of the derivative at x
*/
float SinFunc::dfunc(float x) const
{
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float numerator = (0.01 * exp(x) * x * cos(0.005 * x * x)) - ((exp(1)/100) * x * x * cos(0.005 * x * x)) - (exp(x) * sin(0.005 * x * x)) + (exp(1) * sin(0.005 * x * x));
    float denominator = (exp(x) - (exp(1) * x)) * (exp(x) - (exp(1) * x));
    return numerator / denominator;
}

/**
 * Returns whether the derivative of the sine function is exact.
*/
bool SinFunc::derivativeIsExact() const
{
    return true;
}

/**
 * Returns whether the second derivative of the sine function is exact.
*/
bool SinFunc::secondDerivativeIsExact() const
{
    return false;
}

/**
 * Creates a string representation of the sine function.
 * This string representation is in the form of a mathematical expression that can be 
 * evaluated by Mathematica.
 * 
 * @return a string representation of the sine function
*/
std::shared_ptr<std::string> SinFunc::getExpressionMMA() const
{
    return std::make_shared<std::string>("(sin(x^2)) / (e-x)");
}