#include "NonLinearSolver1D_NewtonRaphson.h"
#include <cstdlib>

NonLinearSolverRecord1D NonLinearSolver1D_NewtonRaphson::solve(std::shared_ptr<Function1D> func, float a, float b, int n, float tolerance) {
    float iterations = 0;
    bool success;
    while (iterations < n) {
        float f = func.get()->func(a);
        float df = func.get()->dfunc(a);
        float dx = -f / df;
        a += dx;
        if (abs(dx) < tolerance) {
            break;
        }
        iterations++;
    }
    if (iterations == n) {
        success = false;
    } else {
        success = true;
    }
    return NonLinearSolverRecord1D(a, func.get()->func(a), iterations, success);
}