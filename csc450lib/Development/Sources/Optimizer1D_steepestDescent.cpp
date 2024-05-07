#include "Optimizer1D_steepestDescent.h"
#include <stdlib.h>

OptimizerRecord1D Optimizer1D_steepestDescent::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {

    // Initialize the record
    float optX, optVal;
    int numIters = 0;
    bool isSuccess = false;

    // Loop until the tolerance is met or the maximum number of iterations is reached
    while (std::abs(f->func(startX)) > tol && numIters < maxNumIters) {
        // Update the record
        numIters++;
        optX = optX - f->dfunc({optX});

        // Update the function value
        optVal = f->func({optX});
    }
    if (numIters < maxNumIters) {
        isSuccess = true;
    }

    return OptimizerRecord1D(optX, optVal, numIters, isSuccess);
}