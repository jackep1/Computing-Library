#include <Optimizer1D.h>
#include <stdlib.h>
#include <cmath>

using namespace csc450lib_calc;


/** Base optimizer methods */

Optimizer1D::Optimizer1D(std::shared_ptr<Function1D> f): f(f) {}

void Optimizer1D::setFunction(std::shared_ptr<Function1D> f) {
    this->f = f;
}

std::shared_ptr<const Function1D> Optimizer1D::getFunction() const {
    return f;
}



/** Steepest descent optimizer methods */

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



/** Parabolic optimizer methods */

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



/** Golden section search optimizer methods */

OptimizerRecord1D Optimizer1D_gss::minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const {

    // Initialize starting record values
    float optX = xMin;
    float optVal = xMax;
    int numIters = 0;
    bool isSuccess = false;

    // Initialize the golden ratio
    float phi = (1.0f + std::sqrt(5.0f)) / 2.0f;
    float resphi = 2.0f - phi;

    // Initialize the golden section search
    float x1 = xMin + resphi * (xMax - xMin);
    float x2 = xMin + phi * (xMax - xMin);
    float f1 = this->f->func({x1});
    float f2 = this->f->func({x2});

    // Loop until the tolerance is met or the maximum number of iterations is reached
    while (std::abs(xMax - xMin) > tol && numIters < maxNumIters) {
        // Update the record
        numIters++;
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
    if (numIters < maxNumIters) {
        isSuccess = true;
    }

    // Update the record
    optX = (xMin + xMax) / 2.0f;
    optVal = f->func({optX});

    return OptimizerRecord1D(optX, optVal, numIters, isSuccess);
}