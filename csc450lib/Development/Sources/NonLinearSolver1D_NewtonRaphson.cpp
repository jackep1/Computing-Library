#include "NonLinearSolver1D_NewtonRaphson.h"
#include <cstdlib>

/**
 * Uses the non-linear Newton-Raphson method to solve the given function
 * 
 * @param func the function to solve
 * @param a the lower end of the search bracket
 * @param b the upper end of the search bracket
 * @param n the maximum number of iterations to perform
 * @param tolerance the tolerance to use when determining if the solution is close enough
 * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
*/
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