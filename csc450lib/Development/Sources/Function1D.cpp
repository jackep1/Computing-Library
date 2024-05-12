#include <Function1D.h>
#include <DomainOfDefinition.h>
#include <CSC450Exception.h>

using namespace csc450lib;
using namespace csc450lib_calc;

/**
 * The default constructor for the Function1D class that sets the domain of definition to be all real numbers.
*/
Function1D::Function1D()
: domain({subDomain(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), false, false)}){}

/**
 * The constructor for the Function1D class that sets the lower and upper bounds of the function.
 * 
 * @param xmin the lower bound of the function
 * @param xmax the upper bound of the function
*/
Function1D::Function1D(float xmin, float xmax)
: domain({subDomain(xmin, xmax, false, false)}) {}

/**
 * The constructor for the Function1D class that sets a unique domain of definition.
 * 
 * @param d the domain of definition
*/
Function1D::Function1D(DomainOfDefinition d)
: domain(d) {}

/**
 * Determines if the function is defined at the given x value.
 * Checks by looking to see if the x value is within the bounds of the function.
 * 
 * @param x the x value to check
 * @return true if the function is defined at x, false otherwise
*/
bool Function1D::isDefinedAt(float x) const
{
    if (domain.contains_point(x)) {
        return true;
    }
    return false;
}

/**
 * Returns the lower bound of the function.
 * 
 * @return the lower bound of the function
*/
float Function1D::getLowerBound(void) const
{
    return domain.get_domain()[0].xMin;
}

/**
 * Returns the upper bound of the function.
 * 
 * @return the upper bound of the function
*/
float Function1D::getUpperBound(void) const
{
    return domain.get_domain()[domain.get_domain().size() - 1].xMax;
}

/**
 * Sets the domain of definition of the function.
 * 
 * @param d the new domain of definition
*/
void Function1D::setDomain(DomainOfDefinition d)
{
    domain = d;
}

/**
 * Returns the deriviative of the function at the given point x using 'step' h
 * 
 * @param x the point at which to evaluate the derivative
 * @param h the size of the small step 'h' used to calculate derivative
 * 
 * @return the derivative at x
*/
float Function1D::dfunc(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    float fxph = func(x + h);
    float fxmh = func(x - h);
    float solution = ((fxph - fxmh) / (2 * h));
    return solution;
}

/**
 * Returns the second derivative of the function at the given point x
 * 
 * @param x the point at which to evaluate the second derivative
 * 
 * @return the second derivative at x
*/
float Function1D::d2func(float x) const
{
    if (!this->isDefinedAt(x)) {
        throw CSC450Exception(ErrorCode::FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT, "x not in domain");
    }
    float h = x * 0.001;
    if (x == 0) {
        h = 0.001;
    }
    float fxph = func(x + h);
    float fxmh = this->func(x - h);
    float fx2 = 2 * func(x);
    float solution = ((fxph - fx2 + fxmh) / (h * h));
    return solution;
}