#include "Optimizer1D.h"

Optimizer1D::Optimizer1D(std::shared_ptr<Function1D> f) {
    this->f = f;
}

void Optimizer1D::setFunction(std::shared_ptr<Function1D> f) {
    this->f = f;
}

std::shared_ptr<const Function1D> Optimizer1D::getFunction() const {
    return f;
}