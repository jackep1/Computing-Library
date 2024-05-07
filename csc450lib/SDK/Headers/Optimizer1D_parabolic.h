#ifndef OPTIMIZER1D_PARABOLIC_H
#define OPTIMIZER1D_PARABOLIC_H

#include <Optimizer1D.h>

using namespace csc450lib_calc;

class Optimizer1D_parabolic : public Optimizer1D {
    public:
        // Copy and move constructors not needed
        virtual ~Optimizer1D_parabolic() = default;
        Optimizer1D_parabolic(const Optimizer1D_parabolic& obj) = delete;
        Optimizer1D_parabolic(Optimizer1D_parabolic&& obj) = delete;
        Optimizer1D_parabolic& operator =(const Optimizer1D_parabolic& obj) = delete;
        Optimizer1D_parabolic& operator =(Optimizer1D_parabolic&& obj) = delete;

        // Public methods
        Optimizer1D_parabolic(std::shared_ptr<Function1D> f) : Optimizer1D(f) {};
        OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_PARABOLIC_H