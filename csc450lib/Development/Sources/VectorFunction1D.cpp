#include <VectorFunction1D.h>
#include <DomainOfDefinition.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;


VectorFunction1D::VectorFunction1D(float xmin, float xmax)
: domain({subDomain(xmin, xmax, false, false)}) {}

VectorFunction1D::VectorFunction1D(DomainOfDefinition d)
: domain(d) {}

bool VectorFunction1D::isDefinedAt(float x) const
{
    if (domain.contains_point(x)) {
        return true;
    }
    return false;
}

float VectorFunction1D::getLowerBound(void) const
{
    return domain.get_domain()[0].xMin;
}

float VectorFunction1D::getUpperBound(void) const
{
    return domain.get_domain()[domain.get_domain().size() - 1].xMax;
}

void VectorFunction1D::setDomain(DomainOfDefinition d)
{
    domain = d;
}

float VectorFunction1D::dfunc(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "The function is not defined at the given x value.");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    return (this->func(x + h) - this->func(x - h)) / (2 * h);
}

float VectorFunction1D::d2func(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "The function is not defined at the given x value.");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    return (this->func(x + h) - 2 * this->func(x) + this->func(x - h)) / (h * h);
}