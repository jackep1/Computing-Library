#include <Function1D.h>
#include <vector>
#ifndef SURFACE_H
#define SURFACE_H

/**
 * Surface class; represents a surface in a collision problem.
*/
class Surface : csc450lib_calc::Function1D {
    public:
        // Public methods for the interface
        std::vector<float> getOutgoingVelocity(float x, float Vinx, float Viny) const;
        void setAlpha(float alpha);

        /** Some methods which will need to be implemented by any actual Surfaces */
        float func(float x) const;
        std::shared_ptr<std::string> getExpressionMMA() const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
    private:
        // The elasticity value of the surface
        float alpha;
};

#endif // SURFACE_H