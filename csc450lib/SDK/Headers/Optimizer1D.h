#include <Function1D.h>

namespace csc450lib_calc {

    #ifndef OPTIMIZERRECORD1D_H
    #define OPTIMIZERRECORD1D_H

    class OptimizerRecord1D {
        
        public:
            // Copy and move constructors not needed
            virtual ~OptimizerRecord1D() = default;
            OptimizerRecord1D(const OptimizerRecord1D& obj) = delete;
            OptimizerRecord1D(OptimizerRecord1D&& obj) = delete;
            OptimizerRecord1D& operator =(const OptimizerRecord1D& obj) = delete;
            OptimizerRecord1D& operator =(OptimizerRecord1D&& obj) = delete;

            /**
             * The constructor for the OptimizerRecord1D class that sets the values of optX, optVal, numIters, and isSuccess.
             * 
             * @param optX the value of x that minimizes the function
             * @param optVal the value of the function at optX
             * @param numIters the number of iterations it took to minimize the function
             * @param isSuccess whether the minimization was successful
            */
            OptimizerRecord1D(float optX, float optVal, int numIters, bool isSuccess)
            : optX(optX), optVal(optVal), numIters(numIters), isSuccess(isSuccess) {}

            // Getters
            float getOptX() const { return optX; }
            float getOptVal() const { return optVal; }
            int getNumIters() const { return numIters; }
            bool getIsSuccess() const { return isSuccess; }

        protected:
            // The value of x that minimizes the function
            float optX;
            // The value of the function at optX
            float optVal;
            // The number of iterations it took to minimize the function
            int numIters;
            // Whether the minimization was successful
            bool isSuccess;
    };

    #endif // OPTIMIZERRECORD1D_H



    #ifndef OPTIMIZER1D_H
    #define OPTIMIZER1D_H

    class Optimizer1D {

        public:
            // Copy and move constructors not needed
            virtual ~Optimizer1D() = default;
            Optimizer1D(const Optimizer1D& obj) = delete;
            Optimizer1D(Optimizer1D&& obj) = delete;
            Optimizer1D& operator =(const Optimizer1D& obj) = delete;
            Optimizer1D& operator =(Optimizer1D&& obj) = delete;

            /**
             * The constructor for the Optimizer1D class that sets the function to minimize.
             * 
             * @param f the function to minimize
            */
            Optimizer1D(std::shared_ptr<Function1D> f);

            /**
             * Sets the function to minimize.
             * 
             * @param f the function to minimize
            */
            void setFunction(std::shared_ptr<Function1D> f);

            /**
             * Get the function to optimize
             * 
             * @return The function to optimize
            */
            std::shared_ptr<const Function1D> getFunction() const;

            /**
             * Minimizes the function.
             * This is a pure virtual function that must be implemented by derived classes
             * using the method of choice.
             * 
             * @param startX the starting x value
             * @param xMin the minimum x value
             * @param xMax the maximum x value
             * @param tol the tolerance
             * @param maxNumIters the maximum number of iterations
             * @return the record of the optimization
            */
            virtual OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const = 0;

        protected:
            // The function to minimize
            std::shared_ptr<Function1D> f;
    };

    #endif // OPTIMIZER1D_H



    #ifndef OPTIMIZER1D_STEEPESTDESCENT_H
    #define OPTIMIZER1D_STEEPESTDESCENT_H

    class Optimizer1D_steepestDescent : public csc450lib_calc::Optimizer1D {

        public:
            /**
             * The constructor for the Optimizer1D_steepestDescent class that sets the function to minimize.
             * 
             * @param f the function to minimize
            */
            Optimizer1D_steepestDescent(std::shared_ptr<Function1D> f) : Optimizer1D(f) {};

            /**
             * Minimization using the steepest descent method.
             * 
             * @param startX the starting x value
             * @param xMin the minimum x value
             * @param xMax the maximum x value
             * @param tol the tolerance
             * @param maxNumIters the maximum number of iterations allowed
             * @return the record of the optimization
            */
            csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
    };

    #endif // OPTIMIZER1D_STEEPESTDESCENT_H



    #ifndef OPTIMIZER1D_PARABOLIC_H
    #define OPTIMIZER1D_PARABOLIC_H

    class Optimizer1D_parabolic : public csc450lib_calc::Optimizer1D {

        public:
            /**
             * The constructor for the Optimizer1D_parabolic class that sets the function to minimize.
             * 
             * @param f the function to minimize
            */
            Optimizer1D_parabolic(std::shared_ptr<csc450lib_calc::Function1D> f) : Optimizer1D(f) {};

            /**
             * Minimization using the parabolic method.
             * 
             * @param startX the starting x value
             * @param xMin the minimum x value
             * @param xMax the maximum x value
             * @param tol the tolerance
             * @param maxNumIters the maximum number of iterations allowed
             * @return the record of the optimization
            */
            csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
    };

    #endif // OPTIMIZER1D_PARABOLIC_H



    #ifndef OPTIMIZER1D_GSS_H
    #define OPTIMIZER1D_GSS_H

    class Optimizer1D_gss : public csc450lib_calc::Optimizer1D {

        public:
            /**
             * The constructor for the Optimizer1D_gss class that sets the function to minimize.
             * 
             * @param f the function to minimize
            */
            Optimizer1D_gss(std::shared_ptr<csc450lib_calc::Function1D> f) : Optimizer1D(f) {};

            /**
             * Minimization using the golden section search method.
             * 
             * @param startX the starting x value
             * @param xMin the minimum x value
             * @param xMax the maximum x value
             * @param tol the tolerance
             * @param maxNumIters the maximum number of iterations allowed
             * @return the record of the optimization
            */
            csc450lib_calc::OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const;
    };

    #endif // OPTIMIZER1D_GSS_H
}