#ifndef CosFuncNoDerivative_H
#define CosFuncNoDerivative_H

#include "Function1D.h"

class CosFuncNoDerivative : public csc450lib_calc::Function1D {
	public:
		CosFuncNoDerivative();
		CosFuncNoDerivative(float lowerBound, float upperBound);
		float func(float x) const;
		bool derivativeIsExact() const;
		bool secondDerivativeIsExact() const;
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFuncNoDerivative_H