#include "Optimizer1D_steepestDescent.h"
#include <stdlib.h>

OptimizerRecord1D Optimizer1D_steepestDescent::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {
    // Initialize the record
    float optX, optVal;
    int numIters = 0;
    bool isSuccess;
    std::shared_ptr<const Function1D> f = this->getFunction();

    // Loop until the tolerance is met or the maximum number of iterations is reached
    while (std::abs(f->func(startX)) > tol && numIters < maxNumIters) {
        // Update the record
        numIters++;
        record.x = record.x - f->derivative({record.x});

        // Update the function value
        record.fx = f->func({record.x});
    }

    return OptimizerRecord1D(xMin, xMax, numIters, isSuccess);
}