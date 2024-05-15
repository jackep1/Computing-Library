#include <DomainOfDefinition.h>
#include <limits>
#include <algorithm>

using namespace csc450lib_calc;

DomainOfDefinition::DomainOfDefinition()
: domain({subDomain(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), false, false)}) {};

DomainOfDefinition::DomainOfDefinition(std::vector<subDomain> domains)
: domain(domains) {};

DomainOfDefinition DomainOfDefinition::intersection(const DomainOfDefinition& other) const {
    std::vector<subDomain> newDomain;
    for (auto& subdomain : this->domain) {
        for (auto& othersubdomain : other.domain) {
            float xMin = std::max(subdomain.xMin, othersubdomain.xMin);
            bool inclMin = (subdomain.xMin < othersubdomain.xMin) ? othersubdomain.inclMin : subdomain.inclMin;

            float xMax = std::min(subdomain.xMax, othersubdomain.xMax);
            bool inclMax = (subdomain.xMax > othersubdomain.xMax) ? subdomain.inclMax : othersubdomain.inclMax;

            if (xMin < xMax || xMin == xMax && inclMin && inclMax) {
                newDomain.push_back(subDomain{xMin, xMax, inclMin, inclMax});
            }
        }
    }
    return DomainOfDefinition(newDomain);
}

DomainOfDefinition DomainOfDefinition::unionWith(const DomainOfDefinition& other) const {
    std::vector<subDomain> newDomain;
    std::vector<subDomain> combined = this->domain;

    combined.insert(combined.end(), other.domain.begin(), other.domain.end());

    std::sort(combined.begin(), combined.end(),
        [](const subDomain& a, const subDomain& b) {
            return a.xMin < b.xMin;
        });

    for (const auto& subdomain : combined) {
        if (newDomain.empty() || subdomain.xMin > newDomain.back().xMax ||
            (subdomain.xMin == newDomain.back().xMax && (!subdomain.inclMin && !newDomain.back().inclMax))) {
            newDomain.push_back(subdomain);
        } else {
            newDomain.back().xMax = std::max(newDomain.back().xMax, subdomain.xMax);
            newDomain.back().inclMax = (newDomain.back().xMax == subdomain.xMax) ? subdomain.inclMax || newDomain.back().inclMax : true;
        }
    }
    return DomainOfDefinition(newDomain);
}

bool DomainOfDefinition::contains_subdomain(const DomainOfDefinition& other) const {
    for (const auto& othersubdomain : other.domain) {
        bool found = false;
        for (const auto& subdomain : this->domain) {
            if ((subdomain.xMin < othersubdomain.xMin || (subdomain.xMin == othersubdomain.xMin && subdomain.inclMin == othersubdomain.inclMin)) &&
                (subdomain.xMax > othersubdomain.xMax || (subdomain.xMax == othersubdomain.xMax && subdomain.inclMax == othersubdomain.inclMax))) {
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

bool DomainOfDefinition::contains_point(float x) const {
    for (const auto& subdomain : this->domain) {
        if ((x > subdomain.xMin || (x == subdomain.xMin && subdomain.inclMin)) &&
            (x < subdomain.xMax || (x == subdomain.xMax && subdomain.inclMax))) {
            return true;
        }
    }
    return false;
}

std::vector<subDomain> DomainOfDefinition::get_domain() const {
    return this->domain;
}