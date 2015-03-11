#ifndef FACTORS_H
#define FACTORS_H

#include "units.h"

/**
 * @file factors.h
 */

// ----------------------------------------------------------------------------------------------------------------------
// Multiples and Fractions

/**
 * @defgroup ten_powers Powers of 10
 * Multiple prefix can be applied to a unit to create a derived unit that
 * differes only be a integral power of ten. It can oly be applied to units,
 * never to dimensions.
 * @{
 */

/**
 * @brief Unitlity class used as a dimensionless unit in order to represent
 * prefixes (multiples) of units.
 */
class Factor10{
public:
    static constexpr double factor = 10;
    typedef Compound<> Dimension;
};

template <typename T>
using Deca = Join<Power<Factor10, 1>, T>;

template <typename T>
using Hecto = Join<Power<Factor10, 2>, T>;

template <typename T>
using Kilo = Join<Power<Factor10, 3>, T>;

template <typename T>
using Mega = Join<Power<Factor10, 6>, T>;

template <typename T>
using Giga = Join<Power<Factor10, 9>, T>;

template <typename T>
using Tera = Join<Power<Factor10, 12>, T>;

template <typename T>
using Peta = Join<Power<Factor10, 15>, T>;

template <typename T>
using Exa = Join<Power<Factor10, 18>, T>;

template <typename T>
using Zetta = Join<Power<Factor10, 21>, T>;

template <typename T>
using Yotta = Join<Power<Factor10, 24>, T>;


template <typename T>
using Deci = Join<Power<Factor10, -1>, T>;

template <typename T>
using Centi = Join<Power<Factor10, -2>, T>;

template <typename T>
using Mili = Join<Power<Factor10, -3>, T>;

template <typename T>
using Micro = Join<Power<Factor10, -6>, T>;

template <typename T>
using Nano = Join<Power<Factor10, -9>, T>;

template <typename T>
using Pico = Join<Power<Factor10, -12>, T>;

template <typename T>
using Femto = Join<Power<Factor10, -15>, T>;

template <typename T>
using Atto = Join<Power<Factor10, -18>, T>;

template <typename T>
using Zepto = Join<Power<Factor10, -21>, T>;

template <typename T>
using Yocto = Join<Power<Factor10, -24>, T>;

/** }@ */

// ----------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------

#endif // FACTORS_H
