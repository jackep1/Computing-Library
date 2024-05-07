#include <iostream>
#include <fstream>
#include <chrono>
#include "Function1D.h"
#include "CSC450Lib.h"
#include "CosFunc.h"
#include "CosFuncNoDerivative.h"
#include "SinFunc.h"
#include "PolynomialFunction1D.h"
#include "Surface.h"
#include "EasySurface.h"
#include "HardSurface.h"
#include "BallisticFunction.h"
#include "CollisionProblem.h"
#include <NonLinearSolver1D.h>
#include <NonLinearSolver1D_bisection.h>
#include <NonLinearSolver1D_NewtonRaphson.h>
#include <NonLinearSolver1D_secant.h>
#include <CSC450Exception.h>

using namespace std;
using namespace csc450lib;
using namespace csc450lib_calc;

int main(int argc, const char* argv[])
{
    float inf = INFINITY;
    float ninf = -INFINITY;

    ofstream cosExactFile("../../../../MMA Files/cosd.txt");
    ofstream cosApproxFile("../../../../MMA Files/cosad.txt");
    // ofstream sinFile("../../../../MMA Files/sind.txt");

    ofstream pdFile("../../../../MMA Files/pd.txt");
    // ofstream p2File("../../../../MMA Files/p2d.txt");


    // Section for testing derivative functionality begins with
    // the cosine function defined for positive numbers, one
    // version with the derivative exactly implemented and one without
    CosFunc f (0, inf);
    CosFuncNoDerivative g (0, inf);
    shared_ptr<PolynomialFunction1D> h = make_shared<PolynomialFunction1D>(vector<float>{1, 2, 3});
    cout << "Is CosFunc f's derivative method exact or approximate: ";
    if (f.derivativeIsExact()) {
        cout << "Exact" << endl;
    } else {
        cout << "Approximate" << endl;
    }
    cout << "Is CosFuncNoDerivative g's derivative method exact or approximate: ";
    if (g.derivativeIsExact()) {
        cout << "Exact" << endl;
    } else {
        cout << "Approximate" << endl;
    }
    cout << "Is PolynomialFunction1D h's derivative method exact or approximate: ";
    if (h->derivativeIsExact()) {
        cout << "Exact" << endl;
    } else {
        cout << "Approximate" << endl;
    }

    // Calculate the derivative at x = 1 and time it
    auto start = chrono::high_resolution_clock::now();
    cout << "CosFunc f's derivative at x = 1: " << f.dfunc(1) << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto exact_duration = std::chrono::duration_cast<chrono::microseconds>(stop - start);

    // Calculate derivative at x = 1 using approximation and time it.
    start = chrono::high_resolution_clock::now();
    cout << "CosFuncNoDerivative g's derivative at x = 1: " << g.dfunc(1) << endl;
    stop = chrono::high_resolution_clock::now();
    auto approx_duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // Calculate the derivative at x = 1 using approximation and time it.
    start = chrono::high_resolution_clock::now();
    cout << "PolynomialFunction1D h's derivative at x = 1: " << h->dfunc(1) << endl;
    stop = chrono::high_resolution_clock::now();
    auto polynomial_approx_duration = chrono::duration_cast<chrono::microseconds>(stop - start);



    // Calculate the derivative of several cosine points and write to file
    for (float x = 0; x < 10; x += 0.1) {
        try {
            cosExactFile << x << " " << f.dfunc(x) << endl;
        } catch (const csc450lib::CSC450Exception& e) {
            continue;
        }
    }

    // Calculate the approximate derivative of several cosine points and write to file
    for (float x = 0; x < 10; x += 0.1) {
        try {
            cosApproxFile << x << " " << g.dfunc(x) << endl;
        } catch (const csc450lib::CSC450Exception& e) {
            continue;
        }
    }

    // Calculate the derivative of several polynomial points and write to file
    for (float x = 0; x < 10; x += 0.1) {
        try {
            pdFile << x << " " << h->dfunc(x) << endl;
        } catch (const csc450lib::CSC450Exception& e) {
            continue;
        }
    }

    // Calculate the approximate derivative of several points along polynomial function and write to file
    cout << "Time to calculate exact derivative: " << exact_duration.count() << " microseconds" << endl;
    cout << "Time to calculate approximate derivative: " << approx_duration.count() << " microseconds" << endl;
    cout << "Time to calculate polynomial derivative: " << polynomial_approx_duration.count() << " microseconds" << endl;
    cout << "PolynomialFunction1D h's derivative at x = 1: " << h->dfunc(1) << endl;

    // Simple surfaces with different elasticity values
    // Defined as cos(x)/5
    EasySurface easy_elastic_surface(1);
    EasySurface easy_absorbant_surface(0.5);

    // Complex surfaces with different elasticity values
    // Defined as
    HardSurface hard_elastic_surface(1);
    HardSurface hard_absorbant_surface(0.5);
    
    // Define an initial ballistic function where
    // projectile is launched directly sideways at
    // a height of 10 units and a velocity of 10 units
    BallisticFunction ballistic(0, 10, 10, 0);

    // Define a collision problem with the perfectly elastic simple surface
    // and the ballistic function
    CollisionProblem easy_elastic_collision(&ballistic, &easy_elastic_surface);

    // Determine a search bracket for the location of the collision
    float TOL = 0.01;
    float left = 0.01;
    float peak_time = ballistic.getPositionAndVelocity(0)[3] / 9.8;
    float right = peak_time * 2;
    while (easy_elastic_collision.func(right) > 0) {
        right *= 1.1;
    }

    
    

    return 0;
}