#include <Function1D.h>

#ifndef CosFunc_H
#define CosFunc_H

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

/**
 * The CosFuncNoDerivative class is a class that represents the function x --> cos(0.01x^2 + 1) / x.
 * The function is defined for all real numbers except x = 0, and is continuous on its domain.
 * This class is the same as CosFunc, but it does not have a derivative.
*/
class CosFuncNoDerivative : public csc450lib_calc::Function1D {
	
	public:
		CosFuncNoDerivative(float lowerBound, float upperBound);
		float func(float x) const;
		bool derivativeIsExact() const;
		bool secondDerivativeIsExact() const;
		std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //CosFuncNoDerivative_H



#ifndef SinFunc_H
#define SinFunc_H

/**
 * The SinFunc class is a class that represents the function x --> (sin(0.005x^2)) / (e^x - e*x).
 * The function is defined for all real numbers except x = 1, and is continuous on its domain.
*/
class SinFunc : public csc450lib_calc::Function1D {
    public:
        SinFunc();
        SinFunc(float lowerBound, float upperBound);
        float func(float x) const;
        float dfunc(float x) const;
        // float d2func(float x) const;
        bool derivativeIsExact() const;
        bool secondDerivativeIsExact() const;
        std::shared_ptr<std::string> getExpressionMMA() const;
};

#endif //SinFunc_H



#ifndef MORTARFUNC_H
#define MORTARFUNC_H

#include <FunctionND.h>

class MortarFunc : public csc450lib_calc::FunctionND {
    
    public:
        float func(const std::vector<float>& x);
    private:
        float x0;
        float y0;
        float Vx0;
        float Vy0;
        float Vz0;
        float h(float x, float y);
};

#endif /// MORTARFUNC_H