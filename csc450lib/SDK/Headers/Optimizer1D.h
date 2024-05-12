#include <OptimizerRecord1D.h>
#include <Function1D.h>

#ifndef OPTIMIZER1D_H
#define OPTIMIZER1D_H

namespace csc450lib_calc {

    class Optimizer1D {

        public:
            // Copy and move constructors not needed
            virtual ~Optimizer1D() = default;
            Optimizer1D(const Optimizer1D& obj) = delete;
            Optimizer1D(Optimizer1D&& obj) = delete;
            Optimizer1D& operator =(const Optimizer1D& obj) = delete;
            Optimizer1D& operator =(Optimizer1D&& obj) = delete;

            // Public methods
            Optimizer1D(std::shared_ptr<Function1D> f);
            void setFunction(std::shared_ptr<Function1D> f);
            std::shared_ptr<const Function1D> getFunction() const;
            virtual OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const = 0;

            std::shared_ptr<Function1D> f;
    };
}

#endif // OPTIMIZER1D_H



#ifndef OPTIMIZER1D_STEEPESTDESCENT_H
#define OPTIMIZER1D_STEEPESTDESCENT_H

class Optimizer1D_steepestDescent : public csc450lib_calc::Optimizer1D {
    
    public:
        Optimizer1D_steepestDescent(std::shared_ptr<csc450lib_calc::Function1D> f) : Optimizer1D(f) {};
        csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_STEEPESTDESCENT_H



#ifndef OPTIMIZER1D_PARABOLIC_H
#define OPTIMIZER1D_PARABOLIC_H

class Optimizer1D_parabolic : public csc450lib_calc::Optimizer1D {
    
    public:
        Optimizer1D_parabolic(std::shared_ptr<csc450lib_calc::Function1D> f) : Optimizer1D(f) {};
        csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_PARABOLIC_H



#ifndef OPTIMIZER1D_GSS_H
#define OPTIMIZER1D_GSS_H

class Optimizer1D_gss : public csc450lib_calc::Optimizer1D {
    
    public:
        Optimizer1D_gss(std::shared_ptr<csc450lib_calc::Function1D> f) : Optimizer1D(f) {};
        csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
};

#endif // OPTIMIZER1D_GSS_H