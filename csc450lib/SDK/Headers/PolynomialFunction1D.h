#ifndef A1_POLYNOMIALFUNCTION1D_H
#define A1_POLYNOMIALFUNCTION1D_H

#include <Function1D.h>
#include <vector>

/**
 * An abstract class that can represent a polynomial function.
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
