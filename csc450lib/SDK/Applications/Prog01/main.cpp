#include <iostream>
#include <fstream>

#include <Function1D.h>
#include <CosFunc.h>
#include <SinFunc.h>
#include <PolynomialFunction1D.h>

#include <CSC450Lib.h>
#include <CSC450Exception.h>

using namespace std;
using namespace csc450lib;
using namespace csc450lib_calc;

int main(int argc, const char* argv[])
{
	float inf = INFINITY;
	float ninf = -INFINITY;

	ofstream cosFile("../../../../MMA Files/cos.txt");
	ofstream sinFile("../../../../MMA Files/sin.txt");
	ofstream p1File("../../../../MMA Files/p1.txt");
	ofstream p2File("../../../../MMA Files/p2.txt");

	// CosFunc defined only over positive numbers
	CosFunc f(-1, inf);
	cout << "CosFunc called with zero denominator: ";
	try {
		float solution = f.func(0);
		cout << "f(0) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "CosFunc with valid input: ";
	try {
		float solution = f.func(0.5);
		cout << "f(0.5) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "CosFunc called with x out of domain: ";
	try {
		float solution = f.func(-1.5);
		cout << "f(-0.5) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	} cout << endl;

	for (int x = 0; x < 100; x++) {
		try {
			float y = f.func(x);
			cosFile << x << " " << y << "\n";
		} catch (const csc450lib::CSC450Exception& e) {
			continue;
		}
	}


	// SinFunc defined only over negative numbers
	SinFunc* g = new SinFunc(ninf, 2);
	cout << "SinFunc called with zero denominator: ";
	try {
		float solution = g->func(1);
		cout << "g(1) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "SinFunc called with valid input: ";
	try {
		float solution = g->func(-0.5);
		cout << "g(-0.5) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "SinFunc called with x out of domain: ";
	try {
		float solution = g->func(2.5);
		cout << "g(0.5) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	} cout << endl;

	for (int x = -100; x < 0; x++) {
		try {
			float y = g->func(x);
			sinFile << x << " " << y << "\n";
		} catch (const csc450lib::CSC450Exception& e) {
			continue;
		}
	}


	// Polynomial function defined over ]1, 10[
	shared_ptr<PolynomialFunction1D> h = make_shared<PolynomialFunction1D>(vector<float>{1, -2, 3, -4, 5}, 1, 10);
	cout << "Polynomial formula 1, only defined ]1, 10[ : "; cout << *h->getExpressionMMA() << endl;
	cout << "P1 at 1.1: ";
	try {
		float solution = h->func(1.1);
		cout << "h(1.1) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "P1 called with x out of domain: ";
	try {
		float solution = h->func(0.1);
		cout << "h(0.1) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	} cout << endl;

	for (float x = 1.1; x < 10; x += 0.1) {
		try {
			float y = h->func(x);
			p1File << x << " " << y << "\n";
		} catch (const csc450lib::CSC450Exception& e) {
			continue;
		}
	}


	//Polynomial function defined over ]-10, -1[
	shared_ptr<PolynomialFunction1D> l = make_shared<PolynomialFunction1D>(vector<float>{5, -4, 3, -2, 1}, -10, -1);
	cout << "Polynomial formula 2, only defined ]-10, -1[ : "; cout << *l->getExpressionMMA() << endl;
	cout << "P2 at -1.1: ";
	try {
		float solution = l->func(-1.1);
		cout << "l(-1.1) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	cout << "P2 called with x out of domain: ";
	try {
		float solution = l->func(-0.1);
		cout << "l(-0.1) = " << solution << endl;
	} catch (const csc450lib::CSC450Exception& e) {
		cout << e.getMessage() << endl;
	}

	for (float x = -9.9; x < -1; x += 0.1) {
		try {
			float y = l->func(x);
			p2File << x << " " << y << "\n";
		} catch (csc450lib::CSC450Exception& e) {
			continue;
		}
	}


	cosFile.close();
	sinFile.close();
	p1File.close();
	p2File.close();
	
	return 0;
}