# CSC 450 - Scientific Computing Library

A library written for URI's CSC 450 course. It defines a number of classes for concepts such as [functions of one variable](#function1D) or of [N variables](#functionND), conversion from [N to 1 variables](#function1DtoND), [non-linear solving methods](#non-linear-solving), and [optimization](#optimization).



<a id="function1D"></a>
## Functions of One Variable
Functions of one variable are represented by [subclasses](csc450lib/SDK/Headers/CosFunc.h) which derive from the abstract [Function1D](csc450lib/SDK/Headers/Function1D.h) class. This class includes member variables for the upper and lower bounds (exclusive) of the domain, as well as a [DomainOfDefinition](csc450lib/SDK/Headers/DomainOfDefinition.h) object. DomainOfDefinition objects can if necessary hold several disjoint subDomains. The class also includes methods for evaluating as well as finding the derivative and second derivative at a point (defined in the parent class using a general linear approximation that can be overridden), and methods which inform the user whether the function has an 'exact' derivative implementation, or relies on the base class approximation.


<a id="functionND"></a>
## Functions of N Variables
Functions of multiple variables are represented by [subclasses](csc450lib/SDK/Headers/MortarFunc.h) which derive from the abstract [FunctionND](csc450lib/SDK/Headers/FunctionND.h) class. This class includes just one member variable, N. There is one constructor which sets N, and a method for evaluating the function given a vector of inputs. FunctionND functions often work together with the Function1DtoND class to find solutions.


<a id="function1DtoND"></a>
## Conversion N-D to 1D
Functions of one variable are much easier to work with, so there is a [conversion class](csc450lib/SDK/Headers/Function1DfromND.h) for turning functions of N dimensions into something simpler. Instances are created with a [function of N variables](csc450lib/SDK/Headers/FunctionND.h), a vector of initial x0 values, and a vector of u values. The class has a method for evaluating the N-D function it points to using a single variable (u).


<a id="NLS"></a>
## Non-Linear Solving
The base [non-linear solver](csc450lib/SDK/Headers/NonLinearSolver1D.h) class allows the user to implement non-linear solving methods such as [bisection](csc450lib/SDK/Headers/NonLinearSolver1D_bisection.h). Each takes a function, a search bracket, a maximum number of iterations, and a tolerance. Use of any method will return a [record](csc450lib/SDK/Headers/NonLinearSolverRecord1D.h) of the search that includes the x and y values of the point found, the number of iterations required to get there, and a bool which says whether a solution within the tolerance was found within the maximum number of iterations allowed.


<a id="optimization"></a>
## Optimization
The [optimization](csc450lib/SDK/Headers/Optimizer1D.h) base class allows the user to implement a variety of optimization methods such as [parabolic approximation](csc450lib/SDK/Headers/Optimizer1D_parabolic.h) to find local minima between a pair of input values. Similar to the non-linear solvers, using any method returns a [record](csc450lib/SDK/Headers/OptimizerRecord1D.h) of the search that includes the x and y values of the point found, the number of iterations required to get there, and a bool which says whether a solution within the tolerance was found within the maximum number of iterations allowed.


<a id="applications"></a>
## Applications
In addition to the library code, there are a few simple applications that demonstrate the code at work.

<a id="prog1"></a>
### Program 1
The first program is a very simple demonstration of implementing 1-dimensional functions; there are four examples, one [cosine function](csc450lib/SDK/Headers/CosFunc.h), one [sine function](csc450lib/SDK/Headers/SinFunc.h), and two examples of a [polynomial function](csc450lib/SDK/Headers/PolynomialFunction1D.h), which is a subclass of [Function1D](csc450lib/SDK/Headers/Function1D.h). There's a demonstration of their domains, with a few attempts at evaluating them returning the appropriate errors, and then they are evaluated for a sample of inputs, with input/output pairs written to local files for analysis in Mathematica.

<a id="prog2"></a>
### Program 2
The first part of program 2 demonstrates 1-dimensional functions' method for finding the derivative of a function. There are two methods for this, the base class's approximation method, or a subclass's implementation of an exact method. The two methods are compared for time by implementing the same function twice, once [with the exact method](csc450lib/SDK/Headers/CosFunc.h) and once [with the approximation](csc450lib/SDK/Headers/CosFuncNoDerivative.h).  
The second part of program 2 demonstrates the use of several classes created to find the path a bouncing object takes off of a surface. The [surface class](csc450lib/SDK/Headers/Surface.h) is a 1-dimensional function that has an additional member variable alpha, which represents the surface's elasticity, and an additional method for getting the outgoing velocity of an object after collision. The [ballistic function](csc450lib/SDK/Headers/BallisticFunction.h) class has members for the initial position (x, y) and the initial components of velocity in each direction. It has methods both for getting position and for getting position/velocity at given time t.  
An instance of the surface class can be combined with an instance of a ballistic function in an instance of the [collision class](csc450lib/SDK/Headers/CollisionProblem.h), which is 1-dimensional function. This function returns the difference between the height of the ballistic object at a given time and the elevation of the surface. This allows the function to be evaluated by a [non-linear solver](csc450lib/SDK/Headers/NonLinearSolver1D.h) to find the point of collision (when the function is zero). This can be repeated to find where a bouncing object lands following consecutive bounces.

<!--
<a id="prog3"></a>
### Program 3

-->
<!--
<a id="prog4"></a>
### Program 4

-->