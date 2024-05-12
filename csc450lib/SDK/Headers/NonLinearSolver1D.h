#include <NonLinearSolverRecord1D.h>
#include <Function1D.h>

#ifndef NONLINEARSOLVER1D_H
#define NONLINEARSOLVER1D_H

namespace csc450lib_calc {

    class NonLinearSolver1D {

        public:
            // Copy and move constructors not needed
            virtual ~NonLinearSolver1D() = default;
            NonLinearSolver1D(const NonLinearSolver1D& obj) = delete;
            NonLinearSolver1D(NonLinearSolver1D&& obj) = delete;
            NonLinearSolver1D& operator =(const NonLinearSolver1D& obj) = delete;
            NonLinearSolver1D& operator =(NonLinearSolver1D&& obj) = delete;

            // Public methods
            NonLinearSolver1D() = default;
            virtual NonLinearSolverRecord1D solve(std::shared_ptr<Function1D> f, float a, float b, int n, float tol) const = 0;
    };
}

#endif // NONLINEARSOLVER1D_H



#ifndef NONLINEARSOLVER1D_BISECTION_H
#define NONLINEARSOLVER1D_BISECTION_H

class NonLinearSolver1D_bisection : public csc450lib_calc::NonLinearSolver1D {

    public:
        csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol) const;
};

#endif // NONLINEARSOLVER1D_BISECTION_H



#ifndef NONLINEARSOLVER1D_NEWTONRAPHSON_H
#define NONLINEARSOLVER1D_NEWTONRAPHSON_H

class NonLinearSolver1D_NewtonRaphson : public csc450lib_calc::NonLinearSolver1D {
    public:
        csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol);
};

#endif // NONLINEARSOLVER1D_NEWTONRAPHSON_H



#ifndef NONLINEARSOLVER1D_SECANT_H
#define NONLINEARSOLVER1D_SECANT_H

class NonLinearSolver1D_secant : public csc450lib_calc::NonLinearSolver1D {
    public:
        csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol);
};

#endif // NONLINEARSOLVER1D_SECANT_H