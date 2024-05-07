#include "NonLinearSolver1D_bisection.h"
#include <cstdlib>

/**
 * Uses the non-linear bisection method to solve the given function
 * 
 * @param f the function to solve
 * @param a the lower end of the search bracket
 * @param b the upper end of the search bracket
 * @param n the maximum number of iterations to perform
 * @param tol the tolerance to use when determining if the solution is close enough
 * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
*/
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