Introduction                            {#mainpage}
------------------------
LibUnit is a library that helps to automate unit checking and converting in C++
code that performs computation on values representing quantities that can be
represented using different units. At it's current development stage it is
compile time only library; this means that all the automation is performed
inside compiler and generated executable code (when optimized) should not be
influenced by it significantly. It is aimed not to incur any unnecesary
performance penalties. Major drawback of it, is that if a program cannot use
compile time unit checking because units are varying depending on runtime data,
the library provides no support. This will be adressed in future
releases of LibUnit.


Main Concepts
------------------------

Before learning the library specifics, it is important to learn basic concepts
that LibUnit is based upon:


 - \e %Quantity is a physical property that can be measured. It can be compared
against quantities of the same dimension, but _it has no numeric value on it's
own._ A quantity can be expressed as a pair consiting of a Unit quantity of the
same dimension and a number by which this unit quantity must be multiplied in
order to be equal to such quantity. Possible examples of quantities include:
length of a table, duration of a movie, electric current in a cable.

 - _Dimension_ is a class of quantities that can be compared between each other.
Quantitity can be expressed as other quantity of the same dimension multiplied
by a number. Possible examples include: length, time, electric current.

 - _Unit_ is a specific quantity that is adopted by convention and is used as a
reference for other quantities of the same dimension. In order to perform
computations on quantities, all of them are expressed in terms of unit quantity
of the same dimension and a number. Computations are then performed on numbers
representing quantities. The results can only be meaningful if numbers used
had right corresponding units. Possible units for length dimension include:
metre, foot, kilometre, nanometre, mile, light year. This set is not closed, and
it is up to a user what units will he use for his purpose. Units outside of
standard sets can also be used, but this creates problems when sharing data, it
makes it necesary  to pass additional information about used unit. For
example if a pencil is used as a unit, when sharing data, either length of a
pencil expressed in a unit others understand (ie. a SI unit), or the pencil
itself must be shared as well.

Goals
------------------------

There are different conventions as to which quantity is to be used as a unit,
and many units can also adopt prefixes that express decadic multiples or
fractions thereof. Because of that, conversions of quantity values are often
necesary when performing calculations involving different quantities. LibUnit
provides automatic detection of situations in which such conversion is required,
and performs it implicitly. For example

~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}

Quantity<U, double> q1(1.1);
Quantity<Kilo<U>, double> q2 = q1;
std::cout << q2; // Prints 0.0011

~~~~~~~~~~~~~~~~~~~~~~~~

Calculations on quantities are usually performed on its values using some
standarized set of uints. In order to check validity of used formulas,
dimensional analysis is often used. LibUnit is able to compute dimension of a
result of mathematical expression on quantities and compare it to dimension
of a variable holding the result. If dimensions are not equal, compilation error
is generated, hinting use of an invalid formula. For example

~~~~~~~~~~~~~~~~~~~~~~~~ {.cpp}

Quantity<U, double> q1(1.1);
Quantity<V, double> q2(3.12356);

Quantity<Compound<U,V>, double> q3 = q1*q2; // correct
Quantity<Compound<U,V>, double> q4 = q1/q2; // compilation error
Quantity<Compound<U,Power<V,-1>>, double> q5 = q1/q2; // correct

~~~~~~~~~~~~~~~~~~~~~~~~

Structure
------------------------

ToDo: write about structure of LibUnit.

Examples
------------------------

ToDo: add some more examples, or even create additional page for it.












