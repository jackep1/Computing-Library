#ifndef MORTARFUNC_H
#define MORTARFUNC_H

#include <FunctionND.h>

class MortarFunc : public csc450lib_calc::FunctionND {
    public:
        float func(const std::vector<float>& x);
};

#endif /// MORTARFUNC_H