#ifndef NONLINEARSOLVER1D_BISECTION_H

#include "NonLinearSolver1D.h"

class NonLinearSolver1D_bisection : public NonLinearSolver1D {
    public:
        NonLinearSolverRecord1D solve(std::shared_ptr<Function1D> func, float a, float b, int n, float tol) const;
};

#endif