#ifndef HARDSURFACE_H
#define HARDSURFACE_H

#include <Surface.h>

/**
 * The HardSurface class represents a surface defined
 * by the function f(x) = 4sin(x) + 5cos(x/2) + (x^3)/10000.
*/
class HardSurface : public Surface {
    public:
        HardSurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // HARDSURFACE_H