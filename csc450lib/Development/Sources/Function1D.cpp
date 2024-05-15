#include <Function1D.h>
#include <DomainOfDefinition.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;


Function1D::Function1D()
: domain({subDomain(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), false, false)}) {}

Function1D::Function1D(float xmin, float xmax)
: domain({subDomain(xmin, xmax, false, false)}) {}

Function1D::Function1D(DomainOfDefinition d)
: domain(d) {}

float Function1D::dfunc(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "The function is not defined at the given x value.");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    float fxph = func(x + h);
    float fxmh = func(x - h);
    float solution = ((fxph - fxmh) / (2 * h));
    return solution;
}

float Function1D::d2func(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    float fxph = func(x + h);
    float fxmh = this->func(x - h);
    float fx2 = 2 * func(x);
    float solution = ((fxph - fx2 + fxmh) / (h * h));
    return solution;
}

bool Function1D::isDefinedAt(float x) const
{
    if (domain.contains_point(x)) {
        return true;
    }
    return false;
}

float Function1D::getLowerBound(void) const
{
    return domain.get_domain()[0].xMin;
}

float Function1D::getUpperBound(void) const
{
    return domain.get_domain()[domain.get_domain().size() - 1].xMax;
}

void Function1D::setDomain(DomainOfDefinition d)
{
    domain = d;
}





/** Polynomial Function methods */

float PolynomialFunction1D::func(float x) const {
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    float solution = 0;
    for (int i = coefficients.size(); i > 0; i--) {
        solution += (coefficients[coefficients.size() - i] * pow(x, i - 1));
    }
    if (solution == NAN) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

PolynomialFunction1D PolynomialFunction1D::derivativeFunc(const PolynomialFunction1D &func) const {
    std::vector<float> new_coefficients;
    for (int i = coefficients.size(); i > 0; i--) {
        float new_coefficient = func.coefficients[i] * (i - 1);
        new_coefficients.insert(new_coefficients.begin(), new_coefficient);
    }
    return PolynomialFunction1D(new_coefficients, this->getLowerBound(), this->getUpperBound());
}

float PolynomialFunction1D::dfunc(float x) const {
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    PolynomialFunction1D derivativeFunc = this->derivativeFunc(*this);
    return derivativeFunc.func(x);
}

float PolynomialFunction1D::d2func(float x) const {
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    PolynomialFunction1D derivativeFunc = this->derivativeFunc(*this);
    PolynomialFunction1D secondDerivativeFunc = derivativeFunc.derivativeFunc(derivativeFunc);
    return secondDerivativeFunc.func(x);
}

float PolynomialFunction1D::funcHorner(float x) const {
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    float solution = 0;
    float inner_phrase = hornerCoefficients[hornerCoefficients.size() - 1];
    for (int i = 0; i < hornerCoefficients.size(); i++) {
        inner_phrase = inner_phrase * x;
        inner_phrase = inner_phrase + hornerCoefficients[hornerCoefficients.size() - i - 2];
    }
    if (solution == NAN) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "function is undefined at x");
    }
    return solution;
}

PolynomialFunction1D::PolynomialFunction1D(const float* a, unsigned int n) {
    for (int i = 0; i < n; i++) {
        coefficients.push_back(a[i]);
    }
}

PolynomialFunction1D::PolynomialFunction1D(std::vector<float> a) {
    for (int i = 0; i < a.size(); i++) {
        coefficients.push_back(a[i]);
    }
}

PolynomialFunction1D::PolynomialFunction1D(const float* a, unsigned int n, float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {
    for (int i = 0; i < n; i++) {
        coefficients.push_back(a[i]);
    }
    lowerBound = lowerBound;
    upperBound = upperBound;
}

PolynomialFunction1D::PolynomialFunction1D(std::vector<float> a, float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {
    for (int i = 0; i < a.size(); i++) {
        coefficients.push_back(a[i]);
    }
}

std::shared_ptr<std::string> PolynomialFunction1D::getExpressionMMA() const {
    std::string expression = "";
    for (int i = coefficients.size(); i > 0; i--) {
        expression += std::to_string(coefficients[coefficients.size() - i]) + "x^" + std::to_string(i - 1);
        if (i > 0) {
            expression += " + ";
        }
    }
    return std::make_shared<std::string>(expression);
}

bool PolynomialFunction1D::derivativeIsExact() const {
    return this->derivativeExact;
}

bool PolynomialFunction1D::secondDerivativeIsExact() const {
    return this->secondDerivativeExact;
}