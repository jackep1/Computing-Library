CSC 450 - Scientific Computing Library
======================================

A library written for URI's CSC 450 course. It defines a number of classes for concepts such as [functions of one variable](#function1D) or of [N variables](#functionND), conversion from [N to 1 variables](#function1DtoND), [non-linear solving methods](#non-linear-solving), and [optimization](#optimization).

<a id="function1D"></a>
Functions of One Variable
-------------------------
Functions of one variable are represented by [subclasses](csc450lib/SDK/Headers/CosFunc.h) which derive from the abstract [Function1D](csc450lib/SDK/Headers/Function1D.h) class. This class includes member variables for the upper and lower bounds (exclusive) of the domain, as well as a [DomainOfDefinition](csc450lib/SDK/Headers/DomainOfDefinition.h) object. DomainOfDefinition objects can if necessary hold several disjoint subDomains. The class also includes methods for evaluating as well as finding the derivative and second derivative at a point (defined in the parent class using a general linear approximation that can be overridden), and methods which inform the user whether the function has an 'exact' derivative implementation, or relies on the base class approximation.


<a id="functionND"></a>
Functions of N Variables
------------------------
Functions of multiple variables are represented by [subclasses](csc450lib/SDK/Headers/MortarFunc.h) which derive from the abstract [FunctionND](csc450lib/SDK/Headers/FunctionND.h) class. This class includes just one member variable, N. There is one constructor which sets N, and a method for evaluating the function given a vector of inputs. FunctionND functions often work together with the Function1DtoND class to find solutions.


<a id="function1DtoND"></a>
Conversion N-D to 1D
-----------------------



<a id="NLS"></a>
Non-Linear Solving
------------------
The base [non-linear solver](csc450lib/SDK/Headers/NonLinearSolver1D.h) class allows the user to implement non-linear solving methods such as [bisection](csc450lib/SDK/Headers/NonLinearSolver1D_bisection.h). Each takes a function, a search bracket, a maximum number of iterations, and a tolerance. Use of any method will return a [record](csc450lib/SDK/Headers/NonLinearSolverRecord1D.h) of the search that includes the x and y values of the point found, the number of iterations required to get there, and a bool which says whether a solution within the tolerance was found within the maximum number of iterations allowed.


<a id="optimization"></a>
Optimization
------------
The [optimization](csc450lib/SDK/Headers/Optimizer1D.h) base class allows the user to implement a variety of optimization methods such as [parabolic approximation](csc450lib/SDK/Headers/Optimizer1D_parabolic.h) to find local minima between a pair of input values. Similar to the non-linear solvers, using any method returns a [record](csc450lib/SDK/Headers/OptimizerRecord1D.h) of the search that includes the x and y values of the point found, the number of iterations required to get there, and a bool which says whether a solution within the tolerance was found within the maximum number of iterations allowed.


<a id="applications"></a>
Applications
------------