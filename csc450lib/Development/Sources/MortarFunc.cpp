#include <MortarFunc.h>
#include <vector>

float h(float x, float y) {

}

float MortarFunc::func(const std::vector<float>& x) {
    int t;
    std::vector<float> m_pos;
    std::vector<float> component1 = {0.0, 0.0, -9.8};
    std::vector<float> component2 = {this->Vx0, this->Vy0, this->Vz0};
    std::vector<float> component3 = {this->x0, this->y0, this->h(this->x0, this->y0)};
    for (int i = 0; i < 3; i++) {
        component1[i] = component1[i] * 0.5 * t * t;
    }
}