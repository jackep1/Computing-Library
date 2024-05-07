#ifndef EASYSURFACE_H
#define EASYSURFACE_H

#include <Surface.h>

/**
 * The EasySurface class represents a surface defined
 * by the function f(x) = cos(x)/5 + 1.
*/
class EasySurface : public Surface {
    public:
        EasySurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif // EASYSURFACE_H