#ifndef SinFunc_H
#define SinFunc_H

#include <Function1D.h>

/**
 * The SinFunc class is a class that represents the function x --> (sin(0.005x^2)) / (e^x - e*x).
 * The function is defined for all real numbers except x = 1, and is continuous on its domain.
*/
class SinFunc : public csc450lib_calc::Function1D {
    public:
        SinFunc();
        SinFunc(float lowerBound, float upperBound);
        float func(float x) const;
        float dfunc(float x) const;
        // float d2func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //SinFunc_H