#ifndef NONLINEARSOLVER1D_NEWTONRAPHSON_H
#define NONLINEARSOLVER1D_NEWTONRAPHSON_H

#include "NonLinearSolver1D.h"

using namespace csc450lib_calc;

class NonLinearSolver1D_NewtonRaphson : public NonLinearSolver1D {
    public:
        NonLinearSolverRecord1D solve(std::shared_ptr<Function1D> func, float a, float b, int n, float tol);};

#endif