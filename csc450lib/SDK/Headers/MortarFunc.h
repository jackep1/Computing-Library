#ifndef MORTARFUNC_H
#define MORTARFUNC_H

#include <FunctionND.h>

class MortarFunc : public csc450lib_calc::FunctionND {
    public:
        float func(const std::vector<float>& x);
    private:
        float x0;
        float y0;
        float Vx0;
        float Vy0;
        float Vz0;
        float h(float x, float y);
};

#endif /// MORTARFUNC_H