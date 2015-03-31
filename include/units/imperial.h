#ifndef FPS_H
#define FPS_H

#include "SI.h"

/**
 * @defgroup imperial_units Imperial units
 *
 * Contains Imperial units definitions. Note that depending on where your data
 * come from there might be some (usually small) differences in unit
 * definitions. This is especially important in case of historical data, as
 * many units changed their definition signifcantly overtime. Full treatment of
 * those cases is outside of LibUnit's scope.
 *
 * Geographical differences between units are usually of little significance,
 * but not non-existent. If your calculation is using units that might be
 * incosistent with libUnit's definitions, confirm it by checking factors. In
 * case of significant differences, try to inform author of a unit set, and as a
 * workaround use own unit definition.
 * @{
 */

// ToDo: descriptions of those units should need fixups.
//       outside of SI, who actually "owns" unit names, or even knows what
//       exactly do those mean?
//       I never suspected that units are such a mess. Thank god for SI!!!!

namespace LibUnit{

namespace Imperial{
//----------------------------------------------------------------------------
// Length units

/** @brief Imperial thou unit.*/
class Thou{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.0000254; //!< factor
};

/** @brief Imperial inch unit.*/
class Inch{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.0254; //!< factor
};

/** @brief Imperial foot unit.*/
class Foot{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.3048; //!< factor
};

/** @brief Imperial yard unit.*/
class Yard{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.9144; //!< factor
};

/** @brief Imperial chain unit.*/
class Chain{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 20.1168; //!< factor
};

/** @brief Imperial furlong unit.*/
class Furlong{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 201.168; //!< factor
};

/** @brief Imperial mile unit.*/
class Mile{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 1609.344; //!< factor
};

/** @brief Imperial league unit.*/
class League{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 4828.032; //!< factor
};

/** @brief Imperial fathom unit.*/
class Fathom{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 1.82880; //!< factor
};

/** @brief Imperial cable unit.*/
class Cable{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 185.3184; //!< factor
};

/** @brief Imperial nautical mile unit.*/
class NauticalMile{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 1853.184; //!< factor
};

/** @brief Imperial link unit.*/
class Link{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.201168; //!< factor
};

/** @brief Imperial rod unit.*/
class Rod{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 5.0292; //!< factor
};

/** @brief Imperial chain unit.*/
class Chain{
public:
    typedef Length Dimension; //!< Dimension of this unit
    static constexpr double factor = 20.1168; //!< factor
};

//----------------------------------------------------------------------------
// Derived area units

using Perch = Power<Rod, 2>;
using Rood = Compound<Furlong, Rod>;
using Acre = Compound<Furlong, Chain>;

// Vloume units

/** @brief Imperial fluid ounce (fl oz) unit.*/
class FluidOunce{
public:
    typedef DimensionOf<Litre> Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.0284130625*FactorOf<Litre>::value; //!< factor
};

/** @brief Imperial gill (gi) unit.*/
class Gill{
public:
    typedef DimensionOf<Litre> Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.1420653125*FactorOf<Litre>::value; //!< factor
};

/** @brief Imperial pint (pt) unit.*/
class Pint{
public:
    typedef DimensionOf<Litre> Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.56826125*FactorOf<Litre>::value; //!< factor
};

/** @brief Imperial quart (qt) unit.*/
class Quart{
public:
    typedef DimensionOf<Litre> Dimension; //!< Dimension of this unit
    static constexpr double factor = 1.1365225*FactorOf<Litre>::value; //!< factor
};

/** @brief Imperial gallon (qt) unit.*/
class Gallon{
public:
    typedef DimensionOf<Litre> Dimension; //!< Dimension of this unit
    static constexpr double factor = 4.54609*FactorOf<Litre>::value; //!< factor
};

// ToDo: for now skipping British apothecaries' volume units - who uses those anyway?

//----------------------------------------------------------------------------
// Mass Units

/** @brief Imperial grain unit.*/
class Grain{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 0.06479891; //!< factor
};

/** @brief Imperial drachm unit.*/
class Drachm{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 1.7718451953125; //!< factor
};

/** @brief Imperial ounce unit.*/
class Ounce{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 28.349523125; //!< factor
};

/** @brief Imperial pound unit.*/
class Pound{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 453.59237; //!< factor
};

/** @brief Imperial stone unit.*/
class Stone{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 6350.29318; //!< factor
};

/** @brief Imperial quarter unit.*/
class Quarter{
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 12700.58636; //!< factor
};

/** @brief Imperial imperial hundredweight unit.*/
class ImperialHundredweight {
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 50802.34544; //!< factor
};

/** @brief Imperial hundredweight unit.*/
class ImperialTon {
public:
    typedef Mass Dimension; //!< Dimension of this unit
    static constexpr double factor = 1016046.9088; //!< factor
};

}

}

/** }@ */

#endif // FPS_H
