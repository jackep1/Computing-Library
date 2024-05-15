#include <ExampleFunc1D.h>
#include <CSC450Exception.h>
#include <cmath>

using namespace csc450lib;


/** CosFunc methods */

CosFunc::CosFunc(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

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

bool CosFunc::derivativeIsExact() const
{
    return true;
}

bool CosFunc::secondDerivativeIsExact() const
{
    return true;
}

std::shared_ptr<std::string> CosFunc::getExpressionMMA() const
{
	return std::make_shared<std::string>("cos(x^2 + 1) / x");
}



/** CosFuncNoDerivative methods */

CosFuncNoDerivative::CosFuncNoDerivative(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

float CosFuncNoDerivative::func(float x) const
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

bool CosFuncNoDerivative::derivativeIsExact() const
{
    return false;
}

bool CosFuncNoDerivative::secondDerivativeIsExact() const
{
    return false;
}

std::shared_ptr<std::string> CosFuncNoDerivative::getExpressionMMA() const
{
    return std::make_shared<std::string>("cos(x^2 + 1) / x");
}



/** SinFunc methods */

SinFunc::SinFunc() {}

SinFunc::SinFunc(float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {}

float SinFunc::func(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float solution = sin(0.005 * x * x) / (exp(x) - exp(1)*x);
    if (solution == NAN || solution == INFINITY || solution == -INFINITY) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

float SinFunc::dfunc(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float numerator = (0.01 * exp(x) * x * cos(0.005 * x * x)) - ((exp(1)/100) * x * x * cos(0.005 * x * x)) - (exp(x) * sin(0.005 * x * x)) + (exp(1) * sin(0.005 * x * x));
    float denominator = (exp(x) - (exp(1) * x)) * (exp(x) - (exp(1) * x));
    return numerator / denominator;
}

bool SinFunc::derivativeIsExact() const
{
    return true;
}

bool SinFunc::secondDerivativeIsExact() const
{
    return false;
}

std::shared_ptr<std::string> SinFunc::getExpressionMMA() const
{
    return std::make_shared<std::string>("(sin(x^2)) / (e-x)");
}