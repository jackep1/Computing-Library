#include "Optimizer1D.h"
#ifndef OPTIMIZER1D_STEEPESTDESCENT_H
#define OPTIMIZER1D_STEEPESTDESCENT_H

class Optimizer1D_steepestDescent : public Optimizer1D {
    public:
        // Copy and move constructors not needed
        virtual ~Optimizer1D_steepestDescent() = default;
        Optimizer1D_steepestDescent(const Optimizer1D_steepestDescent& obj) = delete;
        Optimizer1D_steepestDescent(Optimizer1D_steepestDescent&& obj) = delete;
        Optimizer1D_steepestDescent& operator =(const Optimizer1D_steepestDescent& obj) = delete;
        Optimizer1D_steepestDescent& operator =(Optimizer1D_steepestDescent&& obj) = delete;

        // Public methods
        Optimizer1D_steepestDescent(std::shared_ptr<Function1D> f) : Optimizer1D(f) {};
        OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_STEEPESTDESCENT_H