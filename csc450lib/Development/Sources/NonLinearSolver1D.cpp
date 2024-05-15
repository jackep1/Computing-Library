#include <NonLinearSolver1D.h>
#include <cstdlib>

using namespace csc450lib_calc;


NonLinearSolverRecord1D NonLinearSolver1D_bisection::solve(std::shared_ptr<Function1D> f, float a, float b, int n, float tol) const {
    int iterations = 0;
    bool success;
    float x = (a + b) / 2;
    float f0 = f.get()->func(x);
    while (abs(f0) > tol && iterations < n) {
        if (f0 * f.get()->func(a) < 0) {
            b = x;
        } else {
            a = x;
        }
        x = (a + b) / 2;
        f0 = f.get()->func(x);
        iterations++;
    }
    if (iterations == n) {
        success = false;
    } else {
        success = true;
    }
    return NonLinearSolverRecord1D(x, f.get()->func(x), iterations, success);
}

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

NonLinearSolverRecord1D NonLinearSolver1D_secant::solve(std::shared_ptr<Function1D> func, float x0, float x1, int n, float tolerance) {
    float solution = 0;
    int iterations = 0;
    bool success;
    while (iterations < n) {
        float num = func.get()->func(x1) * (x1 - x0);
        float denom = func.get()->func(x1) - func.get()->func(x0);
        float solution = x1 - num / denom;
        if (abs(solution - x1) < tolerance) {
            break;
        }
        x0 = x1;
        x1 = solution;
        iterations++;
    }
    if (iterations == n) {
        success = false;
    } else {
        success = true;
    }
    return NonLinearSolverRecord1D(solution, func.get()->func(solution), iterations, success);
}