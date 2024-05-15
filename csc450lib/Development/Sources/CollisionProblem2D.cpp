#include <CollisionProblem2D.h>
#include <string>

using namespace csc450lib_calc;


/** MortarFunc1D methods */

MortarFunc1D::MortarFunc1D(float azimuth, float elevation, float x0, float y0, float z0, float velocity)
: Vx0(velocity * cosf(azimuth) * cosf(elevation)),
  Vy0(velocity * sinf(azimuth) * cosf(elevation)),
  Vz0(velocity * sinf(elevation)), velocity(velocity),
  x0(x0), y0(y0), z0(z0), azimuth(azimuth) {}

float MortarFunc1D::func(float t) const
{
    std::vector<float> m_pos(2);
    // u coordinate
    m_pos[0] = 0 + this->velocity * t;
    // z coordiomate
    m_pos[1] = this->z0 + Vz0 * t - 0.5 * 9.8 * t * t;

    return m_pos[1];
}

std::vector<float> MortarFunc1D::getPositionAndVelocity(float t) const {
    std::vector<float> m_pos(4);
    // u coordinate
    m_pos[0] = 0 + this->velocity * t;
    // z coordinate
    m_pos[1] = this->z0 + this->Vz0 * t - 0.5 * 9.8 * t * t;
    // Vu
    m_pos[2] = this->velocity;
    // Vz
    m_pos[3] = this->Vz0 - (9.8 * t);

    return m_pos;
}

std::vector<float> MortarFunc1D::getCoordinates(float t) const {
    std::vector<float> m_pos(3);
    // x coordinate
    m_pos[0] = this->x0 + this->Vx0 * t;
    // y coordinate
    m_pos[1] = this->y0 + this->Vy0 * t;
    // z coordinate
    m_pos[2] = this->z0 + this->Vz0 * t - 0.5 * 9.8 * t * t;

    return m_pos;
}



/** Base surface2D methods */

Surface2D::Surface2D(float alpha) : FunctionND(2) {
    this->a = alpha;
}

void Surface2D::setAlpha(float alpha) {
    this->a = alpha;
}



/** CollisionProblem2D methods */

CollisionProblem2D::CollisionProblem2D(MortarFunc1D* mortar, Surface2D* surface)
: mortar(mortar), surface(surface) {}

float CollisionProblem2D::func(float t) const {
    float position = this->mortar->func(t);
    float current_x = this->mortar->getX0() + (position * cosf(this->mortar->getAzimuth()));
    float current_y = this->mortar->getY0() + (position * sinf(this->mortar->getAzimuth()));
    float surface_height = this->surface->func({current_x, current_y});
    return position - surface_height;
}



/** FlatSurface2D methods */

FlatSurface2D::FlatSurface2D(float alpha) : Surface2D(alpha) {}

float FlatSurface2D::func(const std::vector<float>& x) {
    return 1;
}



/** EasySurface2D methods */

EasySurface2D::EasySurface2D(float alpha) : Surface2D(alpha) {}

float EasySurface2D::func(const std::vector<float>& x) {
    return (x[0] + x[1]) / 10;
}



/** HardSurface2D methods */

HardSurface2D::HardSurface2D(float alpha) : Surface2D(alpha) {}

float HardSurface2D::func(const std::vector<float>& x) {
    return sinf(x[0]) + (x[1] / 10) + 10;
}