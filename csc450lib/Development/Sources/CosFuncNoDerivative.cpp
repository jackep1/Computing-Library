#include <CosFuncNoDerivative.h>
#include <CSC450Exception.h>
#include <cmath>

using namespace csc450lib;

/**
 * The default constructor for the CosFuncNoDerivative class.
*/
CosFuncNoDerivative::CosFuncNoDerivative() {}

/**
 * The constructor for the CosFuncNoDerivative class that sets the lower and upper bounds of the function.
 * 
 * @param lowerBound the lower bound of the function
 * @param upperBound the upper bound of the function
*/
CosFuncNoDerivative::CosFuncNoDerivative(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

/**
 * Evaluates the cosine function at the given x value.
 * 
 * @param x the x value to evaluate the function at
 * @return the value of the function at x
 * @throws CSC450Exception if x is not in the domain of the function
 * @throws CSC450Exception if the function is undefined at x
*/
float CosFuncNoDerivative::func(float x) const
{
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    float solution = cosf(0.01*x*x + 1.f) / x;
    if (solution == NAN || solution == INFINITY || solution == -INFINITY) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

std::shared_ptr<std::string> CosFuncNoDerivative::getExpressionMMA() const
{
    return std::make_shared<std::string>("cos(x^2 + 1) / x");
}

/**
 * Returns whether the derivative of the cosine function is exact.
*/
bool CosFuncNoDerivative::derivativeIsExact() const
{
    return false;
}

/**
 * Returns whether the second derivative of the cosine function is exact.
*/
bool CosFuncNoDerivative::secondDerivativeIsExact() const
{
    return false;
}