#include <Function1D.h>
#include <memory>
#include <cmath>
#include <vector>

#ifndef BALLISTICFUNCTION_H
#define BALLISTICFUNCTION_H

class BallisticFunction {
    public:
        // Public methods for the interface
        BallisticFunction(float x0, float y0, float Vx0, float Vy0);
        std::vector<float> getPosition(float t) const;
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
        Surface1D(float alpha);
        std::vector<float> getOutgoingVelocity(float x, float Vinx, float Viny) const;
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
        // Public methods for the interface
        CollisionProblem1D(std::shared_ptr<BallisticFunction> ballistic, std::shared_ptr<Surface1D> surface);
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
        FlatSurface1D(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
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
        EasySurface1D(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
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
        HardSurface1D(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // HARDSURFACE1D_H