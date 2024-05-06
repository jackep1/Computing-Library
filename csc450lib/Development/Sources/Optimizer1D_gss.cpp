#include "Optimizer1D_gss.h"

OptimizerRecord1D Optimizer1D_gss::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {
    // Initialize the record
    OptimizerRecord1D record;
    record.xMin = xMin;
    record.xMax = xMax;
    record.tol = tol;
    record.maxNumIters = maxNumIters;
    record.numIters = 0;
    record.x = startX;
    record.fx = f->func({startX});

    // Initialize the golden ratio
    float phi = (1.0f + std::sqrt(5.0f)) / 2.0f;
    float resphi = 2.0f - phi;

    // Initialize the golden section search
    float x1 = xMin + resphi * (xMax - xMin);
    float x2 = xMin + phi * (xMax - xMin);
    float f1 = f->func({x1});
    float f2 = f->func({x2});

    // Loop until the tolerance is met or the maximum number of iterations is reached
    while (std::abs(xMax - xMin) > tol && record.numIters < maxNumIters) {
        // Update the record
        record.numIters++;
        if (f1 < f2) {
            xMax = x2;
            x2 = x1;
            f2 = f1;
            x1 = xMin + resphi * (xMax - xMin);
            f1 = f->func({x1});
        } else {
            xMin = x1;
            x1 = x2;
            f1 = f2;
            x2 = xMin + phi * (xMax - xMin);
            f2 = f->func({x2});
        }
    }

    // Update the record
    record.x = (xMin + xMax) / 2.0f;
    record.fx = f->func({record.x});

    return record;
}