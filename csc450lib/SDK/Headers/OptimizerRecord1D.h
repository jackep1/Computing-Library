#ifndef OPTIMIZERRECORD1D_H
#define OPTIMIZERRECORD1D_H

namespace csc450lib_calc {

    class OptimizerRecord1D {
        
        public:
            // Copy and move constructors not needed
            virtual ~OptimizerRecord1D() = default;
            OptimizerRecord1D(const OptimizerRecord1D& obj) = delete;
            OptimizerRecord1D(OptimizerRecord1D&& obj) = delete;
            OptimizerRecord1D& operator =(const OptimizerRecord1D& obj) = delete;
            OptimizerRecord1D& operator =(OptimizerRecord1D&& obj) = delete;

            // Public variables
            float optX;
            float optVal;
            int numIters;
            bool isSuccess;

            // Constructor
            OptimizerRecord1D(float optX, float optVal, int numIters, bool isSuccess) {
                this->optX = optX;
                this->optVal = optVal;
                this->numIters = numIters;
                this->isSuccess = isSuccess;
            }
    };
}

#endif // OPTIMIZERRECORD1D_H