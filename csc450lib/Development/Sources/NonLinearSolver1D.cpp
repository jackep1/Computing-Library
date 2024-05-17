#include <NonLinearSolver1D.h>
#include <cstdlib>

using namespace csc450lib_calc;


std::vector<float> NonLinearSolver1D::find_search_bracket_collision(float TOL, std::shared_ptr<BallisticFunction> ballistic, std::shared_ptr<CollisionProblem1D> flight)
{
    // Start left end of bracket at tolerance
    float a = TOL;
    float peak_time = ballistic.get()->getPositionAndVelocity(0)[3] / 9.8;
    if (peak_time <= 0) {
        peak_time = 0.01;
    }

    // Right end of bracket is at point symmetric to start
    float b = (peak_time * 2) - a;

    // Determine sign of right bracket, if negative, find last positive value
    float right_height = ballistic.get()->getPosition(b)[1];
    
    // If right bracket is positive, increase b by 10% until negative value is found
    while (right_height > 0) {
        if (a < b) {
            a = b;
        }
        b *= 1.1;
        right_height = ballistic.get()->getPosition(b)[1];
        // std::cout << "Revised bracket: " << a << " - " << b << std::endl;
    }

    return std::vector<float>{a, b};
}

NonLinearSolverRecord1D NonLinearSolver1D_bisection::solve(std::shared_ptr<Function1D> f, float a, float b, int n, float tol) const {

    int iterations = 0;
    bool success = false;

    // loop initialization
    float fa = f.get()->func(a);
    float fb = f.get()->func(b);
    float c = (a + b) / 2;
    float fc = f.get()->func(c);

    // keep going until the search bracket is too small
    // or until we run into machine precision limitations
    while (b - a > (2 * tol) &&
           c != a &&
           c != b &&
           iterations < n) {
        if (fa * fc > 0) {
            a = c;
            fa = fc;
        } else if (fc != 0) {
            b = c;
            fb = fc;
        } else {
            return NonLinearSolverRecord1D(c, fc, iterations, true);
        }
        c = (a + b) / 2;
        fc = f.get()->func(c);
        iterations++;
    }
    if (iterations < n) {
        success = true;
    }

    return NonLinearSolverRecord1D(c, fc, iterations, success);
}

NonLinearSolverRecord1D NonLinearSolver1D_NewtonRaphson::solve(std::shared_ptr<Function1D> func, float x0, float blank, int n, float tolerance) const {

    int iterations = 0;
    bool success = true;

    // loop initialization
    float x = x0;
    float fx = func.get()->func(x0);
    float df = func.get()->dfunc(x0);
    
    while (x - x0 > (2 * tolerance) &&
           x != x0 &&
           iterations < n) {
        // find next x
        float xk1 = x - (fx / df);
        // find next f(x) and f'(x)
        float fx = func.get()->func(xk1);
        float df = func.get()->dfunc(xk1);
        
        // check if we are close enough to the solution
        // or if machine precision is reached
        if (abs(-fx / df) < tolerance) {
            break;
        }

        // update x
        iterations++;
        x = xk1;
    }

    // check if we found a solution
    if (iterations >= n) {
        success = false;
    }
    return NonLinearSolverRecord1D(x, func.get()->func(x), iterations, success);
}

NonLinearSolverRecord1D NonLinearSolver1D_secant::solve(std::shared_ptr<Function1D> func, float x0, float x1, int n, float tolerance) const {

    int iterations = 0;
    bool success = true;

    // loop initialization
    float num = func.get()->func(x1) * (x1 - x0);
    float denom = func.get()->func(x1) - func.get()->func(x0);

    while (abs(num / denom) > (2 * tolerance) &&
           iterations < n) {
        // find next x
        float x2 = x1 - (num / denom);
        // find next num and denom
        num = func.get()->func(x2) * (x2 - x1);
        denom = func.get()->func(x2) - func.get()->func(x1);

        // check if we are close enough to the solution
        // or if machine precision is reached
        if (abs(x2 - x1) < tolerance || x2 == x1) {
            break;
        }

        // update x
        x0 = x1;
        x1 = x2;
        iterations++;
    }

    // check if we found a solution
    if (iterations >= n) {
        success = false;
    }
    return NonLinearSolverRecord1D(x1, func.get()->func(x1), iterations, success);
}