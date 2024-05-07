#include <FlatSurface.h>
#include <CSC450Exception.h>

/**
 * FlatSurface constructor
 * 
 * @param alpha the alpha value
*/
FlatSurface::FlatSurface(float alpha) {
    alpha = alpha;
}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float FlatSurface::func(float x) const {
    return 1;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool FlatSurface::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool FlatSurface::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> FlatSurface::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("1"));
    return expression;
}