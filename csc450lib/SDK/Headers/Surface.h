#include <Function1D.h>
#include <vector>
#ifndef SURFACE_H
#define SURFACE_H

/**
 * Surface class; represents a surface in a collision problem.
*/
class Surface : public csc450lib_calc::Function1D {
    public:
        /**
         * Gets the outgoing velocity of the object after a collision with the surface.
         * 
         * @param x the x position of the object
         * @param Vinx the x velocity of the object
         * @param Viny the y velocity of the object
         * @return a vector containing {x, Voutx, Vouty} of the object after the collision
        */
        std::vector<float> getOutgoingVelocity(float x, float Vinx, float Viny) const {
            float Voutx = Vinx * alpha;
            float Vouty = Viny * alpha;
            return std::vector<float>{x, Voutx, Vouty};
        }
        /**
         * Sets the 'a' or elasticity value of the surface.
        */
        void setAlpha(float alpha) { this->alpha = alpha; }

        /** Some methods which will need to be implemented by any actual Surfaces */
        // float func(float x) const;
        // std::shared_ptr<std::string> getExpressionMMA() const;
        // bool derivativeIsExact() const;
        // bool secondDerivativeIsExact() const;
    private:
        // The elasticity value of the surface
        float alpha;
};

#endif // SURFACE_H