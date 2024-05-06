#include <Function1D.h>
#include "NonLinearSolverRecord1D.h"
#ifndef NONLINEARSOLVER1D_H
#define NONLINEARSOLVER1D_H

using namespace csc450lib_calc;

class NonLinearSolver1D {

    public:
        // Copy and move constructors not needed
        virtual ~NonLinearSolver1D() = default;
        NonLinearSolver1D(const NonLinearSolver1D& obj) = delete;
        NonLinearSolver1D(NonLinearSolver1D&& obj) = delete;
        NonLinearSolver1D& operator =(const NonLinearSolver1D& obj) = delete;
        NonLinearSolver1D& operator =(NonLinearSolver1D&& obj) = delete;

        // Public methods for the interface
        NonLinearSolver1D() = default;
        // For solving the given function
        virtual NonLinearSolverRecord1D solve(std::shared_ptr<Function1D> f, float a, float b, int n, float tol) const = 0;
};

#endif