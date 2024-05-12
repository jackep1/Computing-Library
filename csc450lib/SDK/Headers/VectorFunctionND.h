#include <vector>

namespace csc450lib_calc {

    #ifndef VECTORFUNCTIONND_H
    #define VECTORFUNCTIONND_H

    class VectorFunctionND {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~VectorFunctionND() = default;
            VectorFunctionND(const VectorFunctionND& obj) = delete;
            VectorFunctionND(VectorFunctionND&& obj) = delete;
            VectorFunctionND& operator =(const VectorFunctionND& obj) = delete;
            VectorFunctionND& operator =(VectorFunctionND&& obj) = delete;

            // Public methods for the interface
            VectorFunctionND() = default;
            VectorFunctionND(int n);
            virtual std::vector<float> func(const std::vector<float>& x) const = 0;
            virtual std::vector<std::vector<float>> grad(const std::vector<float>& x) const = 0;

        protected:
            // The number of dimensions of the function
            int N;
    };

    #endif /// VECTORFUNCTIONND_H
}