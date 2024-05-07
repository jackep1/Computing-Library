#include <iostream>
#include <fstream>
#include <chrono>

#include <CSC450Lib.h>
#include <CSC450Exception.h>

#include <Function1D.h>
#include <CosFunc.h>
#include <CosFuncNoDerivative.h>
#include <SinFunc.h>
#include <PolynomialFunction1D.h>

#include <FlatSurface.h>
#include <EasySurface.h>
#include <HardSurface.h>
#include <BallisticFunction.h>
#include <CollisionProblem.h>

#include <NonLinearSolver1D.h>
#include <NonLinearSolver1D_bisection.h>
#include <NonLinearSolver1D_NewtonRaphson.h>
#include <NonLinearSolver1D_secant.h>

using namespace std;
using namespace csc450lib;
using namespace csc450lib_calc;

/**
 * Find the search bracket for the location of the collision. Left bracket is
 * set to the tolerance and the right bracket is set to the point where the
 * height is negative. If the right bracket is positive, the right bracket is
 * increased by 10% until a negative value is found. If the right bracket is
 * negative, the right bracket is decreased by 10% until a positive value is
 * found. The left bracket is set to the largest positive value found.
 * 
 * @param TOL The tolerance for the search bracket
 * @param ballistic The ballistic function
 * @param flight The collision problem
 * @return A vector containing the left and right ends of the search bracket
*/
vector<float> find_search_bracket(float TOL, BallisticFunction& ballistic, shared_ptr<CollisionProblem> flight) {

    // Start left end of bracket at tolerance
    float a = TOL;
    float peak_time;
    // Get time of peak height
    if (ballistic.getPositionAndVelocity(0)[3] <= 0) {
        // If not moving up, set peak time to 0.01
        peak_time = 0.01;
    } else {
        // If moving up, set peak time with Vy0 / g
        peak_time = ballistic.getPositionAndVelocity(0)[3] / 9.8;
        cout << "Peak time: " << peak_time << endl;
    }
    // cout << "Time of peak found" << endl;

    // Right end of bracket is at point symmetric to start
    float b = peak_time * 2;
    cout << b << " " << flight->func(b) << endl;

    // Determine sign of right bracket, if negative, find last positive value
    float right_height = flight->func(b);
    // int count = 0; int max = 100;

    if (right_height < 0 /*&& count < max*/) {
        // Store last positive value
        float last_right = b;
        cout << "Search for right bracket started from negative value" << right_height << endl;
        // Reduce b by 10% until positive value is found
        while (right_height < 0) {
            last_right = b;
            b *= 0.9;
            right_height = flight->func(b);
            cout << b << endl;
        }

        // Set b to last positive value
        b = last_right;
        cout << "Right bracket found from intially negative value" << endl;
        return vector<float>{a, b};
    }
    

    // if (count >= max) {
    //     cout << "Failed to find right bracket" << endl;
    //     exit(1);
    // }
    // count = 0;
    // cout << "Search for right bracket started from positive value" << endl;
    // If right bracket is positive, increase b by 10% until negative value is found
    while (right_height > 0 /*&& count < max*/) {
        if (a < b) {
            a = b;
        }
        //cout << "Possible endpoint " << count << ": " << b << endl;
        b *= 1.1;
        right_height = flight->func(b);
        //count++;
    }
    // if (count >= max) {
    //     cout << "Failed to find right bracket" << endl;
    //     exit(1);
    // }
    // cout << "Right bracket found from initially positive value" << endl;

    return vector<float>{a, b};
}

int main(int argc, const char* argv[])
{
    float inf = INFINITY;
    float ninf = -INFINITY;

    ofstream cosExactFile("../../../../MMA Files/cosd.txt");
    ofstream cosApproxFile("../../../../MMA Files/cosad.txt");
    ofstream pdFile("../../../../MMA Files/pd.txt");


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
    NonLinearSolver1D_bisection bisection_solver;;

    // Flat surfaces with different elasticity values
    FlatSurface flat_elastic_surface(1);
    FlatSurface flat_absorbant_surface(0.5);

    // Define an initial ballistic function where
    // projectile is launched directly sideways at
    // a height of 10 units and a velocity of 10 units
    BallisticFunction ballistic1(0, 10, 10, 0);

    // Open files for writing bounce data
    ofstream flat_bounce1_File("../../../../MMA Files/flat_bounce1.txt");
    ofstream flat_bounce2_File("../../../../MMA Files/flat_bounce2.txt");
    ofstream flat_bounce3_File("../../../../MMA Files/flat_bounce3.txt");
    ofstream flat_bounce4_File("../../../../MMA Files/flat_bounce4.txt");
    ofstream flat_bounce5_File("../../../../MMA Files/flat_bounce5.txt");
    vector<ofstream*> flat_bounces = {&flat_bounce1_File, &flat_bounce2_File, &flat_bounce3_File, &flat_bounce4_File, &flat_bounce5_File};
    vector<vector<float>> trajectory;

    for (int i = 0; i < 5; i++) {

        // Define a collision problem with the perfectly elastic
        // simple surface and the ballistic function
        shared_ptr<CollisionProblem> flight = make_shared<CollisionProblem>(&ballistic1, &flat_elastic_surface);
        // cout << "Flight created" << endl;

        // Determine a search bracket for the location of the collision
        vector<float> search_bracket = find_search_bracket(0.01, ballistic1, flight);
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
            trajectory.push_back(ballistic1.getPosition(time_interval));
        }

        // Write the trajectory to a file
        for (int j = 0; j < 10; j++) {
            *flat_bounces[i] << trajectory[j][0] << " " << trajectory[j][1] << endl;
        }
        cout << "Trajectory number " << i + 1 << " created and added to file" << endl;

        // Use the bounce information to define a new ballistic function
        // where the projectile is launched from the bounce location with
        // new position and velocity info
        vector<float> in_info = ballistic1.getPositionAndVelocity(bounce.valStar);
        vector<float> out_info = flat_elastic_surface.getOutgoingVelocity(in_info[0], in_info[2], in_info[3]);

        // Set the new ballistic function
        ballistic1 = BallisticFunction(out_info[0], out_info[1], out_info[2], out_info[3]);
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