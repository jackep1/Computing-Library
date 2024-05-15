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

    cout << "\nFlat surface data: " << endl;

    // Flat surface
    FlatSurface2D surface(1);
    
    // Mortar launched at 45 degrees with initial velocity of 10 units
    MortarFunc1D mortar(1, 1, 0, 0, 10, 10);

    // Open file for writing impact data
    ofstream flat_impact_file("../../../../MMA Files/impact_data.txt");

    // Vector for points along trajectory
    vector<vector<float>> trajectory;
    
    // Define the collision problem
    shared_ptr<CollisionProblem2D> flight = make_shared<CollisionProblem2D>(&mortar, &surface);

    // Determine the search bracket for the time of impact
    vector<float> bracket = find_search_bracket(0.001, mortar, flight);
    cout << "Bracket: " << bracket[0] << " " << bracket[1] << endl;

    // Find the time of impact
    NonLinearSolverRecord1D impact_data = solver.solve(static_pointer_cast<csc450lib_calc::Function1D>(flight), bracket[0], bracket[1], 100, 0.01);

    // Write the trajectory to file
    float time_interval = impact_data.getValStar() / 10;
    for (int j = 0; j < 10; j++) {
        trajectory.push_back(mortar.getCoordinates(time_interval * j));
    }

    float x_impact = mortar.getCoordinates(impact_data.getValStar())[0];
    float y_impact = mortar.getCoordinates(impact_data.getValStar())[1];
    cout << "Impact at {" << x_impact << ", " << y_impact << "}" << endl;
    cout << "Point of impact at height " << surface.func({x_impact, y_impact}) << " at time " << impact_data.getValStar() << endl;

    cout << "\nEasy surface data: " << endl;

    // Easy surface
    EasySurface2D surface2(1);

    // Mortar launched at 45 degrees with initial velocity of 10 units
    MortarFunc1D mortar2(1, 1, 0, 0, 10, 10);

    // Open file for writing impact data
    ofstream easy_impact_file("../../../../MMA Files/impact_data_easy.txt");

    // Vector for points along trajectory
    vector<vector<float>> trajectory2;

    // Define the collision problem
    shared_ptr<CollisionProblem2D> flight2 = make_shared<CollisionProblem2D>(&mortar2, &surface2);

    // Determine the search bracket for the time of impact
    vector<float> bracket2 = find_search_bracket(0.001, mortar2, flight2);
    cout << "Bracket: " << bracket2[0] << " " << bracket2[1] << endl;

    // Find the time of impact
    NonLinearSolverRecord1D impact_data2 = solver.solve(static_pointer_cast<csc450lib_calc::Function1D>(flight2), bracket2[0], bracket2[1], 100, 0.01);

    // Write the trajectory to file
    float time_interval2 = impact_data2.getValStar() / 10;
    for (int j = 0; j < 10; j++) {
        trajectory2.push_back(mortar2.getCoordinates(time_interval2 * j));
    }

    float x_impact2 = mortar2.getCoordinates(impact_data2.getValStar())[0];
    float y_impact2 = mortar2.getCoordinates(impact_data2.getValStar())[1];
    cout << "Impact at {" << x_impact2 << ", " << y_impact2 << "}" << endl;
    cout << "Point of impact at height " << surface2.func({x_impact2, y_impact2}) << " at time " << impact_data2.getValStar() << endl;

    cout << endl;
    return 0;
}