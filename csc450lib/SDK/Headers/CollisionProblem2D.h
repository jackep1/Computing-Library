#include <Function1D.h>
#include <VectorFunction1D.h>
#include <FunctionND.h>
#include <cmath>
#include <vector>

#ifndef MORTARFUNC1D_H
#define MORTARFUNC1D_H

class MortarFunc1D : public csc450lib_calc::Function1D {
    
    public:
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
        MortarFunc1D(float azimuth, float elevation, float x0, float y0, float z0, float velocity);

        /**
         * Gets the position of the object at time t in the u-z plane.
         * 
         * @param t the time to get the position at
         * @return a vector containing {u, z} of the object at time t
        */
        float func(float t) const;

        /**
         * Gets the position and velocity of the object at time t in the u-z plane.
         * 
         * @param t the time to get the position and velocity at
         * @return a vector containing {u, z, Vu, Vz} of the object at time t
        */
        std::vector<float> getPositionAndVelocity(float t) const;

        /**
         * Gets the coordinates {x, y, z} of the object at time t.
         * 
         * @param t the time to get the coordinates at
         * @return a vector containing {x, y, z} of the object at time t
        */
        std::vector<float> getCoordinates(float t) const;
        float dfunc(float x) const { return 0; }
        bool derivativeIsExact() const { return false; }
        bool secondDerivativeIsExact() const { return false; }
        std::shared_ptr<std::string> getExpressionMMA() const { return nullptr; }

        // Getters
        float getX0() const { return x0; }
        float getY0() const { return y0; }
        float getZ0() const { return z0; }
        float getVx0() const { return Vx0; }
        float getVy0() const { return Vy0; }
        float getVz0() const { return Vz0; }
        float getVelocity() const { return velocity; }
        float getAzimuth() const { return azimuth; }
    protected:
        // The initial x position
        float x0;
        // The initial y position
        float y0;
        // The initial z position
        float z0;
        // The initial x-velocity
        float Vx0;
        // The initial y-velocity
        float Vy0;
        // The initial z-velocity
        float Vz0;
        // The initial velocity
        float velocity;
        // The azimuth angle
        float azimuth;
};

#endif // MORTARFUNC1D_H



#ifndef SURFACE2D_H
#define SURFACE2D_H

class Surface2D : public csc450lib_calc::FunctionND {
    
    public:
        /**
         * Constructor for the Surface2D class that initializes the elasticity value.
        */
        Surface2D(float alpha);

        /**
         * Gets the outgoing velocity of the object after a collision with the surface.
         * 
         * @param
        */
        std::vector<float> getOutgoingVelocity(float x, float y, float Vinx, float Viny) const;

        /**
         * Resets the elasticity value of the surface.
         * 
         * @param alpha the new elasticity value
        */
        void setAlpha(float alpha);
    private:
        // The elasticity value of the surface
        float a;
};

#endif // SURFACE2D_H



#ifndef COLLISIONPROBLEM2D_H
#define COLLISIONPROBLEM2D_H

class CollisionProblem2D : public csc450lib_calc::Function1D {

    public:
        /**
         * Constructor for the CollisionProblem2D class that initializes the mortar
         * and the surface.
         * 
         * @param mortar the mortar function
         * @param surface the surface function
         * @return a CollisionProblem2D object
        */
        CollisionProblem2D(MortarFunc1D* mortar, Surface2D* surface);

        /**
         * Gets the height of the mortar above the surface at time t.
         * 
         * @param t the time to get the height at
         * @return the height of the mortar above the surface at time t
        */
        float func(float t) const;

        bool derivativeIsExact() const { return false; }
        bool secondDerivativeIsExact() const { return false; }
        std::shared_ptr<std::string> getExpressionMMA() const { return nullptr; }

    protected:
        // The function of the mortar's position
        MortarFunc1D* mortar;
        // The function of the surface's height
        Surface2D* surface;
};

#endif // COLLISIONPROBLEM2D_H



#ifndef FLATSURFACE2D_H
#define FLATSURFACE2D_H

class FlatSurface2D : public Surface2D {
    
    public:
        /**
         * Constructor for the FlatSurface2D class that initializes the elasticity value.
         * 
         * @param alpha the elasticity value of the surface
         * @return a FlatSurface2D object
        */
        FlatSurface2D(float alpha);

        /**
         * Gets the height of the surface at a given x and y value.
         * 
         * @param x a vector containing {x, y}
         * @return 1, since the height of the surface at {x, y} is constant/flat
        */ 
        float func(const std::vector<float>& x);
};

#endif // FLATSURFACE2D_H



#ifndef EASYSURFACE2D_H
#define EASYSURFACE2D_H

class EasySurface2D : public Surface2D {
    
    public:
        /**
         * Constructor for the EasySurface2D class that initializes the elasticity value.
         * 
         * @param alpha the elasticity value of the surface
         * @return an EasySurface2D object
        */
        EasySurface2D(float alpha);

        /**
         * Gets the height of the surface at a given x and y value.
         * 
         * @param x the x value
         * @param y the y value
         * @return the height of the surface at {x, y}
        */
        float func(const std::vector<float>& x);
};

#endif // EASYSURFACE2D_H



#ifndef HARDSURFACE2D_H
#define HARDSURFACE2D_H

class HardSurface2D : public Surface2D {
    
    public:
        /**
         * Constructor for the HardSurface2D class that initializes the elasticity value.
         * 
         * @param alpha the elasticity value of the surface
         * @return a HardSurface2D object
        */
        HardSurface2D(float alpha);

        /**
         * Gets the height of the surface at a given x and y value.
         * 
         * @param x the x value
         * @param y the y value
         * @return the height of the surface at {x, y}
        */
        float func(const std::vector<float>& x);
};

#endif // HARDSURFACE2D_H