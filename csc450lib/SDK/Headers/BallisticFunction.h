#include <Function1D.h>
#include <vector>
#ifndef BALLISTICFUNCTION_H
#define BALLISTICFUNCTION_H

class BallisticFunction /**: public csc450lib_calc::Function1D*/ {
    public:
        // Public methods for the interface
        BallisticFunction(float x0, float y0, float Vx0, float Vy0);
        std::vector<float> getPosition(float t) const;
        std::vector<float> getPositionAndVelocity(float t) const;

        /** Only needed if defining Ballistic Function as a subclass of Function1D */
        // float func(float x) const;
        // float dfunc(float x) const;
        // std::vector<float> getAltitudeAndVelocity(float x) const;
        // std::shared_ptr<std::string> getExpressionMMA() const;
        // bool derivativeIsExact() const;
        // bool secondDerivativeIsExact() const;

    private:
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