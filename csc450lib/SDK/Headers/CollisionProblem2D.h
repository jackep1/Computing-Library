#include <Function1D.h>
#include <VectorFunction1D.h>
#include <FunctionND.h>
#include <cmath>
#include <vector>


#ifndef COLLISIONPROBLEM2D_H
#define COLLISIONPROBLEM2D_H

class CollisionProblem2D : public csc450lib_calc::Function1D {
    public:
        CollisionProblem2D(MortarFunc1D* mortar, Surface2D* surface);
        float func(float t) const;

        bool derivativeIsExact() const { return false;}
        bool secondDerivativeIsExact() const { return false; }
        std::shared_ptr<std::string> getExpressionMMA() const { return nullptr; }

    protected:
        MortarFunc1D* mortar;
        Surface2D* surface;
};

#endif // COLLISIONPROBLEM2D_H



// #ifndef MORTARFUNCCOORDINATES_H
// #define MORTARFUNCCOORDINATES_H

// class MortarFuncCoordinates : public csc450lib_calc::VectorFunction1D {
    
//     public:
//         MortarFuncCoordinates(float azimuth, float elevation, float x0, float y0, float velocity);
//         std::vector<float> func(float t);
//     protected:
//         // The initial x position
//         float x0;
//         // The initial y position
//         float y0;
//         // The initial z position
//         float z0;
//         // The initial x-velocity
//         float Vx0;
//         // The initial y-velocity
//         float Vy0;
//         // The initial z-velocity
//         float Vz0;
// };

// #endif /// MORTARFUNCCOORDINATES_H



#ifndef MORTARFUNC1D_H
#define MORTARFUNC1D_H

class MortarFunc1D : public csc450lib_calc::Function1D {
    
    public:
        MortarFunc1D(float azimuth, float elevation, float x0, float y0, float velocity);
        std::vector<float> func(float t);
        std::vector<float> getPosition(float t) const;
        std::vector<float> getPositionAndVelocity(float t) const;
        float dfunc(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
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
        virtual float h(float x, float y) = 0;
};

#endif // MORTARFUNC1D_H



#ifndef SURFACE2D_H
#define SURFACE2D_H

class Surface2D : public csc450lib_calc::FunctionND {
    
    public:
        Surface2D(float alpha);
        std::vector<float> getOutgoingVelocity(float x, float y, float Vinx, float Viny) const;
        void setAlpha(float alpha);
    private:
        float a;
};

#endif // SURFACE2D_H



#ifndef FLATSURFACE2D_H
#define FLATSURFACE2D_H

class FlatSurface2D : public Surface2D {
    
    public:
        FlatSurface2D(float alpha);
        float func(const std::vector<float>& x);
};

#endif // FLATSURFACE2D_H



#ifndef EASYSURFACE2D_H
#define EASYSURFACE2D_H

class EasySurface2D : public Surface2D {
    
    public:
        EasySurface2D(float alpha);
        float func(const std::vector<float>& x);
};

#endif // EASYSURFACE2D_H



#ifndef HARDSURFACE2D_H
#define HARDSURFACE2D_H

class HardSurface2D : public Surface2D {
    
    public:
        HardSurface2D(float alpha);
        float func(const std::vector<float>& x);
};

#endif // HARDSURFACE2D_H