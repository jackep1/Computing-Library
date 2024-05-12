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

            // Constructor
            OptimizerRecord1D(float optX, float optVal, int numIters, bool isSuccess) {
                this->optX = optX;
                this->optVal = optVal;
                this->numIters = numIters;
                this->isSuccess = isSuccess;
            }
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

            // Public methods
            Optimizer1D(std::shared_ptr<Function1D> f);
            void setFunction(std::shared_ptr<Function1D> f);
            std::shared_ptr<const Function1D> getFunction() const;
            virtual OptimizerRecord1D minimize(float startX, float xMin, float xMax, float tol, int maxNumIters) const = 0;

            std::shared_ptr<Function1D> f;
    };

    #endif // OPTIMIZER1D_H



    #ifndef OPTIMIZER1D_STEEPESTDESCENT_H
    #define OPTIMIZER1D_STEEPESTDESCENT_H

    class Optimizer1D_steepestDescent : public csc450lib_calc::Optimizer1D {

        public:
            Optimizer1D_steepestDescent(std::shared_ptr<Function1D> f) : Optimizer1D(f) {};
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
}