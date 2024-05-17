#include <Function1D.h>
#include <memory>
#include <cmath>
#include <vector>

#ifndef BALLISTICFUNCTION_H
#define BALLISTICFUNCTION_H

class BallisticFunction {

    public:
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
        BallisticFunction(float x0, float y0, float Vx0, float Vy0);

        /**
         * Gets the position of the object at time t.
         * 
         * @param t the time to get the position at
         * @return a vector containing {x, y} of the object at time t
        */
        std::vector<float> getPosition(float t) const;

        /**
         * Gets the position and velocity of the object at time t.
         * 
         * @param t the time to get the position and velocity at
         * @return a vector containing {x, y, Vx, Vy} of the object at time t
        */
        std::vector<float> getPositionAndVelocity(float t) const;

    protected:
        // The initial x position
        float x0;
        // The initial y position
        float y0;
        // The initial horizontal velocity
        float Vx0;
        // The initial vertical velocity
        float Vy0;
};

#endif // BALLISTICFUNCTION_H



#ifndef SURFACE1D_H
#define SURFACE1D_H

/**
 * Represents a surface in a collision problem.
*/
class Surface1D : public csc450lib_calc::Function1D {

    public:
        /**
         * Constructs a surface with a given elasticity value.
         * 
         * @param alpha the elasticity value of the surface
        */
        Surface1D(float alpha);

        /**
         * Gets the outgoing velocity of the object after a collision with the surface.
         * 
         * @param x the x position of the object
         * @param Vinx the x velocity of the object
         * @param Viny the y velocity of the object
         * @return a vector containing {x, Voutx, Vouty} of the object after the collision
        */
        std::vector<float> getOutgoingVelocity(float x, float Vinx, float Viny) const;

        /**
         * Sets the elasticity value of the surface.
         * 
         * @param alpha the new elasticity value of the surface
        */
        void setAlpha(float alpha);

    protected:
        // The elasticity value of the surface
        float a;
};

#endif // SURFACE1D_H



#ifndef COLLISIONPROBLEM1D_H
#define COLLISIONPROBLEM1D_H

class CollisionProblem1D : public csc450lib_calc::Function1D {
    public:
        /**
         * CollisiomProblem1D constructor; consists of a ballistic
         * function and a surface.
         * 
         * @param ballistic the ballistic function
         * @param surface the surface
         * @return a CollisionProblem object
        */
        CollisionProblem1D(std::shared_ptr<BallisticFunction> ballistic, std::shared_ptr<Surface1D> surface);

        /**
         * Gets the object's height above the surface at time t.
         * 
         * @param t the time to get the difference at
         * @return the difference between the height of the surface
        */
        float func(float t) const;

        // Some methods that are useless but must be defined
        bool derivativeIsExact() const { return false; }
        bool secondDerivativeIsExact() const { return false; }
        std::shared_ptr<std::string> getExpressionMMA() const { return nullptr; }

    protected:
        std::shared_ptr<BallisticFunction> ballistic;
        std::shared_ptr<Surface1D> surface;
};

#endif // COLLISIONPROBLEM1D_H



#ifndef FLATSURFACE1D_H
#define FLATSURFACE1D_H

/**
 * The FlatSurface1D class represents a flat surface at y = 1.
*/
class FlatSurface1D : public Surface1D {
    
    public:
        /**
         * FlatSurface1D constructor; defines the elasticity.
         * 
         * @param alpha the parameter
         * @return a FlatSurface object
        */
        FlatSurface1D(float alpha);

        /**
         * Gets the height of the surface at a given x value.
         * 
         * @param x the x value
         * @return the height of the surface at x
        */
        float func(float x) const;

        /**
         * Gets the derivative of the surface at a given x value.
         * 
         * @param x the x value
         * @return 0, the derivative of the surface at x
        */
        float dfunc(float x) const;

        /**
         * @return whether the derivative of the surface is exact
        */
        bool derivativeIsExact() const;

        /**
         * @return whether the second derivative of the surface is exact
        */
        bool secondDerivativeIsExact() const;

        /**
         * @return the expression of the surface in Mathematica format
        */
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // FLATSURFACE1D_H



#ifndef EASYSURFACE1D_H
#define EASYSURFACE1D_H

/**
 * The EasySurface1D class represents a surface defined
 * by the function f(x) = cos(x)/5 + 1.
*/
class EasySurface1D : public Surface1D {
    public:
        /**
         * EasySurface1D constructor; defines the elasticity.
         * 
         * @param alpha the parameter
         * @return an EasySurface object
        */
        EasySurface1D(float alpha);

        /**
         * Gets the height of the surface at a given x value.
         * 
         * @param x the x value
         * @return the height of the surface at x
        */
        float func(float x) const;

        /**
         * @return whether the derivative of the surface is exact
        */
        bool derivativeIsExact() const;

        /**
         * @return whether the second derivative of the surface is exact
        */
        bool secondDerivativeIsExact() const;

        /**
         * @return the expression of the surface in Mathematica format
        */
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // EASYSURFACE1D_H



#ifndef HARDSURFACE1D_H
#define HARDSURFACE1D_H

/**
 * The HardSurface class represents a surface defined
 * by the function f(x) = 4sin(x) + 5cos(x/2) + (x^3)/10000.
*/
class HardSurface1D : public Surface1D {
    public:
        /**
         * HardSurface1D constructor; consists of a single parameter.
         * 
         * @param alpha the parameter
         * @return a HardSurface object
        */
        HardSurface1D(float alpha);

        /**
         * Gets the height of the surface at a given x value.
         * 
         * @param x the x value
         * @return the height of the surface at x
        */
        float func(float x) const;

        /**
         * @return whether the derivative of the surface is exact
        */
        bool derivativeIsExact() const;

        /**
         * @return whether the second derivative of the surface is exact
        */
        bool secondDerivativeIsExact() const;

        /**
         * @return the expression of the surface in Mathematica format
        */
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // HARDSURFACE1D_H