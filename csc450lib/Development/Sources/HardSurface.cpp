#include <HardSurface.h>
#include <CSC450Exception.h>

/**
 * HardSurface constructor
 * 
 * @param alpha the alpha value
*/
HardSurface::HardSurface(float alpha) {
    this->setAlpha(alpha);
}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float HardSurface::func(float x) const {
    float t1 = 4 * sinf(x);
    float t2 = 5 * cosf(x/2);
    float t3 = x * x * x / 10000;
    return t1 + t2 + t3;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool HardSurface::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool HardSurface::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> HardSurface::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("4 Sin[x] + 5 Cos[x/2] + (x^3)/10000"));
    return expression;
}