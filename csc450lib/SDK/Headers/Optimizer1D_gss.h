#ifndef OPTIMIZER1D_GSS_H
#define OPTIMIZER1D_GSS_H

#include <Optimizer1D.h>

using namespace csc450lib_calc;

class Optimizer1D_gss : public Optimizer1D {
    public:
        // Copy and move constructors not needed
        virtual ~Optimizer1D_gss() = default;
        Optimizer1D_gss(const Optimizer1D_gss& obj) = delete;
        Optimizer1D_gss(Optimizer1D_gss&& obj) = delete;
        Optimizer1D_gss& operator =(const Optimizer1D_gss& obj) = delete;
        Optimizer1D_gss& operator =(Optimizer1D_gss&& obj) = delete;

        // Public methods
        Optimizer1D_gss(std::shared_ptr<Function1D> f) : Optimizer1D(f) {};
        OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_GSS_H