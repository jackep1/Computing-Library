#include <EasySurface.h>
#include <CSC450Exception.h>

/**
 * EasySurface constructor
 * 
 * @param alpha the alpha value
*/
EasySurface::EasySurface(float alpha) {
    alpha = alpha;
}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float EasySurface::func(float x) const {
    return (cosf(x) / 5) + 1;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool EasySurface::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool EasySurface::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> EasySurface::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("Cos[x]/5 + 1"));
    return expression;
}