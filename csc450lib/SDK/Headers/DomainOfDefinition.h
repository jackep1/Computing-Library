#ifndef DOMAINOFDEFINITION_H
#define DOMAINOFDEFINITION_H

#include <Function1D.h>
#include <vector>
#include <tuple>

/**
 * A subdomain represents a range of x values beginning at
 * the first float and ending at the second float. The first
 * bool indicates whether the range is inclusive of the first
 * float, and the second bool indicates whether the range is
 * inclusive of the second float.
*/
using subDomain = std::tuple<float, float, bool, bool>;

namespace csc450lib_calc {

    class DomainOfDefinition {
        
        public:
            // Don't need copy and move constructors and assignment operators
            virtual ~DomainOfDefinition() = default;
            DomainOfDefinition(const DomainOfDefinition& obj) = delete;
            DomainOfDefinition(DomainOfDefinition&& obj) = delete;
            DomainOfDefinition& operator =(const DomainOfDefinition& obj) = delete;
            DomainOfDefinition& operator =(DomainOfDefinition&& obj) = delete;

            DomainOfDefinition(std::vector<subDomain> domain);
            DomainOfDefinition intersection(const DomainOfDefinition& other) const;
            DomainOfDefinition unionWith(const DomainOfDefinition& other) const;
            bool contains_subdomain(const DomainOfDefinition& other) const;
            bool contains_point(float x) const;
            
            std::vector<subDomain> domain;
    };
}

#endif /// DOMAINOFDEFINITION_H