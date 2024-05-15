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
        // The minimum x value of the subdomain
        float xMin;
        // The maximum x value of the subdomain
        float xMax;
        // Whether the minimum value is included in the subdomain
        bool inclMin;
        // Whether the maximum value is included in the subdomain
        bool inclMax;

        /**
         * Constructor for the subDomain class that initializes the
         * minimum and maximum x values and whether the minimum and
         * maximum values are included in the subdomain.
        */
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

            /**
             * Default constructor sets the domain to be the entire real line.
            */
            DomainOfDefinition();

            /**
             * Constructor initializes the domain using a vector of subdomains.
             * 
             * @param domain the domain
            */
            DomainOfDefinition(std::vector<subDomain> domains);

            /**
             * Operates on this domain and another domain to find the intersection of the two.
             * 
             * @param other the other domain
             * @return the intersection of the two domains
            */
            DomainOfDefinition intersection(const DomainOfDefinition& other) const;

            /**
             * Operates on this domain and another domain to find the union of the two.
             * Tests each subdomain for overlap with the other domain.
             * 
             * @param other the other domain
             * @return the union of the two domains
            */
            DomainOfDefinition unionWith(const DomainOfDefinition& other) const;

            /**
             * Determines whether this domain fully contains another domain.
             * 
             * @param other the other domain
             * @return true if this domain contains the other domain, false otherwise
            */
            bool contains_subdomain(const DomainOfDefinition& other) const;

            /**
             * Determines whether a point is contained within the domain.
             * 
             * @param x the point to check
             * @return true if the point is contained within the domain, false otherwise
            */
            bool contains_point(float x) const;

            /**
             * Gets the domain of the function.
             * 
             * @return the domain of the function
            */
            std::vector<subDomain> get_domain() const;
            
        protected:
            // The domain of the function
            std::vector<subDomain> domain;
    };

    #endif /// DOMAINOFDEFINITION_H
}