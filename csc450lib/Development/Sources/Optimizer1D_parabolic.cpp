#include "Optimizer1D_parabolic.h"
#include <cmath>

OptimizerRecord1D Optimizer1D_parabolic::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {
    
    // Initialize starting record values
    float optX = xMin;
    float optVal = xMax;
    int numIters = 0;
    bool isSuccess = false;

    // Initialize the parabolic minimum
    float x1 = xMin;
    float x2 = startX;
    float x3 = xMax;
    float f1 = f->func({x1});
    float f2 = f->func({x2});
    float f3 = f->func({x3});
    float xMinParabolic = x2 - 0.5f * ((x2 - x1) * (x2 - x1) * (f2 - f3) - (x2 - x3) * (x2 - x3) * (f2 - f1)) /
        ((x2 - x1) * (f2 - f3) - (x2 - x3) * (f2 - f1));
    float fMinParabolic = f->func({xMinParabolic});

    // Loop until the tolerance is met or the maximum number of iterations is reached
    while (std::abs(xMinParabolic - x2) > tol && numIters < maxNumIters) {
        // Update the record
        numIters++;
        optX = xMinParabolic;
        optVal = fMinParabolic;

        // Update the parabolic minimum
        if (xMinParabolic < x2) {
            if (fMinParabolic < f2) {
                x3 = x2;
                f3 = f2;
                x2 = xMinParabolic;
                f2 = fMinParabolic;
            } else {
                x1 = xMinParabolic;
                f1 = fMinParabolic;
            }
        } else {
            if (fMinParabolic < f2) {
                x1 = x2;
                f1 = f2;
                x2 = xMinParabolic;
                f2 = fMinParabolic;
            } else {
                x3 = xMinParabolic;
                f3 = fMinParabolic;
            }
        }
    }
    if (numIters < maxNumIters) {
        isSuccess = true;
    }
    return OptimizerRecord1D(optX, optVal, numIters, isSuccess);
}
