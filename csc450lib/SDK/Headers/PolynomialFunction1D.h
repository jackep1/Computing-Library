//
// Created by jack on 2/09/24.
//
#include <vector>

#ifndef A1_POLYNOMIALFUNCTION1D_H
#define A1_POLYNOMIALFUNCTION1D_H

#include "Function1D.h"

/**
 * The PolynomialFunction1D class is a class that can represent a polynomial function of many forms.
 * The class does not include a default constructor, since the exact form of the function must be specified.
 * The class includes constructors that take an array of coefficients or a vector of coefficients.
 * The class also includes constructors that take an array or vector of coefficients, as well as lower and upper bounds.
 * The class includes a method that evaluates the function at a given x value in the standard form of a polynomial (x^2 + x + c, for example).
 * The class also includes a method that evaluates the function at a given x value using Horner's method.
 * The class includes a method that returns a string representation of the function that can be evaluated by Mathematica.
 * The classes members are the coefficients of the polynomial function and the coefficients of the polynomial function in Horner's form.
*/
class PolynomialFunction1D : public csc450lib_calc::Function1D {
public:
    std::vector<float> coefficients;
    std::vector<float> hornerCoefficients;
    float func(float x) const;
    float dfunc(float x) const;
    float d2func(float x) const;
    float funcHorner(float x) const;
    PolynomialFunction1D derivativeFunc(const PolynomialFunction1D &func) const;
    bool derivativeIsExact() const;
    bool secondDerivativeIsExact() const;
    PolynomialFunction1D(const float* a, unsigned int n);
    PolynomialFunction1D(std::vector<float> coefficients);
    PolynomialFunction1D(const float* a, unsigned int n, float lowerBound, float upperBound);
    PolynomialFunction1D(std::vector<float> coefficients, float lowerBound, float upperBound);
    std::shared_ptr<std::string> getExpressionMMA() const;
    bool derivativeExact = true;
    bool secondDerivativeExact = true;
};

#endif //A1_POLYNOMIALFUNCTION1D_H
