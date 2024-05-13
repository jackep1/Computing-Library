#include <CollisionProblem1D.h>
#include <memory>
#include <string>

using namespace csc450lib_calc;

/** Collision Problem methods */

/**
 * CollisiomProblem1D constructor; consists of a ballistic
 * function and a surface.
 * 
 * @param ballistic the ballistic function
 * @param surface the surface
 * @return a CollisionProblem object
*/
CollisionProblem1D::CollisionProblem1D(std::shared_ptr<BallisticFunction> ballistic, std::shared_ptr<Surface1D> surface)
: ballistic(ballistic), surface(surface) {}

/**
 * Gets the object's height above the surface at time t.
 * 
 * @param t the time to get the difference at
 * @return the difference between the height of the surface
*/
float CollisionProblem1D::func(float t) const {
    std::vector<float> position = this->ballistic->getPosition(t);
    float surface_height = this->surface->func(position[0]);
    return position[1] - surface_height;
}



/** Ballistic Function methods */

/**
 * The constructor for the BallisticFunctions which
 * sets the initial x and y positions and the initial
 * x and y velocities.
 * 
 * @param x0 the initial x position
 * @param y0 the initial y position
 * @param Vx0 the initial x velocity
 * @param Vy0 the initial y velocity
*/
BallisticFunction::BallisticFunction(float x0, float y0, float Vx0, float Vy0)
: x0(x0), y0(y0), Vx0(Vx0), Vy0(Vy0) {}

/**
 * Gets the position of the object at time t.
 * 
 * @param t the time to get the position at
 * @return a vector containing {x, y} of the object at time t
*/
std::vector<float> BallisticFunction::getPosition(float t) const {
    float x = this->x0 + this->Vx0 * t;
    float y = this->y0 + (this->Vy0 * t) - (0.5 * 9.8 * t * t);
    return std::vector<float>{x, y};
}

/**
 * Gets the position and velocity of the object at time t.
 * 
 * @param t the time to get the position and velocity at
 * @return a vector containing {x, y, Vx, Vy} of the object at time t
*/
std::vector<float> BallisticFunction::getPositionAndVelocity(float t) const {
    float x = this->x0 + this->Vx0 * t;
    float y = this->y0 + (this->Vy0 * t) - (0.5 * 9.8 * t * t);
    float Vx = this->Vx0;
    float Vy = this->Vy0 - (9.8 * t);
    return std::vector<float>{x, y, Vx, Vy};
}



/** Base surface methods */

/**
 * Constructs a surface with a given elasticity value.
 * 
 * @param alpha the elasticity value of the surface
*/
Surface1D::Surface1D(float alpha) : a(alpha) {}

/**
 * Gets the outgoing velocity of the object after a collision with the surface.
 * 
 * @param x the x position of the object
 * @param Vinx the x velocity of the object
 * @param Viny the y velocity of the object
 * @return a vector containing {x, Voutx, Vouty} of the object after the collision
*/
std::vector<float> Surface1D::getOutgoingVelocity(float x, float Vinx, float Viny) const {
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
void Surface1D::setAlpha(float alpha) {
    this->a = alpha;
}



/** FlatSurface1D methods */

/**
 * FlatSurface1D constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return a FlatSurface object
*/
FlatSurface1D::FlatSurface1D(float alpha) : Surface1D(alpha) {}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float FlatSurface1D::func(float x) const {
    return 1;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool FlatSurface1D::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool FlatSurface1D::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> FlatSurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("1"));
    return expression;
}



/** EasySurface1D methods */

/**
 * EasySurface1D constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return an EasySurface object
*/
EasySurface1D::EasySurface1D(float alpha) : Surface1D(alpha) {}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float EasySurface1D::func(float x) const {
    return (cosf(x) / 5) + 1;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool EasySurface1D::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool EasySurface1D::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> EasySurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("Cos[x]/5 + 1"));
    return expression;
}



/** HardSurface1D methods */

/**
 * HardSurface1D constructor; consists of a single parameter.
 * 
 * @param alpha the parameter
 * @return a HardSurface object
*/
HardSurface1D::HardSurface1D(float alpha) : Surface1D(alpha) {}

/**
 * Gets the height of the surface at a given x value.
 * 
 * @param x the x value
 * @return the height of the surface at x
*/
float HardSurface1D::func(float x) const {
    float t1 = 4 * sinf(x);
    float t2 = 5 * cosf(x/2);
    float t3 = x * x * x / 10000;
    return t1 + t2 + t3;
}

/**
 * @return whether the derivative of the surface is exact
*/
bool HardSurface1D::derivativeIsExact() const {
    return false;
}

/**
 * @return whether the second derivative of the surface is exact
*/
bool HardSurface1D::secondDerivativeIsExact() const {
    return false;
}

/**
 * @return the expression of the surface in Mathematica format
*/
std::shared_ptr<std::string> HardSurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("4 Sin[x] + 5 Cos[x/2] + (x^3)/10000"));
    return expression;
}