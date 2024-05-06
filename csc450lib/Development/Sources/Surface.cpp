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
*/
std::vector<float> Surface::getOutgoingVelocity(float x, float Vinx, float Viny) const {
    float Voutx = Vinx * alpha;
    float Vouty = Viny * alpha;
    return std::vector<float>{x, Voutx, Vouty};
}