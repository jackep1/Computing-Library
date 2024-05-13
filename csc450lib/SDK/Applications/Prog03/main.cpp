#include <iostream>
#include <fstream>

#include <CSC450Lib.h>
#include <CSC450Exception.h>

#include <Function1D.h>
#include <CollisionProblem2D.h>

#include <NonLinearSolver1D.h>
// #include <FunctionND.h>
// #include <Function1DfromND.h>

using namespace std;
using namespace csc450lib;
using namespace csc450lib_calc;

vector<float> find_search_bracket(float TOL, MortarFunc1D& mortar, shared_ptr<CollisionProblem2D> flight)
{
    // Start left end of bracket at tolerance
    float a = TOL;
    float peak_time = mortar.getPositionAndVelocity(0)[3] / 9.8;
    if (peak_time <= 0) {
        peak_time = 0.01;
    }

    // Right end of bracket at point symmetric to start
    float b = (peak_time * 2) - a;

    // Determine sign of right bracket, if negative, find last positive value
    float right_height = flight->func(b);

    // If right bracket is positive, increase b by 10% until negative value is found
    while (right_height > 0) {
        b *= 1.1;
        right_height = flight->func(b);
    }

    // Return bracket
    return {a, b};
}

int main(int argc, const char* argv[])
{
    // Non-linear solver for finding the time of impact
    NonLinearSolver1D_bisection solver;

    // Flat surface
    FlatSurface2D surface(1);
    
    // Mortar launched at 45 degrees with initial velocity of 10 units
    MortarFunc1D mortar(1, 1, 0, 0, 10, 10);

    // Open files for writing impact data
    ofstream impact_file("../../../../MMA Files/impact_data.txt");

    // Vector for points along trajectory
    vector<float> trajectory;
    
    // Define the collision problem
    shared_ptr<CollisionProblem2D> flight = make_shared<CollisionProblem2D>(&mortar, &surface);

    // Determine the search bracket for the time of impact
    vector<float> bracket = find_search_bracket(0.001, mortar, flight);

    // Find the time of impact
    NonLinearSolverRecord1D impact_data = solver.solve(static_pointer_cast<csc450lib_calc::Function1D>(flight), bracket[0], bracket[1], 100, 0.01);

    // Write the trajectory to file
    float time_interval = impact_data.getValStar() / 10;
    for (int j = 0; j < 10; j++) {
        trajectory.push_back(mortar.getPosition(time_interval * j)[1]);
    }

    float x_impact = mortar.getCoordinates(impact_data.getValStar())[0];
    float y_impact = mortar.getCoordinates(impact_data.getValStar())[1];
    cout << "Point of impact at " << surface.func({x_impact, y_impact}) << " at time " << impact_data.getValStar() << endl;

    return 0;
}