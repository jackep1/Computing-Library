#include <BallisticFunction.h>

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