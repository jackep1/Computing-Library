#ifndef BALLISTICFUNCTION_H
#define BALLISTICFUNCTION_H

#include <Function1D.h>
#include <vector>

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