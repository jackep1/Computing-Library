#include <BallisticFunction.h>
#include <Surface.h>

namespace csc450lib_calc {

    #ifndef COLLISIONPROBLEM_H
    #define COLLISIONPROBLEM_H

    class CollisionProblem : public Function1D {
        public:
            // Public methods for the interface
            CollisionProblem(BallisticFunction* ballistic, Surface* surface);
            float func(float t) const;

            // Some methods that are useless but must be defined
            bool derivativeIsExact() const { return false; }
            bool secondDerivativeIsExact() const { return false; }
            std::shared_ptr<std::string> getExpressionMMA() const { return nullptr; }

        protected:
            BallisticFunction* ballistic;
            Surface* surface;
    };

    #endif // COLLISIONPROBLEM_H
}