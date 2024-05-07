#include <BallisticFunction.h>
#include <cmath>

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
BallisticFunction::BallisticFunction(float x0, float y0, float Vx0, float Vy0) {
    this->x0 = x0;
    this->y0 = y0;
    this->Vx0 = Vx0;
    this->Vy0 = Vy0;
}

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

// float BallisticFunction::func(float x) const {

// }

// float BallisticFunction::dfunc(float x) const {

// }

// std::vector<float> BallisticFunction::getAltitudeAndVelocity(float x) const {
//     return std::vector<float>{this->func(x), this->Vx0, this->Vy0};
// }

// std::shared_ptr<std::string> BallisticFunction::getExpressionMMA() const {
//     return std::make_shared<std::string>("BallisticFunction");
// }

// bool BallisticFunction::derivativeIsExact() const {
//     return false;
// }

// bool BallisticFunction::secondDerivativeIsExact() const {
//     return false;
// }