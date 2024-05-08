#include <MortarFunc.h>
#include <vector>

float MortarFunc::func(const std::vector<float>& x) {
    std::vector<float> m_pos;
    std::vector<float> component1 = {0.0, 0.0, 0.0};
    component1.map([](float x) { return 0.5 * x; });
}