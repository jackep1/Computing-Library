#include <MortarFunc.h>
#include <vector>

float h(float x, float y) {

}

float MortarFuncV2::func(float t) {
    std::vector<float> m_pos;
    std::vector<float> component1 = {0.0, 0.0, -9.8};
    std::vector<float> component2 = {this->Vx0, this->Vy0, this->Vz0};
    std::vector<float> component3 = {this->x0, this->y0, this->h(this->x0, this->y0)};
    for (int i = 0; i < 3; i++) {
        component1[i] = component1[i] * 0.5 * t * t;
    }
}

// MortarFunc has been initialized with initial z0 (implociot;ly u0=0) vu, vz

// Displacement is in the plane u-z
std::vector<float> MortarFuncV1::func(float t) {
    std::vector<float> m_pos(2);
    // u coordinate
    m_pos[0] = 0 + vu*t;
    // z coordiomate
    m_pos[1] = z0 + vz*t - 0.5*g*t*t;

    std::vector<float> component1 = {0.0, 0.0, -9.8};
    std::vector<float> component2 = {this->Vx0, this->Vy0, this->Vz0};
    std::vector<float> component3 = {this->x0, this->y0, this->h(this->x0, this->y0)};
    for (int i = 0; i < 3; i++) {
        component1[i] = component1[i] * 0.5 * t * t;
    }
}



// class VectorFunctionND {

//     std::vector<float> func(float t) const  = 0;
//     virtual std::vector<float> func(float t) const;
// }

// class MortarFunc : public VectorFunctionND {


// }

class IntersectionFunc : public Function1D {

    public:

        IntersectionFunc(shared_ptr<MortarFunc> mortar, shared_ptr<Function1DFromND> surfaceSection)

        float func(float t) {
                //get um, zm from mortar

                return zm - surfaceSection.func(um);

        }

}