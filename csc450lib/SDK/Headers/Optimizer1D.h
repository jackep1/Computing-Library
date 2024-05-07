#include <Function1D.h>
#include <OptimizerRecord1D.h>
#ifndef OPTIMIZER1D_H
#define OPTIMIZER1D_H

using namespace csc450lib_calc;

class Optimizer1D {
    public:
        // Copy and move constructors not needed
        virtual ~Optimizer1D() = default;
        Optimizer1D(const Optimizer1D& obj) = delete;
        Optimizer1D(Optimizer1D&& obj) = delete;
        Optimizer1D& operator =(const Optimizer1D& obj) = delete;
        Optimizer1D& operator =(Optimizer1D&& obj) = delete;

        // Public methods
        Optimizer1D(std::shared_ptr<Function1D> f) { this->f = f; }
        void setFunction(std::shared_ptr<Function1D> f) { this->f = f;}
        std::shared_ptr<const Function1D> getFunction() const { return f; };
        virtual OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const = 0;

        std::shared_ptr<Function1D> f;
};

#endif // OPTIMIZER1D_H