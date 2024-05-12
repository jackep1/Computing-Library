#ifndef VECTORFUNCTION1D_H
#define VECTORFUNCTION1D_H

#include <DomainOfDefinition.h>
#include <Function1D.h>
#include <limits>
#include <memory>

namespace csc450lib_calc {

    class VectorFunction1D {

        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~VectorFunction1D() = default;
            VectorFunction1D(const VectorFunction1D& obj) = delete;
            VectorFunction1D(VectorFunction1D&& obj) = delete;
            VectorFunction1D& operator =(const VectorFunction1D& obj) = delete;
            VectorFunction1D& operator =(VectorFunction1D&& obj) = delete;

            // Public methods for the interface
            VectorFunction1D() = default;
            VectorFunction1D(float xmin, float xmax);
            VectorFunction1D(std::shared_ptr<DomainOfDefinition> d);
            virtual float func(float x) const = 0;
            virtual float dfunc(float x) const;
            virtual float d2func(float x) const;
            virtual std::shared_ptr<std::string> getExpressionMMA() const = 0;

            // A few methods that get properties of a function
            bool isDefinedAt(float x) const;
            float getLowerBound(void) const;
            float getUpperBound(void) const;
            virtual bool derivativeIsExact() const = 0;
            virtual bool secondDerivativeIsExact() const = 0;

        protected:
            DomainOfDefinition domain;
    };
}

#endif /// VECTORFUNCTION1D_H