#ifndef CosFunc_H
#define CosFunc_H

#include <Function1D.h>

/**
 * The CosFunc class is a class that represents the function x --> cos(0.01x^2 + 1) / x.
 * The function is defined for all real numbers except x = 0, and is continuous on its domain.
*/
class CosFunc : public csc450lib_calc::Function1D {

	public:
			CosFunc(float lowerBound, float upperBound);
			float func(float x) const;
			float dfunc(float x) const;
			float d2func(float x) const;
			bool derivativeIsExact() const;
			bool secondDerivativeIsExact() const;
			std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFunc_H


#ifndef CosFuncNoDerivative_H
#define CosFuncNoDerivative_H

#include <Function1D.h>

class CosFuncNoDerivative : public csc450lib_calc::Function1D {
	
	public:
		CosFuncNoDerivative(float lowerBound, float upperBound);
		float func(float x) const;
		bool derivativeIsExact() const;
		bool secondDerivativeIsExact() const;
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFuncNoDerivative_H