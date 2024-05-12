#include <VectorFunction1D.h>

using namespace csc450lib_calc;

VectorFunction1D::VectorFunction1D(float xmin, float xmax) {
    this->lowerBound = xmin;
    this->upperBound = xmax;
}

VectorFunction1D::VectorFunction1D(std::shared_ptr<DomainOfDefinition> d) {
    this->domain = d;
}