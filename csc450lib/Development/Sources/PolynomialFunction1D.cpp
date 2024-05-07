#include <PolynomialFunction1D.h>
#include <CSC450Exception.h>

using namespace csc450lib;

/**
 * Evaluates a the polynomial function at the given x value.
 * The x value must be within the domain of the function, as defined by the lower
 * and upper bounds, where the bounds are exclusive. The function is evaluated
 * using single precision floating point arithmetic.
 * 
 * @param x the x value to evaluate the function at
 * @return the value of the function at x
 * @throws CSC450Exception if x is not in the domain of the function
 * @throws CSC450Exception if the function is undefined at x
*/
float PolynomialFunction1D::func(float x) const {
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
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

/**
 * Returns a new PolynomialFunction1D object that represents the derivative of the function.
 * 
 * @param func the function to take the derivative of
 * @return the derivative of the function
*/
PolynomialFunction1D PolynomialFunction1D::derivativeFunc(const PolynomialFunction1D &func) const {
    std::vector<float> new_coefficients;
    for (int i = coefficients.size(); i > 0; i--) {
        float new_coefficient = func.coefficients[i] * (i - 1);
        new_coefficients.insert(new_coefficients.begin(), new_coefficient);
    }
    return PolynomialFunction1D(new_coefficients, this->getLowerBound(), this->getUpperBound());
}

/**
 * Returns the value of the first derivative of the function at the given x value.
 * 
 * @param x the x value to evaluate the first derivative at
 * @return the value of the first derivative at x
*/
float PolynomialFunction1D::dfunc(float x) const {
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    PolynomialFunction1D derivativeFunc = this->derivativeFunc(*this);
    return derivativeFunc.func(x);
}

/**
 * Returns the value of the second derivative of the function at the given x value.
 * 
 * @param x the x value to evaluate the second derivative at
 * @return the value of the second derivative at x
*/
float PolynomialFunction1D::d2func(float x) const {
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x is not in domain");
    }
    PolynomialFunction1D derivativeFunc = this->derivativeFunc(*this);
    PolynomialFunction1D secondDerivativeFunc = derivativeFunc.derivativeFunc(derivativeFunc);
    return secondDerivativeFunc.func(x);
}

/**
 * Evaluates a the polynomial function at the given x value using Horner's method.
 * The x value must be within the domain of the function, as defined by the lower
 * and upper bounds, where the bounds are exclusive. The function is evaluated
 * using single precision floating point arithmetic.
 * 
 * @param x the x value to evaluate the function at
 * @return the value of the function at x
 * @throws CSC450Exception if x is not in the domain of the function
 * @throws CSC450Exception if the function is undefined at x
*/
float PolynomialFunction1D::funcHorner(float x) const {
    if (x <= this->getLowerBound() || x >= this->getUpperBound()) {
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

/**
 * Creates a new 1-dimensional polynomial function with n coefficients that are
 * stored in the array a. This constructor uses the default lower and upper bounds (none).
 * 
 * @param a the array of coefficients
 * @param n the number of coefficients
*/
PolynomialFunction1D::PolynomialFunction1D(const float* a, unsigned int n) {
    for (int i = 0; i < n; i++) {
        coefficients.push_back(a[i]);
    }
}

/**
 * Creates a new 1-dimensional polynomial function with coefficients that are
 * stored in the vector a. This constructor uses the default lower and upper bounds (none).
 * 
 * @param a the vector of coefficients
*/
PolynomialFunction1D::PolynomialFunction1D(std::vector<float> a) {
    for (int i = 0; i < a.size(); i++) {
        coefficients.push_back(a[i]);
    }
}

/**
 * Creates a new 1-dimensional polynomial function with n coefficients that are
 * stored in the array a. This constructor uses the specified lower and upper bounds.
 * 
 * @param a the array of coefficients
 * @param n the number of coefficients
 * @param lowerBound the lower bound of the function
 * @param upperBound the upper bound of the function
*/
PolynomialFunction1D::PolynomialFunction1D(const float* a, unsigned int n, float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {
    for (int i = 0; i < n; i++) {
        coefficients.push_back(a[i]);
    }
    lowerBound = lowerBound;
    upperBound = upperBound;
}

/**
 * Creates a new 1-dimensional polynomial function with coefficients that are
 * stored in the vector a. This constructor uses the specified lower and upper bounds.
 * 
 * @param a the vector of coefficients
 * @param lowerBound the lower bound of the function
 * @param upperBound the upper bound of the function
*/
PolynomialFunction1D::PolynomialFunction1D(std::vector<float> a, float lowerBound, float upperBound) : Function1D(lowerBound, upperBound) {
    for (int i = 0; i < a.size(); i++) {
        coefficients.push_back(a[i]);
    }
    lowerBound = lowerBound;
    upperBound = upperBound;
}

/**
 * Uses the coefficients of the polynomial to create a string representation of the function.
 * This string representation is in the form of a mathematical expression that can be 
 * evaluated by Mathematica.
 * 
 * @return a shared pointer to a string representation of the function
*/
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

/**
 * Determines if the derivative of the function is exact.
 * 
 * @return true if the derivative is exact, false otherwise
*/
bool PolynomialFunction1D::derivativeIsExact() const {
    return this->derivativeExact;
}

/**
 * Determines if the second derivative of the function is exact.
 * 
 * @return true if the second derivative is exact, false otherwise
*/
bool PolynomialFunction1D::secondDerivativeIsExact() const {
    return this->secondDerivativeExact;
}