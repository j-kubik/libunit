#ifndef SI_H
#define SI_H

#include <cmath>
#include "../quantity.h"

namespace LibUnit{

/**
 *
 * @defgroup si_units SI units
 * These are definitions of units included in SI unit system. Units and
 * dimensions are exactly as in International System of Units, with exception
 * of Gram, which is defined as basic instead of a kilogram. This doesn't
 * introduce any practical differences in usage of those units in LibUnit.
 *
 * Multiple SI prefixes can be applied to a unit to create a derived unit that
 * differes only by a factor of integral power of ten. It should only be applied
 * to units, but not to dimensions. Lib unit provides set of helper types
 * representing such prefixes.
 *
 * Examples
 * ------------------------
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * Kilo<A> // is a unit 1000x bigger than unit A.
 * Mili<A> // is a unit of 1/1000 of A.
 * Kilo<Metre> // a kilometre.
 * Kilo<Gramm> // a kilogram.
 * Giga<Metre> // a gigametre
 * Kilo<Kilo<Metre>> // also a gigametre
 * Mili<Ampere> // miliampere
 * ~~~~~~~~~~~~~~~~~~~~
 *
 * SI units and prefixes are supplementary to LibUnit. There is no requirement
 * to use SI units provided with LibUnit. If other set of units is more
 * appropriate, it should be used instead.
 * @{
 *
 */

// ----------------------------------------------------------------------------------------------------------------------
// Multiples and Fractions

/**
 * @brief Unitlity class used as a dimensionless unit in order to represent
 * prefixes (multiples) of units.
 */
template <int f>
class IntFactor{
public:
    static constexpr double factor = f;
    typedef Compound<> Dimension;
};

/** @brief Unit prefix typedef */
template <typename T>
using Deca = Join<Power<IntFactor<10>, 1>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Hecto = Join<Power<IntFactor<10>, 2>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Kilo = Join<Power<IntFactor<10>, 3>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Mega = Join<Power<IntFactor<10>, 6>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Giga = Join<Power<IntFactor<10>, 9>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Tera = Join<Power<IntFactor<10>, 12>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Peta = Join<Power<IntFactor<10>, 15>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Exa = Join<Power<IntFactor<10>, 18>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Zetta = Join<Power<IntFactor<10>, 21>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Yotta = Join<Power<IntFactor<10>, 24>, T>;


/** @brief Unit prefix typedef */
template <typename T>
using Deci = Join<Power<IntFactor<10>, -1>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Centi = Join<Power<IntFactor<10>, -2>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Mili = Join<Power<IntFactor<10>, -3>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Micro = Join<Power<IntFactor<10>, -6>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Nano = Join<Power<IntFactor<10>, -9>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Pico = Join<Power<IntFactor<10>, -12>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Femto = Join<Power<IntFactor<10>, -15>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Atto = Join<Power<IntFactor<10>, -18>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Zepto = Join<Power<IntFactor<10>, -21>, T>;

/** @brief Unit prefix typedef */
template <typename T>
using Yocto = Join<Power<IntFactor<10>, -24>, T>;

// ----------------------------------------------------------------------------------------------------------------------

/** @cond DOXYGEN_EXCLUDE */

class Metre;
class Gram;
class Second;
class Ampere;
class Kelvin;
class Mole;
class Candela;

/** @endcond */

// ----------------------------------------------------------------------------------------------------------------------
// Dimensions for base SI units...
/** @brief Length dimension.
 * @sa si_units */
class Length{
public:
//    typedef Metre DefaultUnit;
};

/** @brief Mass dimension.
 * @sa si_units */
class Mass{
public:
//    typedef Gram DefaultUnit;
};

/** @brief Time dimension.
 * @sa si_units */
class Time{
public:
//    typedef Second DefaultUnit;
};

/** @brief Electric current dimension.
 * @sa si_units */
class ElectricCurrent{
public:
//    typedef Ampere DefaultUnit;
};

/** @brief Theromodynamic temperature dimension.
 *
 * Different units of temperature are not multiplication-convertible,so in a
 * compound expression there is no way to convert between units. Currently
 * LibUnit doesn't address this issue. Future versions will offer some measure
 * of support for this kind of .

 * @sa si_units */
// Singular-unit conversion can be performed; this must be tackled at the level of value/type pairing.
class ThermodynamicTemperature{
public:
//    typedef Kelvin DefaultUnit;
};

/** @brief Substance amount dimension.
 * @sa si_units */
class SubstanceAmount{
public:
//    typedef Mole DefaultUnit;
};


/** @brief Luminous intensity dimension.
 * @sa si_units */
class LuminousIntensity{
public:
//    typedef Candela DefaultUnit;
};

// ----------------------------------------------------------------------------------------------------------------------
// Base SI units

/** @brief Metre unit.
 * @sa si_units */
class Metre{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr unsigned int factor = 1; //!< factor equals 1 for default units
};

/**
 * @brief Gram unit.
 *
 * Although Kilogram is actual basic SI unit, Gram is defined to be basic unit
 * in order to avoid weird constructs like Mili<Kilogram>, thet would have been
 * necesary otherwise.

 * @sa si_units */
class Gram{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

/** @brief Second unit.
 * @sa si_units */
class Second{
public:
    typedef Time Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

/** @brief Ampere unit.
 * @sa si_units */
class Ampere{
public:
    typedef ElectricCurrent Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

/** @brief Kelvin unit.
 * @sa si_units */
class Kelvin{
public:
    typedef ThermodynamicTemperature Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

/** @brief Mole unit.
 * @sa si_units */
class Mole{
public:
    typedef SubstanceAmount Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

/** @brief Candela unit.
 * @sa si_units */
class Candela{
public:
    typedef LuminousIntensity Dimension; //!< Dimension of this unit
    static constexpr unsigned int  factor = 1; //!< factor equals 1 for default units
};

// ----------------------------------------------------------------------------------------------------------------------
// Derived SI units...
/** @brief Derived SI unit. */
using Radian = Compound<>;
/** @brief Derived SI unit. */
using Steradian = Compound<>;
/** @brief Derived SI unit. */
using Herz = Compound<Power<Second, -1>>;
/** @brief Derived SI unit. */
using Newton = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 1>, Power<Second, -2>>;
/** @brief Derived SI unit. */
using Pascal = Compound<Power<Kilo<Gram>, 1>, Power<Metre, -1>, Power<Second, -2>>;
/** @brief Derived SI unit. */
using Joule = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -2>>;
/** @brief Derived SI unit. */
using Watt = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -3>>;
/** @brief Derived SI unit. */
using Coulomb = Compound<Power<Second, 1>, Power<Ampere, 1>>;
/** @brief Derived SI unit. */
using Volt = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -3>, Power<Ampere, -1>>;
/** @brief Derived SI unit. */
using Farad = Compound<Power<Kilo<Gram>, -1>, Power<Metre, -2>, Power<Second, 4>, Power<Ampere, 2>>;
/** @brief Derived SI unit. */
using Ohm = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -3>, Power<Ampere, -2>>;
/** @brief Derived SI unit. */
using Siemens = Compound<Power<Kilo<Gram>, -1>, Power<Metre, -2>, Power<Second, 3>, Power<Ampere, 2>>;
/** @brief Derived SI unit. */
using Weber = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -2>, Power<Ampere, -1>>;
/** @brief Derived SI unit. */
using Tesla = Compound<Power<Kilo<Gram>, 1>, Power<Second, -2>, Power<Ampere, -1>>;
/** @brief Derived SI unit. */
using Henry = Compound<Power<Kilo<Gram>, 1>, Power<Metre, 2>, Power<Second, -2>, Power<Ampere, -2>>;

/** @brief Derived SI unit. */
using Lumen = Compound<Power<Candela, 1>>; // Actually candela times steradian.
/** @brief Derived SI unit. */
using Lux = Compound<Power<Metre, -2>, Power<Candela, 1>>;
/** @brief Derived SI unit. */
using Becquerel = Compound<Power<Second, -1>>;
/** @brief Derived SI unit. */
using Gray = Compound<Power<Metre, 2>, Power<Second, -2>>;
/** @brief Derived SI unit. */
using Sievert = Compound<Power<Metre, 2>, Power<Second, -2>>;
/** @brief Derived SI unit. */
using Katal = Compound<Power<Second, -1>, Power<Mole, 1>>;

// ----------------------------------------------------------------------------------------------------------------------

// Related non-SI units and other, commonly used
using Minute =         Join< IntFactor<60>,                   Second>;
using Hour =           Join< Power<IntFactor<60>, 2>,         Second>;
using Day =            Join< IntFactor<24>,                   Hour>;

class PlaneDegree{
public:
    typedef Compound<> Dimension;
    static constexpr double factor = M_PI / 180;
};

using PlaneMinute =    Join< Power<IntFactor<60>, -1>,        PlaneDegree>;
using PlaneSecond =    Join< Power<IntFactor<60>, -2>,        PlaneDegree>;
using Hectare =        Join< Power<IntFactor<10>, 4>,         Power<Metre, 2>>;
using Litre =          Join< Power<IntFactor<10>, -3>,        Power<Metre, 3>>;
using Tonne =          Join< Power<IntFactor<10>, 6>,         Gram>;

class ElectronVolt{
public:
    typedef DimensionOf<Joule> Dimension;
    static constexpr double factor = 1.60217653e-19*FactorOf<Joule>::value;
};

class AtomicMass{
public:
    typedef Mass Dimension;
    static constexpr double factor = 1.660538921e-24; //!< factor equals 1.660538921e-27 kg

};

class AstronomicalUnit{
public:
    typedef Length Dimension;
    static constexpr unsigned long long factor = 149597870692;
};


// ToDo: neper and decibel
// ToDo: natural units here or rather as constants?

using Angstrom =       Join< Power<IntFactor<10>, -10>,        Metre>;
using Are =            Join< Power<IntFactor<10>, 2>,          Power<Metre,2>>;
using Barn =           Join< Power<IntFactor<10>, -28>,        Power<Metre,2>>;
using Bar =            Join< Power<IntFactor<10>, 5>,          Pascal>;

class Atmosphere{
public:
    typedef DimensionOf<Pascal> Dimension;
    static constexpr auto factor = 101325*FactorOf<Pascal>::value;
};

class MillimetreOfMercury{
public:
    typedef DimensionOf<Pascal> Dimension;
    static constexpr auto factor = 133.322387415*FactorOf<Pascal>::value;
};

class Torr{
public:
    typedef DimensionOf<Pascal> Dimension;
    static constexpr auto factor = 133.322368421*FactorOf<Pascal>::value;
};

// -----------------------------------------------------------------------------------------------------------------------

/** @cond INTERNAL */

namespace Helper{

/**
 * @brief Helper class used as underlying type for helper variables used for
 * inline unit creation.
 */

class OneType{
public:
    /**
     * @brief OneType default constructor.
     */
    inline OneType(){}

