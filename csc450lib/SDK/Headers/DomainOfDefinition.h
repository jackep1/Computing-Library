#include <vector>

namespace csc450lib_calc {

    #ifndef SUBDOMAIN_H
    #define SUBDOMAIN_H

    /**
     * A subdomain represents a range of x values. The first
     * bool indicates whether the range is inclusive of the
     * minimum value, and the second bool indicates whether
     * the range is inclusive of the maximum value.
    */
    struct subDomain {
        float xMin;
        float xMax;
        bool inclMin;
        bool inclMax;

        subDomain(float xMin, float xMax, bool inclMin, bool inclMax)
        : xMin(xMin), xMax(xMax), inclMin(inclMin), inclMax(inclMax) {};
    };

    #endif /// SUBDOMAIN_H

    #ifndef DOMAINOFDEFINITION_H
    #define DOMAINOFDEFINITION_H

    class DomainOfDefinition {
        
        public:
            // Copy constructor is useful - used in Function1D.cpp
            virtual ~DomainOfDefinition() = default;
            // DomainOfDefinition(const DomainOfDefinition& obj) = delete;
            // DomainOfDefinition(DomainOfDefinition&& obj) = delete;
            // DomainOfDefinition& operator =(const DomainOfDefinition& obj) = delete;
            // DomainOfDefinition& operator =(DomainOfDefinition&& obj) = delete;

            DomainOfDefinition();
            DomainOfDefinition(std::vector<subDomain> domains);
            DomainOfDefinition intersection(const DomainOfDefinition& other) const;
            DomainOfDefinition unionWith(const DomainOfDefinition& other) const;
            bool contains_subdomain(const DomainOfDefinition& other) const;
            bool contains_point(float x) const;

            std::vector<subDomain> get_domain() const;
            
        protected:
            std::vector<subDomain> domain;
    };

    #endif /// DOMAINOFDEFINITION_H
}