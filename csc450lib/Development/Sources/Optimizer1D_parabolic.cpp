#include "Optimizer1D_parabolic.h"

OptimizerRecord1D Optimizer1D_parabolic::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {
    // Initialize the record
    OptimizerRecord1D record;
    record.xMin = xMin;
    record.xMax = xMax;
    record.tol = tol;
    record.maxNumIters = maxNumIters;
    record.numIters = 0;
    record.x = startX;
    record.fx = f->func({startX});

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
    while (std::abs(xMinParabolic - x2) > tol && record.numIters < maxNumIters) {
        // Update the record
        record.numIters++;
        record.x = xMinParabolic;
        record.fx = fMinParabolic;

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
}
