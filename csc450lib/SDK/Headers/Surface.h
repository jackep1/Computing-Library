#include <Function1D.h>
#include <cmath>
#include <vector>

#ifndef SURFACE_H
#define SURFACE_H

/**
 * Represents a surface in a collision problem.
*/
class Surface : public csc450lib_calc::Function1D {

    public:
        Surface(float alpha);
        std::vector<float> getOutgoingVelocity(float x, float Vinx, float Viny) const;
        void setAlpha(float alpha);

    protected:
        // The elasticity value of the surface
        float a;
};

#endif // SURFACE_H



#ifndef FLATSURFACE_H
#define FLATSURFACE_H

/**
 * The FlatSurface class represents a flat surface at y = 1.
*/
class FlatSurface : public Surface {
    
    public:
        FlatSurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // FLATSURFACE_H



#ifndef EASYSURFACE_H
#define EASYSURFACE_H

/**
 * The EasySurface class represents a surface defined
 * by the function f(x) = cos(x)/5 + 1.
*/
class EasySurface : public Surface {
    public:
        EasySurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // EASYSURFACE_H



#ifndef HARDSURFACE_H
#define HARDSURFACE_H

/**
 * The HardSurface class represents a surface defined
 * by the function f(x) = 4sin(x) + 5cos(x/2) + (x^3)/10000.
*/
class HardSurface : public Surface {
    public:
        HardSurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // HARDSURFACE_H