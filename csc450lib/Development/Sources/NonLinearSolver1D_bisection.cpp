#include "NonLinearSolver1D_bisection.h"
#include <cstdlib>

NonLinearSolverRecord1D NonLinearSolver1D_bisection::solve(std::shared_ptr<Function1D> func, float a, float b, int n, float tolerance) {
    int iterations = 0;
    bool success;
    float x = (a + b) / 2;
    float f = func.get()->func(x);
    while (abs(f) > tolerance && iterations < n) {
        if (f * func.get()->func(a) < 0) {
            b = x;
        } else {
            a = x;
        }
        x = (a + b) / 2;
        f = func.get()->func(x);
        iterations++;
    }
    if (iterations == n) {
        success = false;
    } else {
        success = true;
    }
    return NonLinearSolverRecord1D(x, func.get()->func(x), iterations, success);
}