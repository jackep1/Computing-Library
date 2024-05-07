#include "NonLinearSolver1D_secant.h"
#include <cstdlib>

/**
 * Uses the non-linear secant method to solve the given function
 * 
 * @param func the function to solve
 * @param x0 the first initial guess
 * @param x1 the second initial guess
 * @param n the maximum number of iterations to perform
 * @param tolerance the tolerance to use when determining if the solution is close enough
 * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
*/
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