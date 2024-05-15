#include <iostream>
#include <fstream>
#include <chrono>

#include <CSC450Lib.h>
#include <CSC450Exception.h>

#include <Function1D.h>
#include <ExampleFunc1D.h>

#include <CollisionProblem1D.h>

#include <NonLinearSolver1D.h>

using namespace std;
using namespace csc450lib;
using namespace csc450lib_calc;


int main(int argc, const char* argv[])
{
    float inf = INFINITY;
    float ninf = -INFINITY;

    ofstream cosExactFile("../../../../MMA Files/A2/cosd.txt");
    ofstream cosApproxFile("../../../../MMA Files/A2/cosad.txt");
    ofstream pdFile("../../../../MMA Files/A2/pd.txt");


    /** 
     * Section for testing derivative functionality begins with
     * the cosine function defined for positive numbers, one
     * version with the derivative exactly implemented and one without
    */
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
    auto exact_duration = chrono::duration_cast<chrono::microseconds>(stop - start);

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
    cosExactFile.close();

    // Calculate the approximate derivative of several cosine points and write to file
    for (float x = 0; x < 10; x += 0.1) {
        try {
            cosApproxFile << x << " " << g.dfunc(x) << endl;
        } catch (const csc450lib::CSC450Exception& e) {
            continue;
        }
    }
    cosApproxFile.close();

    // Calculate the derivative of several polynomial points and write to file
    for (float x = 0; x < 10; x += 0.1) {
        try {
            pdFile << x << " " << h->dfunc(x) << endl;
        } catch (const csc450lib::CSC450Exception& e) {
            continue;
        }
    }
    pdFile.close();

    // Calculate the approximate derivative of several points along polynomial function and write to file
    cout << "Time to calculate exact derivative: " << exact_duration.count() << " microseconds" << endl;
    cout << "Time to calculate approximate derivative: " << approx_duration.count() << " microseconds" << endl;
    cout << "Time to calculate polynomial derivative: " << polynomial_approx_duration.count() << " microseconds" << endl;
    cout << "PolynomialFunction1D h's derivative at x = 1: " << h->dfunc(1) << endl;


    /**
     * Section for finding five bounces off of a flat
     * and inelastic surface.
    */

    // Non-linear solver for finding the collision locations
    NonLinearSolver1D_bisection bisection_solver;

    // Flat surfaces with different elasticity values
    shared_ptr<FlatSurface1D> flat_elastic_surface = make_shared<FlatSurface1D>(1);
    FlatSurface1D flat_absorbant_surface(0.5);

    // Initial ballistic function where projectile
    // is launched from a height of 10 units with
    // both vertical and horizontal velocities of 10 units
    shared_ptr<BallisticFunction> ballistic = make_shared<BallisticFunction>(0, 10, 10, 10);

    // Open files for writing bounce data
    ofstream flat_bounce1_File("../../../../MMA Files/A2/flat_bounce1.txt");
    ofstream flat_bounce2_File("../../../../MMA Files/A2/flat_bounce2.txt");
    ofstream flat_bounce3_File("../../../../MMA Files/A2/flat_bounce3.txt");
    ofstream flat_bounce4_File("../../../../MMA Files/A2/flat_bounce4.txt");
    ofstream flat_bounce5_File("../../../../MMA Files/A2/flat_bounce5.txt");
    vector<ofstream*> flat_bounces = {&flat_bounce1_File, &flat_bounce2_File, &flat_bounce3_File, &flat_bounce4_File, &flat_bounce5_File};
    vector<vector<float>> trajectory;

    for (int i = 0; i < 5; i++) {

        // Define a collision problem with the perfectly elastic
        // simple surface and the ballistic function
        shared_ptr<CollisionProblem1D> flight = make_shared<CollisionProblem1D>(ballistic, flat_elastic_surface);
        // cout << "Flight created" << endl;

        // Determine a search bracket for the location of the collision
        vector<float> search_bracket = bisection_solver.find_search_bracket_collision(0.01, ballistic, flight);
        // cout << "Search bracket found" << endl;


        // Find the exact time of collision
        NonLinearSolverRecord1D bounce = bisection_solver.solve(static_pointer_cast<csc450lib_calc::Function1D>(flight), search_bracket[0], search_bracket[1], 100, 0.01);
        if (!bounce.getIsSuccess()) {
            cout << "Bisection failed to find bounce location" << endl;
            exit(1);
        }
        // cout << "Time of bounce found" << endl;

        // Use the ballistic function info and bounce location to
        // find 10 points along the trajectory of the projectile
        float time_interval = bounce.getValStar() / 10;
        for (int j = 0; j < 10; j++) {
            trajectory.push_back(ballistic.get()->getPosition(time_interval * j));
        }

        // Write the trajectory to a file
        for (int j = 0; j < 10; j++) {
            *flat_bounces[i] << trajectory[j][0] << " " << trajectory[j][1] << endl;
        }
        cout << "Trajectory number " << i + 1 << " created and added to file" << endl;

        // Use the bounce information to define a new ballistic function
        // where the projectile is launched from the bounce location with
        // new position and velocity info
        vector<float> in_info = ballistic.get()->getPositionAndVelocity(bounce.getValStar());
        vector<float> out_info = flat_elastic_surface.get()->getOutgoingVelocity(in_info[0], in_info[2], in_info[3]);

        // Set the new ballistic function
        ballistic = make_shared<BallisticFunction>(out_info[0], out_info[1], out_info[2], out_info[3]);
        // cout << "Ballistic function updated" << endl;
    }
    
    /**
     * Section for finding five bounces off of a simple surface
     * with perfect elasticity.
    */

    /**
    // Simple surfaces with different elasticity values
    EasySurface easy_elastic_surface(1);
    EasySurface easy_absorbant_surface(0.5);

    // Define an initial ballistic function where
    // projectile is launched directly sideways at
    // a height of 10 units and a velocity of 10 units
    BallisticFunction ballistic2(0, 10, 10, 0);

    // Open files for writing bounce data
    ofstream easy_bounce1_File("../../../../MMA Files/easy_bounce1.txt");
    ofstream easy_bounce2_File("../../../../MMA Files/easy_bounce2.txt");
    ofstream easy_bounce3_File("../../../../MMA Files/easy_bounce3.txt");
    ofstream easy_bounce4_File("../../../../MMA Files/easy_bounce4.txt");
    ofstream easy_bounce5_File("../../../../MMA Files/easy_bounce5.txt");
    vector<ofstream*> easy_bounces = {&easy_bounce1_File, &easy_bounce2_File, &easy_bounce3_File, &easy_bounce4_File, &easy_bounce5_File};

    for (int i = 0; i < 5; i++) {

        // Define a collision problem with the perfectly elastic
        // simple surface and the ballistic function
        shared_ptr<CollisionProblem> flight = make_shared<CollisionProblem>(&ballistic2, &easy_elastic_surface);
        // cout << "Flight created" << endl;

        // Determine a search bracket for the location of the collision
        vector<float> search_bracket = find_search_bracket(0.01, ballistic2, flight);
        // cout << "Search bracket found" << endl;


        // Find the exact time of collision
        NonLinearSolverRecord1D bounce = bisection_solver.solve(static_pointer_cast<csc450lib_calc::Function1D>(flight), search_bracket[0], search_bracket[1], 100, 0.01);
        if (!bounce.isSuccess) {
            cout << "Bisection failed to find bounce location" << endl;
            exit(1);
        }
        // cout << "Time of bounce found" << endl;

        // Use the ballistic function info and bounce location to
        // find 10 points along the trajectory of the projectile
        float time_interval = bounce.valStar / 10;
        for (int j = 0; j < 10; j++) {
            trajectory.push_back(ballistic2.getPosition(time_interval));
        }

        // Write the trajectory to a file
        for (int j = 0; j < 10; j++) {
            *easy_bounces[i] << trajectory[j][0] << " " << trajectory[j][1] << endl;
        }
        cout << "Trajectory number " << i + 1 << " created and added to file" << endl;

        // Use the bounce information to define a new ballistic function
        // where the projectile is launched from the bounce location with
        // new position and velocity info
        vector<float> in_info = ballistic2.getPositionAndVelocity(bounce.valStar);
        vector<float> out_info = easy_elastic_surface.getOutgoingVelocity(in_info[0], in_info[2], in_info[3]);

        // Set the new ballistic function
        ballistic2 = BallisticFunction(out_info[0], out_info[1], out_info[2], out_info[3]);
        // cout << "Ballistic function updated" << endl;
    }
    

    // Complex surfaces with different elasticity values
    // Defined as 4sin(x) + 5cos(x/2) + (x^3)/10000
    HardSurface hard_elastic_surface(1);
    HardSurface hard_absorbant_surface(0.5);
    */
    return 0;
}