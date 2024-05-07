#ifndef NONLINEARSOLVERRECORD1D_H
#define NONLINEARSOLVERRECORD1D_H

namespace csc450lib_calc {

    class NonLinearSolverRecord1D {

        public:
            // Copy and move constructors not needed
            virtual ~NonLinearSolverRecord1D() = default;
            NonLinearSolverRecord1D(const NonLinearSolverRecord1D& obj) = delete;
            NonLinearSolverRecord1D(NonLinearSolverRecord1D&& obj) = delete;
            NonLinearSolverRecord1D& operator =(const NonLinearSolverRecord1D& obj) = delete;
            NonLinearSolverRecord1D& operator =(NonLinearSolverRecord1D&& obj) = delete;

            // Public variables
            float xStar;
            float valStar;
            int numIter;
            bool isSuccess;

            // Constructor
            NonLinearSolverRecord1D(float xStar, float valStar, int numIter, bool isSuccess) {
                this->xStar = xStar;
                this->valStar = valStar;
                this->numIter = numIter;
                this->isSuccess = isSuccess;
            }
    };
}

#endif