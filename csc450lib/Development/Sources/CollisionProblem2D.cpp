#include <CollisionProblem2D.h>
#include <string>

using namespace csc450lib_calc;

/** CollisionProblem2D methods */

/**
 * Constructor for the CollisionProblem2D class that initializes the mortar
 * and the surface.
 * 
 * @param mortar the mortar function
 * @param surface the surface function
 * @return a CollisionProblem2D object
*/
CollisionProblem2D::CollisionProblem2D(MortarFunc1D* mortar, Surface2D* surface)
: mortar(mortar), surface(surface) {}

/**
 * Gets the height of the mortar above the surface at time t.
 * 
 * @param t the time to get the height at
 * @return the height of the mortar above the surface at time t
*/
float CollisionProblem2D::func(float t) const {
    std::vector<float> position = this->mortar->func(t);
    float surface_height = this->surface->func(position[0]);
    return position[1] - surface_height;
}



/** MortarFunc1D methods */

// MortarFunc has been initialized with initial z0 (implociot;ly u0=0) vu, vz

/**
 * Constructor for the mortar that initializes using azimuth angle
 * and elevation angle. Azimuth must be in the range [0, 2pi] and
 * elevation must be in the range [0, pi/2].
 * 
 * @param azimuth the azimuth angle in radians
 * @param elevation the elevation angle in radians
 * @param x0 the initial x position
 * @param y0 the initial y position
 * @param velocity the initial velocity
*/
MortarFunc1D::MortarFunc1D(float azimuth, float elevation, float x0, float y0, float velocity)
: Vx0(velocity * cosf(azimuth) * cosf(elevation)),
  Vy0(velocity * sinf(azimuth) * cosf(elevation)),
  Vz0(velocity * sinf(elevation)), velocity(velocity),
  x0(x0), y0(y0), z0(h(x0, y0)) {}


/**
 * Gets the position of the object at time t in the u-z plane.
 * 
 * @param t the time to get the position at
 * @return a vector containing {u, z} of the object at time t
*/
std::vector<float> MortarFunc1D::func(float t)
{
    std::vector<float> m_pos(2);
    // u coordinate
    m_pos[0] = 0 + this->velocity * t;
    // z coordiomate
    m_pos[1] = this->z0 + Vz0 * t - 0.5 * 9.8 * t * t;

    return m_pos;
}

/**
 * Gets the position and velocity of the object at time t in the u-z plane.
 * 
 * @param t the time to get the position and velocity at
 * @return a vector containing {u, z, Vu, Vz} of the object at time t
*/
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


// class IntersectionFunc : public Function1D {

//     public:

//         IntersectionFunc(shared_ptr<MortarFunc> mortar, shared_ptr<Function1DFromND> surfaceSection)

//         float func(float t) {
//                 //get um, zm from mortar

//                 return zm - surfaceSection.func(um);

//         }

// }


/** Base surface2D methods */

/**
 * Constructor for the Surface2D class that initializes the elasticity value.
*/
Surface2D::Surface2D(float alpha) : FunctionND(2) {
    this->a = alpha;
}

/**
 * Gets the outgoing velocity of the object after a collision with the surface.
 * 
 * @param
*/


/**
 * Resets the elasticity value of the surface.
 * 
 * @param alpha the new elasticity value
*/
void Surface2D::setAlpha(float alpha) {
    this->a = alpha;
}



/**
 * Constructor for the FlatSurface2D class that initializes the elasticity value.
 * 
 * @param alpha the elasticity value of the surface
 * @return a FlatSurface2D object
*/
FlatSurface2D::FlatSurface2D(float alpha) : Surface2D(alpha) {}

/**
 * Gets the height of the surface at a given x and y value.
 * 
 * @param x a vector containing {x, y}
 * @return 1, since the height of the surface at {x, y} is constant/flat
*/ 
float FlatSurface2D::func(const std::vector<float>& x) {
    return 1;
}



/** EasySurface2D methods */

/**
 * Constructor for the EasySurface2D class that initializes the elasticity value.
 * 
 * @param alpha the elasticity value of the surface
 * @return an EasySurface2D object
*/
EasySurface2D::EasySurface2D(float alpha) : Surface2D(alpha) {}

/**
 * Gets the height of the surface at a given x and y value.
 * 
 * @param x the x value
 * @param y the y value
 * @return the height of the surface at {x, y}
*/
float EasySurface2D::func(const std::vector<float>& x) {
    return (x[0] + x[1]) / 10;
}



/** HardSurface2D methods */

/**
 * Constructor for the HardSurface2D class that initializes the elasticity value.
 * 
 * @param alpha the elasticity value of the surface
 * @return a HardSurface2D object
*/
HardSurface2D::HardSurface2D(float alpha) : Surface2D(alpha) {}

/**
 * Gets the height of the surface at a given x and y value.
 * 
 * @param x the x value
 * @param y the y value
 * @return the height of the surface at {x, y}
*/
float HardSurface2D::func(const std::vector<float>& x) {
    return sinf(x[0]) + (x[1] / 10) + 10;
}