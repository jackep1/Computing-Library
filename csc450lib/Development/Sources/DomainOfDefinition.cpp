#include <DomainOfDefinition.h>

using namespace csc450lib_calc;

/**
 * Constructor for DomainOfDefinition
 * 
 * @param domain the domain
*/
DomainOfDefinition::DomainOfDefinition(std::vector<subDomain> domain) {
    this->domain = domain;
}

/**
 * Operates on this domain and another domain to find the intersection of the two.
 * 
 * @param other the other domain
 * @return the intersection of the two domains
*/
DomainOfDefinition DomainOfDefinition::intersection(const DomainOfDefinition& other) const {
    std::vector<subDomain> newDomain;
    for (int i = 0; i < this->domain.size(); i++) {
        for (int j = 0; j < other.domain.size(); j++) {
            float x1 = std::max(std::get<0>(this->domain[i]), std::get<0>(other.domain[j]));
            float x2 = std::min(std::get<1>(this->domain[i]), std::get<1>(other.domain[j]));
            bool incl1 = std::get<2>(this->domain[i]) && std::get<2>(other.domain[j]);
            bool incl2 = std::get<3>(this->domain[i]) && std::get<3>(other.domain[j]);
            if (x1 < x2) {
                newDomain.push_back(std::make_tuple(x1, x2, incl1, incl2));
            }
        }
    }
    return DomainOfDefinition(newDomain);
}

/**
 * Operates on this domain and another domain to find the union of the two.
 * Tests each subdomain for overlap with the other domain.
 * 
 * @param other the other domain
 * @return the union of the two domains
*/
DomainOfDefinition DomainOfDefinition::unionWith(const DomainOfDefinition& other) const {
    std::vector<subDomain> newDomain;
    for (int i = 0; i < this->domain.size(); i++) {
        newDomain.push_back(this->domain[i]);
    }
    for (int i = 0; i < other.domain.size(); i++) {
        bool found = false;
        for (int j = 0; j < this->domain.size(); j++) {
            float x1 = std::max(std::get<0>(this->domain[j]), std::get<0>(other.domain[i]));
            float x2 = std::min(std::get<1>(this->domain[j]), std::get<1>(other.domain[i]));
            bool incl1 = std::get<2>(this->domain[j]) && std::get<2>(other.domain[i]);
            bool incl2 = std::get<3>(this->domain[j]) && std::get<3>(other.domain[i]);
            if (x1 < x2) {
                newDomain[j] = std::make_tuple(x1, x2, incl1, incl2);
                found = true;
            }
        }
        if (!found) {
            newDomain.push_back(other.domain[i]);
        }
    }
    return DomainOfDefinition(newDomain);
}

/**
 * Determines whether this domain fully contains another domain.
 * 
 * @param other the other domain
 * @return whether this domain contains the other domain
*/
bool DomainOfDefinition::contains_subdomain(const DomainOfDefinition& other) const {
    for (int i = 0; i < other.domain.size(); i++) {
        bool found = false;
        for (int j = 0; j < this->domain.size(); j++) {
            if (std::get<0>(this->domain[j]) <= std::get<0>(other.domain[i]) &&
                std::get<1>(this->domain[j]) >= std::get<1>(other.domain[i]) &&
                std::get<2>(this->domain[j]) == std::get<2>(other.domain[i]) &&
                std::get<3>(this->domain[j]) == std::get<3>(other.domain[i])) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

/**
 * Determines whether this domain contains a point.
 * 
 * @param x the point
 * @return whether this domain contains the point
*/
bool DomainOfDefinition::contains_point(float x) const {
    for (int i = 0; i < this->domain.size(); i++) {
        if ((std::get<2>(this->domain[i]) && x < std::get<0>(this->domain[i])) ||
            (std::get<3>(this->domain[i]) && x > std::get<1>(this->domain[i])) ||
            (!std::get<2>(this->domain[i]) && x <= std::get<0>(this->domain[i])) ||
            (!std::get<3>(this->domain[i]) && x >= std::get<1>(this->domain[i]))) {
            return false;
        }
    }
    return true;
}