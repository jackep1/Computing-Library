#include <VectorFunction1D.h>
#include <DomainOfDefinition.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;

/**
 * The default constructor for the class, sets the domain to be all real numbers.
*/
VectorFunction1D::VectorFunction1D()
: domain({subDomain(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), false, false)}) {}

/**
 * The constructor that sets the lower and upper bounds of the function.
 * 
 * @param xmin The lower bound of the function.
 * @param xmax The upper bound of the function.
*/
VectorFunction1D::VectorFunction1D(float xmin, float xmax)
: domain({subDomain(xmin, xmax, false, false)}) {}

/**
 * The constructor that sets a unique domain of definition.
*/
VectorFunction1D::VectorFunction1D(DomainOfDefinition d)
: domain(d) {}

/**
 * Checks if the function is defined at a given x value.
 * 
 * @param x The x value to check.
 * @return true if the function is defined at x, false otherwise.
*/
bool VectorFunction1D::isDefinedAt(float x) const
{
    if (domain.contains_point(x)) {
        return true;
    }
    return false;
}

/**
 * Gets the lower bound of the function.
 * 
 * @return The lower bound of the function.
*/
float VectorFunction1D::getLowerBound(void) const
{
    return domain.get_domain()[0].xMin;
}

/**
 * Gets the upper bound of the function.
 * 
 * @return The upper bound of the function.
*/
float VectorFunction1D::getUpperBound(void) const
{
    return domain.get_domain()[domain.get_domain().size() - 1].xMax;
}

/**
 * Sets the domain of the function.
 * 
 * @param d the new domain of definition
*/
void VectorFunction1D::setDomain(DomainOfDefinition d)
{
    domain = d;
}

/**
 * Returns the derivative of the function at x using an approximation.
 * 
 * @param x The x value to evaluate the derivative at.
 * 
 * @return The derivative of the function at x.
*/
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

/**
 * Returns the second derivative of the function at x using an approximation.
 * 
 * @param x The x value to evaluate the second derivative at.
 * 
 * @return The second derivative of the function at x.
*/
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