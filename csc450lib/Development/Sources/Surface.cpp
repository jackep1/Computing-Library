#include <Surface.h>
#include <string>

using namespace csc450lib_calc;

/** Base surface methods */

/**
 * Constructs a surface with a given elasticity value.
 * 
 * @param alpha the elasticity value of the surface
*/
Surface::Surface(float alpha) : a(alpha) {}

/**
 * Gets the outgoing velocity of the object after a collision with the surface.
 * 
 * @param x the x position of the object
 * @param Vinx the x velocity of the object
 * @param Viny the y velocity of the object
 * @return a vector containing {x, Voutx, Vouty} of the object after the collision
*/
std::vector<float> Surface::getOutgoingVelocity(float x, float Vinx, float Viny) const {
    float n1 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * this->dfunc(x);
    float n2 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * 1;
    std::vector<float> normal_force = std::vector<float>{n1, n2};
    std::vector<float> aN = std::vector<float>{a * normal_force[0], a * normal_force[1]};
    std::vector<float> Vout = std::vector<float>{Vinx + aN[0], Viny + aN[1]};
    return std::vector<float>{x, Vout[0], Vout[1]};
}

/**
 * Sets the elasticity value of the surface.
*/
void Surface::setAlpha(float alpha) {
    this->a = alpha;
}



/** FlatSurface methods */

/**
 * FlatSurface constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return a FlatSurface object
*/
FlatSurface::FlatSurface(float alpha) : Surface(alpha) {}

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



/** EasySurface methods */

/**
 * EasySurface constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return an EasySurface object
*/
EasySurface::EasySurface(float alpha) : Surface(alpha) {}

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



/** HardSurface methods */

/**
 * HardSurface constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return a HardSurface object
*/
HardSurface::HardSurface(float alpha) : Surface(alpha) {}

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