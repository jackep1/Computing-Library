#ifndef FLATSURFACE_H
#define FLATSURFACE_H

#include <Surface.h>

/**
 * The FlatSurface class represents a flat surface.
*/
class FlatSurface : public Surface {
    public:
        FlatSurface(float alpha);
        float func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
    protected:
        float a;
};

#endif // FLATSURFACE_H