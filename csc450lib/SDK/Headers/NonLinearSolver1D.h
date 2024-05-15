#include <Function1D.h>

namespace csc450lib_calc {
    
    #ifndef NONLINEARSOLVERRECORD1D_H
    #define NONLINEARSOLVERRECORD1D_H

    class NonLinearSolverRecord1D {

        public:
            // Copy and move constructors not needed
            virtual ~NonLinearSolverRecord1D() = default;
            NonLinearSolverRecord1D(const NonLinearSolverRecord1D& obj) = delete;
            NonLinearSolverRecord1D(NonLinearSolverRecord1D&& obj) = delete;
            NonLinearSolverRecord1D& operator =(const NonLinearSolverRecord1D& obj) = delete;
            NonLinearSolverRecord1D& operator =(NonLinearSolverRecord1D&& obj) = delete;

            /**
             * The constructor for the NonLinearSolverRecord1D class that sets the values of xStar, valStar, numIter, and isSuccess.
             * 
             * @param xStar the value of x that solves the equation
             * @param valStar the value of the function at xStar
             * @param numIter the number of iterations it took to solve the equation
             * @param isSuccess whether the solution was successful
            */
            NonLinearSolverRecord1D(float xStar, float valStar, int numIter, bool isSuccess)
            : xStar(xStar), valStar(valStar), numIter(numIter), isSuccess(isSuccess) {}

            // Getters
            float getXStar() const { return xStar; }
            float getValStar() const { return valStar; }
            int getNumIter() const { return numIter; }
            bool getIsSuccess() const { return isSuccess; }

        protected:
            // The value of x that solves the equation
            float xStar;
            // The value of the function at xStar
            float valStar;
            // The number of iterations it took to solve the equation
            int numIter;
            // Whether the solution was successful
            bool isSuccess;
    };

    #endif // NONLINEARSOLVERRECORD1D_H



    #ifndef NONLINEARSOLVER1D_H
    #define NONLINEARSOLVER1D_H

    class NonLinearSolver1D {

        public:
            // Copy and move constructors not needed
            virtual ~NonLinearSolver1D() = default;
            NonLinearSolver1D(const NonLinearSolver1D& obj) = delete;
            NonLinearSolver1D(NonLinearSolver1D&& obj) = delete;
            NonLinearSolver1D& operator =(const NonLinearSolver1D& obj) = delete;
            NonLinearSolver1D& operator =(NonLinearSolver1D&& obj) = delete;

            /**
             * The default constructor for the NonLinearSolver1D class.
            */
            NonLinearSolver1D() = default;

            /**
             * Solves the given function using the non-linear solver.
             * This is a pure virtual function that must be implemented by derived classes.
             * using the method of choice.
             * 
             * @param f the function to solve
             * @param a the lower end of the search bracket
             * @param b the upper end of the search bracket
             * @param n the maximum number of iterations to perform
             * @param tol the tolerance to use when determining if the solution is close enough
             * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
            */
            virtual NonLinearSolverRecord1D solve(std::shared_ptr<Function1D> f, float a, float b, int n, float tol) const = 0;
    };

    #endif // NONLINEARSOLVER1D_H



    #ifndef NONLINEARSOLVER1D_BISECTION_H
    #define NONLINEARSOLVER1D_BISECTION_H

    class NonLinearSolver1D_bisection : public csc450lib_calc::NonLinearSolver1D {

        public:
            /**
             * Solves the function using the bisection method.
             * 
             * @param f the function to solve
             * @param a the lower bound of the interval
             * @param b the upper bound of the interval
             * @param n the maximum number of iterations
             * @param tol the tolerance
             * @return the record of the solution
            */
            csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol) const;
    };

    #endif // NONLINEARSOLVER1D_BISECTION_H



    #ifndef NONLINEARSOLVER1D_NEWTONRAPHSON_H
    #define NONLINEARSOLVER1D_NEWTONRAPHSON_H

    class NonLinearSolver1D_NewtonRaphson : public csc450lib_calc::NonLinearSolver1D {

        public:
            /**
             * Uses the non-linear Newton-Raphson method to solve the given function
             * 
             * @param func the function to solve
             * @param a the lower end of the search bracket
             * @param b the upper end of the search bracket
             * @param n the maximum number of iterations to perform
             * @param tolerance the tolerance to use when determining if the solution is close enough
             * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
            */
            csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol);
    };

    #endif // NONLINEARSOLVER1D_NEWTONRAPHSON_H



    #ifndef NONLINEARSOLVER1D_SECANT_H
    #define NONLINEARSOLVER1D_SECANT_H

    class NonLinearSolver1D_secant : public csc450lib_calc::NonLinearSolver1D {

        public:
            /**
             * Uses the non-linear secant method to solve the given function
             * 
             * @param func the function to solve
             * @param x0 the first initial guess
             * @param x1 the second initial guess
             * @param n the maximum number of iterations to perform
             * @param tolerance the tolerance to use when determining if the solution is close enough
             * @return a record containing the solution, the value of the function at the solution, the number of iterations performed, and whether the solution was successful
            */
            csc450lib_calc::NonLinearSolverRecord1D solve(std::shared_ptr<csc450lib_calc::Function1D> func, float a, float b, int n, float tol);
    };

    #endif // NONLINEARSOLVER1D_SECANT_H
}