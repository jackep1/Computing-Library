#include <Surface.h>
#include <cmath>

/**
 * Sets the 'a' or elasticity value of the surface.
*/
void Surface::setAlpha(float alpha) {
    this->alpha = alpha;
}

// std::shared_ptr<std::string> Surface::getExpressionMMA() const {
//     return std::make_shared<std::string>("Surface");
// }

// bool Surface::derivativeIsExact() const {
//     return false;
// }

// bool Surface::secondDerivativeIsExact() const {
//     return false;
// }

/**
 * Gets the outgoing velocity of the object after a collision with the surface.
 * 
 * @param x the x position of the object
 * @param Vinx the x velocity of the object
 * @param Viny the y velocity of the object
 * @return a vector containing {x, Voutx, Vouty} of the object after the collision
*/
std::vector<float> Surface::getOutgoingVelocity(float x, float Vinx, float Viny) const {
    float Voutx = Vinx * alpha;
    float Vouty = Viny * alpha;
    return std::vector<float>{x, Voutx, Vouty};
}