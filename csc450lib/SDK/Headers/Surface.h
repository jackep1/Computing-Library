#ifndef SURFACE_H
#define SURFACE_H

#include <Function1D.h>
#include <cmath>
#include <vector>

/**
 * Represents a surface in a collision problem.
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
            float n1 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * this->dfunc(x);
            float n2 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * 1;
            std::vector<float> normal_force = std::vector<float>{n1, n2};
            std::vector<float> aN = std::vector<float>{alpha * normal_force[0], alpha * normal_force[1]};
            std::vector<float> Vout = std::vector<float>{Vinx + aN[0], Viny + aN[1]};
            return std::vector<float>{x, Vout[0], Vout[1]};
        }

        /**
         * Sets the 'a' or elasticity value of the surface.
        */
        void setAlpha(float alpha) { this->alpha = alpha; }

    private:
        // The elasticity value of the surface
        float alpha;
};

#endif // SURFACE_H