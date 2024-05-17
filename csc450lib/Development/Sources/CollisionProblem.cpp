#include <CollisionProblem1D.h>
#include <memory>
#include <string>

using namespace csc450lib_calc;


/** Ballistic Function methods */

BallisticFunction::BallisticFunction(float x0, float y0, float Vx0, float Vy0)
: x0(x0), y0(y0), Vx0(Vx0), Vy0(Vy0) {}

std::vector<float> BallisticFunction::getPosition(float t) const {
    float x = this->x0 + this->Vx0 * t;
    float y = this->y0 + (this->Vy0 * t) - (0.5 * 9.8 * t * t);
    return std::vector<float>{x, y};
}

std::vector<float> BallisticFunction::getPositionAndVelocity(float t) const {
    float x = this->x0 + this->Vx0 * t;
    float y = this->y0 + (this->Vy0 * t) - (0.5 * 9.8 * t * t);
    float Vx = this->Vx0;
    float Vy = this->Vy0 - (9.8 * t);
    return std::vector<float>{x, y, Vx, Vy};
}



/** Base surface methods */

Surface1D::Surface1D(float alpha) : a(alpha) {}

std::vector<float> Surface1D::getOutgoingVelocity(float x, float Vinx, float Viny) const {
    // float n1 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * this->dfunc(x);
    // float n2 = (1 / sqrt(1 + this->dfunc(x) * this->dfunc(x))) * 1;
    // std::vector<float> normal_force = std::vector<float>{n1, n2};
    // std::vector<float> aN = std::vector<float>{a * normal_force[0], a * normal_force[1]};
    // std::vector<float> Vout = std::vector<float>{Vinx + aN[0], Viny + aN[1]};

    float dx = this->dfunc(x);

    float numX = (Vinx * dx * dx) - (Viny * dx);
    float denomX = (dx * dx) + 1;
    float Voutx = Vinx + (2 * a * numX / denomX);

    float numY = Viny - (Vinx * dx);
    float denomY = (dx * dx) + 1;
    float Vouty = Viny - (2 * a * numY / denomY);

    return std::vector<float>{x, Voutx, Vouty};
}

void Surface1D::setAlpha(float alpha) {
    this->a = alpha;
}



/** Collision Problem methods */

CollisionProblem1D::CollisionProblem1D(std::shared_ptr<BallisticFunction> ballistic, std::shared_ptr<Surface1D> surface)
: ballistic(ballistic), surface(surface) {}

float CollisionProblem1D::func(float t) const {
    std::vector<float> position = this->ballistic->getPosition(t);
    float surface_height = this->surface->func(position[0]);
    return position[1] - surface_height;
}



/** FlatSurface1D methods */

FlatSurface1D::FlatSurface1D(float alpha) : Surface1D(alpha) {}

float FlatSurface1D::func(float x) const {
    return 1;
}

float FlatSurface1D::dfunc(float x) const {
    return 0;
}

bool FlatSurface1D::derivativeIsExact() const {
    return false;
}

bool FlatSurface1D::secondDerivativeIsExact() const {
    return false;
}

std::shared_ptr<std::string> FlatSurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("1"));
    return expression;
}



/** EasySurface1D methods */

EasySurface1D::EasySurface1D(float alpha) : Surface1D(alpha) {}

float EasySurface1D::func(float x) const {
    return (cosf(x) / 5) + 1;
}

bool EasySurface1D::derivativeIsExact() const {
    return false;
}

bool EasySurface1D::secondDerivativeIsExact() const {
    return false;
}

std::shared_ptr<std::string> EasySurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("Cos[x]/5 + 1"));
    return expression;
}



/** HardSurface1D methods */

HardSurface1D::HardSurface1D(float alpha) : Surface1D(alpha) {}

float HardSurface1D::func(float x) const {
    float t1 = 4 * sinf(x);
    float t2 = 5 * cosf(x/2);
    float t3 = x * x * x / 10000;
    return t1 + t2 + t3;
}

bool HardSurface1D::derivativeIsExact() const {
    return false;
}

bool HardSurface1D::secondDerivativeIsExact() const {
    return false;
}

std::shared_ptr<std::string> HardSurface1D::getExpressionMMA() const {
    std::shared_ptr<std::string> expression(new std::string("4 Sin[x] + 5 Cos[x/2] + (x^3)/10000"));
    return expression;
}