    /**
     * @brief OneType constructs from anything.
     */
    template <typename T>
    inline OneType(const T&){}

    /**
     * @brief Converts to anything.
     */
    template <typename T>
    inline operator T() const{
        return 1;
    }
};

/** @brief Helper operator. */
template <typename T>
inline T operator*(T t, OneType){
    return t;
}

/** @brief Helper operator. */
template <typename T>
inline T operator*(OneType, T t){
    return t;
}

/** @brief Helper operator. */
inline int operator*(OneType, OneType){
    return 1;
}

}

/** @endcond */

/** @brief Helper variable used for inline unit composition. */
Quantity<Metre, Helper::OneType>       metre;
/** @brief Helper variable used for inline unit composition. */
Quantity<Gram, Helper::OneType>        gram;
/** @brief Helper variable used for inline unit composition. */
Quantity<Second, Helper::OneType>      second;
/** @brief Helper variable used for inline unit composition. */
Quantity<Ampere, Helper::OneType>      ampere;
/** @brief Helper variable used for inline unit composition. */
Quantity<Kelvin, Helper::OneType>      kelvin;
/** @brief Helper variable used for inline unit composition. */
Quantity<Mole, Helper::OneType>        mole;
/** @brief Helper variable used for inline unit composition. */
Quantity<Candela, Helper::OneType>     candela;

/** @brief Helper variable used for inline unit composition. */
Quantity<Radian, Helper::OneType>      radian;
/** @brief Helper variable used for inline unit composition. */
Quantity<Steradian, Helper::OneType>   steradian;
/** @brief Helper variable used for inline unit composition. */
Quantity<Herz, Helper::OneType>        herz;
/** @brief Helper variable used for inline unit composition. */
Quantity<Newton, Helper::OneType>      newton;
/** @brief Helper variable used for inline unit composition. */
Quantity<Pascal, Helper::OneType>      pascal;
/** @brief Helper variable used for inline unit composition. */
Quantity<Joule, Helper::OneType>       joule;
/** @brief Helper variable used for inline unit composition. */
Quantity<Watt, Helper::OneType>        watt;
/** @brief Helper variable used for inline unit composition. */
Quantity<Coulomb, Helper::OneType>     coulomb;
/** @brief Helper variable used for inline unit composition. */
Quantity<Volt, Helper::OneType>        volt;
/** @brief Helper variable used for inline unit composition. */
Quantity<Farad, Helper::OneType>       farad;
/** @brief Helper variable used for inline unit composition. */
Quantity<Ohm, Helper::OneType>         ohm;
/** @brief Helper variable used for inline unit composition. */
Quantity<Siemens, Helper::OneType>     siemens;
/** @brief Helper variable used for inline unit composition. */
Quantity<Weber, Helper::OneType>       weber;
/** @brief Helper variable used for inline unit composition. */
Quantity<Tesla, Helper::OneType>       tesla;
/** @brief Helper variable used for inline unit composition. */
Quantity<Henry, Helper::OneType>       henry;
/** @brief Helper variable used for inline unit composition. */
Quantity<Lumen, Helper::OneType>       lumen;
/** @brief Helper variable used for inline unit composition. */
Quantity<Lux, Helper::OneType>         lux;
/** @brief Helper variable used for inline unit composition. */
Quantity<Becquerel, Helper::OneType>   becquerel;
/** @brief Helper variable used for inline unit composition. */
Quantity<Gray, Helper::OneType>        gray;
/** @brief Helper variable used for inline unit composition. */
Quantity<Sievert, Helper::OneType>     sievert;
/** @brief Helper variable used for inline unit composition. */
Quantity<Katal, Helper::OneType>       katal;

/** }@ */

}

#endif // SI_H
