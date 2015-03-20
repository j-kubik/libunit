#ifndef UNITS_H
#define UNITS_H

#include <type_traits>

/**
 * @file unitof.h
 */

namespace LibUnit{

/** @cond DOXYGEN_EXCLUDE */
template <typename Unit, typename T>
class Quantity;

template <typename T, int pow = 1>
class Power;

template <typename ...Args>
class Compound;

/** @endcond */

//------------------------------------------------------------------------------------------------------------------

namespace Helper{

/** @cond DOXYGEN_EXCLUDE */

template <typename T>
class TypeCount;

template <typename T, int i>
class TypeAt;

template <typename T, int pow=1, int i=TypeCount<T>::value-1>
class Raise;

template <typename T>
class PowerOf;

template <typename T>
class BasicOf;

template <typename T, typename U, int i=TypeCount<T>::value-1>
class HasPower;

template <typename T, typename U>
class IsEqual;

template <typename T, typename U>
class Join;

template <typename T, int i, int j=TypeCount<T>::value-1>
class TakeAt;

template <typename T, typename U, int i, int j=TypeCount<T>::value-1>
class ReplaceAt;

template <typename T, int i=TypeCount<T>::value-1>
class InvertPowers;

template <typename T, int i=TypeCount<T>::value-1>
class Flatten;

template <typename T, int i=TypeCount<T>::value-1>
class Simplify;

template <typename T>
class UnitOf;

template <typename T, int i=TypeCount<T>::value-1>
class DimensionOf;

template <typename T, int i=TypeCount<T>::value-1>
class FactorOf;

/** @endcond */

//------------------------------------------------------------------------------------------------------------------

/** @cond INTERNAL */

/**
 * @brief Helper class used for counting members of Compound;
 */
template <typename T>
class TypeCount{
public:
    static const int value = 1; //!< One for non-Compound types.
};

/**
 * @brief Helper class used for counting members of Compound;
 */
template <typename ...Args>
class TypeCount<Compound<Args...>>{
public:
    static const int value = sizeof...(Args); //!< Number of Compound types.
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used for extracting i-th type from Compound;
 */
template <typename T, int i>
class TypeAt{
public:
    typedef T Type; //!< For non-Compound type, it's always template type;
};

/**
 * @brief Helper class used for extracting i-th type from Compound;
 */
template <typename T, typename ...Args>
class TypeAt<Compound<T, Args...>, 0>{
public:
    typedef T Type;    //!< I-th type of the Compound.
};

/**
 * @brief Helper class used for extracting i-th type from Compound;
 *
 * Specialization added for error control purpose.
 */
template <>
class TypeAt<Compound<>, 0>{};

/**
 * @brief Helper class used for extracting i-th type from Compound;
 *
 * Specialization added for error control purpose.
 */
template <int i>
class TypeAt<Compound<>, i>{};

/**
 * @brief Helper class used for extracting i-th type from Compound;
 */
template <int i, typename T, typename ...Args>
class TypeAt<Compound<T, Args...>, i>{
public:
    typedef typename TypeAt<Compound<Args...>, i-1>::Type Type;
    //!< Defined as i-1-th element of shorter Compound.
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization that uses recursion to check all members of a Compound type.
 */
template <typename ...Args, int pow, int i>
class Raise<Compound<Args...>, pow, i>{
public:
    typedef typename Raise<Compound<Args...>, pow, i-1>::Type Basic;
    typedef typename Raise<typename TypeAt<Compound<Args...>, i>::Type, pow>::Type iPower;
public:
    typedef typename Join<Basic, iPower>::Type Type;
    //!< For Compound types, just use Raise on every type on it's argument list.
};

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization for recursion termination.
 */
template <typename ...Args, int pow>
class Raise<Compound<Args...>, pow, -1>{
public:
    typedef Compound<> Type;
};

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization for Power class.
 */
template <typename T, int tpow, int pow, int i>
class Raise<Power<T, tpow>, pow, i>{
public:
    typedef typename Raise<T, tpow*pow>::Type Type;
};

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization for power of one.
 * Used to skip Power wrapper class if it's not necesary.
 */
template <typename T, int i>
class Raise<T, 1, i>{
public:
    typedef T Type;
};

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization for power of one and Power class. It is necesary to avoid
 * ambiguity when selcting template specialization. Used to skip Power wrapper
 * class if it's not necesary.
 */
template <typename T, int tpow, int i>
class Raise<Power<T, tpow>, 1, i>{
public:
    typedef typename Raise<T, tpow>::Type Type;
};

/**
 * @brief Helper class used for raising to given power classes representing
 * units and dimensions.
 *
 * Specialization for generic classes.
 */
template <typename T, int pow, int i>
class Raise{
public:
    typedef Power<T, pow> Type;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class returning power of a type.
 *
 * Specialization for simple types.
 */
template <typename T>
class PowerOf{
public:
    static const int value = 1;
};

/**
 * @brief Helper class returning power of a type.
 *
 * Specialization for power types.
 */
template <typename T, int pow>
class PowerOf<Power<T, pow>>{
public:
    static const int value = pow*PowerOf<T>::value;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class extracting basic type from a power of a type.
 * If a simple type is passed as parameter, same type is returned.
 *
 * Specialization for simple types.
 */
template <typename T>
class BasicOf{
public:
    typedef T Type;
};

/**
 * @brief Helper class extracting basic type from a power of a simple type.
 * If a simple type is passed as parameter, same type is returned.
 *
 * Specialization for power types.
 */
template <typename T, int pow>
class BasicOf<Power<T, pow>>{
public:
    typedef typename BasicOf<T>::Type Type;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Recursive specialization for Compound class and singular type.
 */

template <typename ...Args, typename T, int i>
class HasPower<Compound<Args...>, T, i>{
private:
    typedef HasPower<Compound<Args...>, T, i-1> Basic;
    typedef typename TypeAt<Compound<Args...>, i>::Type iType;
public:
    enum:int { value = Basic::value || HasPower<T, iType>::value };
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for recursion termination.
 */
template <typename ...Args, typename T>
class HasPower<Compound<Args...>, T, -1>{
public:
    static const bool value = false;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization overload for Compound class and Power type.
 */
template <typename ...Args, typename T, int pow, int i>
class HasPower<Compound<Args...>, Power<T, pow>, i>{
private:
    typedef HasPower<Compound<Args...>, Power<T, pow>, i-1> Basic;
    typedef typename TypeAt<Compound<Args...>, i>::Type iType;
public:
    static const bool value = Basic::value || HasPower<Power<T, pow>, iType>::value;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for recursion termination.
 */
template <typename ...Args, typename T, int pow>
class HasPower<Compound<Args...>, Power<T, pow>, -1>{
public:
    static const bool value = false;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for comparing power classes.
 */
template <typename T, int tpow, typename U, int upow, int i>
class HasPower<Power<T, tpow>, Power<U, upow>, i>{
public:
    static const bool value = std::is_same<T, U>::value && tpow == upow;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for comparing power class and singular type.
 */
template <typename T, typename U, int upow, int i>
class HasPower<T, Power<U, upow>, i>{
public:
    static const bool value = std::is_same<T, U>::value && upow == 1;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for comparing power class and singular type.
 */
template <typename T, typename U, int tpow, int i>
class HasPower<Power<T, tpow>, U, i>{
public:
    static const bool value = std::is_same<T, U>::value && tpow == 1;
};

/**
 * @brief Helper class used for checking if (first template argument) class
 * representing unit or dimensions contains specific unit or dimension (second
 * class template).
 *
 * First template argument must be simplified. Second template
 * argument can be a singular unit or dimension or a power of it, but never a
 * compound unit or dimension.
 *
 * Specialization for comparing singular types.
 */
template <typename T, typename U, int i>
class HasPower{
public:
    static const bool value = std::is_same<T, U>::value;
};

//------------------------------------------------------------------------------------------------------------------

/** @cond DOXYGEN_EXCLUDE */

template <typename T, typename U>
class IsEqualHelper;

/** @endcond */

/**
 * @brief Helper class used for comparing Compound units and dimensions.
 *
 * It uses recursion, and it has additional template parameter used to cutoff
 * template instantiation in case it is already clear that Compound units are
 * different. Input types must be simplified and have the same length.
 */
// Additional bool parameter stops checking if we deteremine that both Compounds
// are not equal.
template <typename T, typename U, int i=TypeCount<T>::value-1, bool differ=false>
class IsEqualCompound;

/**
 * @brief Helper class used for comparing Compound units and dimensions.
 *
 * It uses recursion, and it has additional template parameter used to cutoff
 * template instantiation in case it is already clear that Compound units are
 * different. Input types must be simplified and have the same length.
 *
 * Specialization used as cutoff when Compounds are already known to be
 * different.
 */
template <typename T, typename U, int i>
class IsEqualCompound<T, U, i, true>{
public:
    static const bool value = 0;
};

/**
 * @brief Helper class used for comparing Compound units and dimensions.
 *
 * It uses recursion, and it has additional template parameter used to cutoff
 * template instantiation in case it is already clear that Compound units are
 * different. Input types must be simplified and have the same length.
 *
 * Specialization for recursion stop.
 */
template <typename ...Args1, typename ...Args2>
class IsEqualCompound<Compound<Args1...>, Compound<Args2...>, -1, false>{
public:
    static const bool value = 1;
};

/**
 * @brief Helper class used for comparing Compound units and dimensions.
 *
 * It uses recursion, and it has additional template parameter used to cutoff
 * template instantiation in case it is already clear that Compound units are
 * different. Input types must be simplified and have the same length.
 *
 * Main specialization used for recursive checking.
 */
template <typename ...Args1, typename ...Args2, int i>
class IsEqualCompound<Compound<Args1...>, Compound<Args2...>, i, false>{
private:
    typedef typename TypeAt<Compound<Args1...>, i>::Type iType;
    typedef IsEqualCompound<Compound<Args1...>, Compound<Args2...>, i-1, !HasPower<Compound<Args2...>, iType>::value> Basic;
public:
    static const bool value = Basic::value;
};

/**
 * @brief Helper class used for comparing units and dimensions.
 *
 * It is used to distinguish between simple types and powers of those and
 * Compound types. Input types must be simplified.
 *
 * Simple types and powers of them are equal only if the types are the same.
 * For Compound types IsEqualCompound is used.
 *
 * Specialization for simple types.
 */
template <typename T, typename U>
class IsEqualHelper{
public:
    static const bool value = std::is_same<T, U>::value;
};

/**
 * @brief Helper class used for comparing units and dimensions.
 *
 * It is used to distinguish between simple types and powers of those and
 * Compound types. Input types must be simplified.
 *
 * Simple types and powers of them are equal only if the types are the same.
 * For Compound types IsEqualCompound is used.
 *
 * Specialization for Compound types.
 */
template <typename ...Args1, typename ...Args2>
class IsEqualHelper<Compound<Args1...>, Compound<Args2...>>{
public:
    static const bool value = (TypeCount<Compound<Args1...>>::value == TypeCount<Compound<Args2...>>::value) && IsEqualCompound<Compound<Args1...>, Compound<Args2...>>::value;
};

/**
 * @brief Helper class used for comparing units and dimensions.
 *
 * It is used to initially Flatten and Simplify Compared types, before passing
 * them to IsEqualHelper.
 */
template <typename T, typename U>
class IsEqual{
public:
    static const bool value = IsEqualHelper<typename Simplify<typename Flatten<Compound<T>>::Type>::Type, typename Simplify<typename Flatten<Compound<U>>::Type>::Type>::value;
};

//------------------------------------------------------------------------------------------------------------------


/**
 * @brief Helper class used for joining units and dimensions into compound units
 * and dimensions.
 *
 * Specialization for simple types.
 */
template <typename T, typename U>
class Join{
public:
    typedef Compound<T, U> Type;
};

//template <typename T, int i, typename U>
//class Join<Power<T,i>, U>{
//public:
//    typedef Compound<Power<T,i>, U> Type;
//};

//template <typename T, int i, typename U>
//class Join<U, Power<T,i>>{
//public:
//    typedef Compound<U, Power<T,i>> Type;
//};

//template <typename T, int i, typename U, int j>
//class Join<Power<T,i>, Power<U,j>>{
//public:
//    typedef Compound<Power<T,i>, Power<U, j>> Type;
//};

//template <typename T, int i, typename ...Args>
//class Join<Power<T,i>, Compound<Args...>>{
//public:
//    typedef Compound<Power<T,i>, Args...> Type;
//};

//template <typename T, int i, typename ...Args>
//class Join<Compound<Args...>, Power<T,i>>{
//public:
//    typedef Compound<Args..., Power<T,i>> Type;
//};

/**
 * @brief Helper class used for joining units and dimensions into compound units
 * and dimensions.
 *
 * Specialization for a simple type and a Compound type.
 */
template <typename T, typename ...Args>
class Join<T, Compound<Args...>>{
public:
    typedef Compound<T, Args...> Type;
};

/**
 * @brief Helper class used for joining units and dimensions into compound units
 * and dimensions.
 *
 * Specialization for a simple type and a Compound type.
 */
template <typename T, typename ...Args>
class Join<Compound<Args...>, T>{
public:
    typedef Compound<Args..., T> Type;
};

/**
 * @brief Helper class used for joining units and dimensions into compound units
 * and dimensions.
 *
 * Specialization for Compound types.
 */
template <typename ...Args1, typename ...Args2>
class Join<Compound<Args1...>, Compound<Args2...>>{
public:
    typedef Compound<Args1..., Args2...> Type;
};

//------------------------------------------------------------------------------------------------------------------

// If you take a type from a singular type, there is nothing left ;)
//template <typename T, int i, int j>
//class TakeAt{
//public:
//    typedef Compound<> Type;
//};

//template <typename ...Args, int i, int j>
//class TakeAt<Compound<Args...>, i, j>{
//private:
//    typedef typename TakeAt<Compound<Args...>, i, j-1>::Type Basic;
//public:
//    typedef typename std::conditional<j==i,
//                                      Basic,
//                                      typename Join<Basic, typename TypeAt<Compound<Args...>, j>::Type>::Type
//    >::type Type;
//};

//template <typename ...Args, int i>
//class TakeAt<Compound<Args...>,i, -1>{
//public:
//    typedef Compound<> Type;
//};

//------------------------------------------------------------------------------------------------------------------

// For singular types replaceAt can oly replace entire type...
//template <typename T, typename U, int i, int j>
//class ReplaceAt{
//public:
//    typedef Compound<Power<U>> Type;
//};

//template <typename T, typename U, int k, int i, int j>
//class ReplaceAt<T, Power<U, k>, i, j>{
//public:
//    typedef Compound<Power<U, k>> Type;
//};

//template <typename ...Args, typename T, int i, int j>
//class ReplaceAt<Compound<Args...>, T, i, j>{
//private:
//    typedef typename ReplaceAt<Compound<Args...>, T, i, j-1>::Type Basic;
//public:
//    typedef typename std::conditional<j==i,
//                                      typename Join<Basic,T>::Type,
//                                      typename Join<Basic, typename TypeAt<Compound<Args...>, j>::Type>::Type
//    >::type Type;
//};

//template <typename ...Args, typename T, int i>
//class ReplaceAt<Compound<Args...>, T, i, -1>{
//public:
//    typedef Compound<> Type;
//};

//------------------------------------------------------------------------------------------------------------------

// Flatten Helper class.
//
// This class works on user-supplied compound types without any further checking.
// It is used to transform possibly nested Compound type into flat list without nesting.

/**
 * @brief Helper class used for flattening nested Compound types.
 *
 * Flattened type is guaranteed to be either a simple type, a power of a simple
 * type or a Compound containing simple types and powers of simple types.
 * Flatten converts input types into falttened types by extracting nested
 * Compound types and converting Compound type raised to a power to Compound
 * with all its elements raised to the same power.
 *
 * Specialization for Compound types.
 */
template <typename ...Args, int i>
class Flatten<Compound<Args...>, i>{
    typedef typename Flatten<Compound<Args...>, i-1>::Type Basic;
public:
    typedef typename Join<Basic, typename Flatten<typename TypeAt<Compound<Args...>, i>::Type>::Type>::Type Type;
    // Appending a compound joins both argument lists, so no matter what comes out At<i>, it will behave well
};

/**
 * @brief Helper class used for flattening nested Compound types.
 *
 * Flattened type is guaranteed to be either a simple type, a power of a simple
 * type or a Compound containing simple types and powers of simple types.
 * Flatten converts input types into falttened types by extracting nested
 * Compound types and converting Compound type raised to a power to Compound
 * with all its elements raised to the same power.
 *
 * Specialization used as recursion end condition.
 */
template <typename ...Args>
class Flatten<Compound<Args...>, -1>{
public:
    typedef Compound<> Type;
};

/**
 * @brief Helper class used for flattening nested Compound types.
 *
 * Flattened type is guaranteed to be either a simple type, a power of a simple
 * type or a Compound containing simple types and powers of simple types.
 * Flatten converts input types into falttened types by extracting nested
 * Compound types and converting Compound type raised to a power to Compound
 * with all its elements raised to the same power.
 *
 * Specialization for Power type.
 */
template <typename T, int pow, int i>
class Flatten<Power<T, pow>, i>{
public:
    typedef typename Raise<T, pow>::Type Type;
};

/**
 * @brief Helper class used for flattening nested Compound types.
 *
 * Flattened type is guaranteed to be either a simple type, a power of a simple
 * type or a Compound containing simple types and powers of simple types.
 * Flatten converts input types into falttened types by extracting nested
 * Compound types and converting Compound type raised to a power to Compound
 * with all its elements raised to the same power.
 *
 * Specialization for Power of one type.
 */
template <typename T, int i>
class Flatten<Power<T, 1>, i>{
public:
    typedef typename Flatten<T>::Type Type;
};

/**
 * @brief Helper class used for flattening nested Compound types.
 *
 * Flattened type is guaranteed to be either a simple type, a power of a simple
 * type or a Compound containing simple types and powers of simple types.
 * Flatten converts input types into falttened types by extracting nested
 * Compound types and converting Compound type raised to a power to Compound
 * with all its elements raised to the same power.
 *
 * Specialization for simple types.
 */
template <typename T, int i>
class Flatten{
public:
    typedef T Type;
};

//------------------------------------------------------------------------------------------------------------------

// SimplifyJoin is a helper class that is used by Simplify. It is inserting type T into U if U already contains
// any power of T::basic. If resulting power of T::basic equals 0, resulting list has no entry for this type.
//
// If U doesnt contain a power of T::basic, entry is not created, and joined equals zero. Otherwise joined equals one.
// Parameters:
//  - U: Already simplified Compound class, that type T will be integrated into.
//  - T: Power class, that should be integrated into U list.
//  - i: helper parameter, it's default value should be preserved.
//
// Members:
//  - joined: enum flag indicating if T was indeed integrated into resulting list.
//  - Type:   Compound class representing resulting list.

/** @cond DOXYGEN_EXCLUDE */
template <typename U, typename T, int i = TypeCount<U>::value-1>
class SimplifyJoin;
/** @endcond */


/**
 * @brief Helper class used for joining a type into a Compound type by adjusting
 * a power of preexisting power of same simple type and removing such entry
 * completely if final power equals `0`. If no preexisting power of given simple
 * type exists in given Compound, the `Type` typedef equals to input Compound
 * and `joined` member is set to `false`. Otherwise `joined` member is set to
 * `true`. Input Compound must be already simplified, and type to be joined
 * must be a power of a simple type.
 *
 * Template parameters:
 *  - `U`: Already simplified Compound class, that type T will be integrated
 * into.
 *  - `T`: Power class, that should be integrated into U list.
 *  - `i`: helper parameter, it's default value should be preserved.
 *
 * Specialization for recursive joining.
 */

// SimplifyJoin is a helper class that is used by Simplify. It is inserting type T into U if U already contains
// any power of T::basic. If resulting power of T::basic equals 0, resulting list has no entry for this type.
//
// If U doesnt contain a power of T::basic, entry is not created, and joined equals zero. Otherwise joined equals one.

template <typename ...Args, typename T, int i>
class SimplifyJoin<Compound<Args...>, T, i>{
private:
    typedef typename TypeAt<Compound<Args...>, i>::Type I;
    //typedef typename I>>::Type iPower;
    //typedef typename Simplify<Power<T>>::Type tPower;
    typedef SimplifyJoin<Compound<Args...>, T, i-1> Helper;

    // This is here and not direclty public because doxygen was making huge mess
    // out of it.
    typedef typename std::conditional< std::is_same<typename BasicOf<T>::Type, typename BasicOf<I>::Type>::value,
                                       typename std::conditional<PowerOf<T>::value + PowerOf<I>::value,
                                                                 typename Join<typename Helper::Type, Power<typename BasicOf<T>::Type, PowerOf<T>::value + PowerOf<I>::value>>::Type,
                                                                 typename Helper::Type
                                       >::type,
                                       typename Join<typename Helper::Type, I>::Type
        >::type ResultType;
public:

    static const bool joined = Helper::joined || std::is_same<typename BasicOf<T>::Type, typename BasicOf<I>::Type>::value;
    //!< indicates if T was indeed integrated into resulting list.

    typedef ResultType Type;
    //!< compound class representing resulting list
};


/**
 * @brief Helper class used for joining a type into a Compound type by adjusting
 * a power of preexisting power of same simple type and removing such entry
 * completely if final power equals `0`. If no preexisting power of given simple
 * type exists in given Compound, the `Type` typedef equals to input Compound
 * and `joined` member is set to `false`. Otherwise `joined` member is set to
 * `true`. Input Compound must be already simplified, and type to be joined
 * must be a power of a simple type.
 *
 * Template parameters:
 *  - `U`: Already simplified Compound class, that type T will be integrated
 * into.
 *  - `T`: Power class, that should be integrated into U list.
 *
 * Specialization that stops recursion.
 */
template <typename ...Args, typename T>
class SimplifyJoin<Compound<Args...>, T, -1>{
public:
    static const bool joined = 0;

    typedef Compound<> Type;
};

/**
 * @brief Helper class used for simplifying a type.
 *
 * Type that is to be simplified must be flat. Simplified type is a flat type
 * that has at most one power of any singular type. If simplified type has only
 * a power of one singular type, then it should be an instance of a `Power`
 * class, not wrapped in a `Compound`. If in addition power of this singular
 * type equals one, simplified type equals to this simple type, not wrapped in
 * `Power` or `Compound`. Empty-unit (dimensionless) is represented by empty
 * `Compound<>`.
 *
 * Specialization for recursive simplification of Compound types.
 */
template <typename ...Args, int i>
class Simplify<Compound<Args...>, i>{
private:
    typedef typename Simplify<Compound<Args...>, i-1>::Type Basic;
    typedef typename TypeAt<Compound<Args...>, i>::Type I;
    typedef SimplifyJoin<Basic, I> Helper;
public:

    typedef typename std::conditional<Helper::joined || PowerOf<I>::value == 0,
                                      typename Helper::Type,
                                      typename Join<typename Helper::Type, I>::Type
    >::type Type;

};

/**
 * @brief Helper class used for simplifying a type.
 *
 * Type that is to be simplified must be flat. Simplified type is a flat type
 * that has at most one power of any singular type. If simplified type has only
 * a power of one singular type, then it should be an instance of a `Power`
 * class, not wrapped in a `Compound`. If in addition power of this singular
 * type equals one, simplified type equals to this simple type, not wrapped in
 * `Power` or `Compound`. Empty-unit (dimensionless) is represented by empty
 * `Compound<>`.
 *
 * Specialization that stops recursion.
 */
template <typename ...Args>
class Simplify<Compound<Args...>, -1>{
public:
    typedef Compound<> Type;
};

/**
 * @brief Helper class used for simplifying a type.
 *
 * Type that is to be simplified must be flat. Simplified type is a flat type
 * that has at most one power of any singular type. If simplified type has only
 * a power of one singular type, then it should be an instance of a `Power`
 * class, not wrapped in a `Compound`. If in addition power of this singular
 * type equals one, simplified type equals to this simple type, not wrapped in
 * `Power` or `Compound`. Empty-unit (dimensionless) is represented by empty
 * `Compound<>`.
 *
 * Specialization for power type.
 */
template <typename T, int pow, int i>
class Simplify<Power<T, pow>, i>{
public:
    typedef typename Raise<typename Simplify<T>::Type, pow>::Type Type;
};

/**
 * @brief Helper class used for simplifying a type.
 *
 * Type that is to be simplified must be flat. Simplified type is a flat type
 * that has at most one power of any singular type. If simplified type has only
 * a power of one singular type, then it should be an instance of a `Power`
 * class, not wrapped in a `Compound`. If in addition power of this singular
 * type equals one, simplified type equals to this simple type, not wrapped in
 * `Power` or `Compound`. Empty-unit (dimensionless) is represented by empty
 * `Compound<>`.
 *
 * Specialization for power-of-one type.
 */
template <typename T, int i>
class Simplify<Power<T, 1>, i>{
public:
    typedef typename Simplify<T>::Type Type;
};

/**
 * @brief Helper class used for simplifying a type.
 *
 * Type that is to be simplified must be flat. Simplified type is a flat type
 * that has at most one power of any singular type. If simplified type has only
 * a power of one singular type, then it should be an instance of a `Power`
 * class, not wrapped in a `Compound`. If in addition power of this singular
 * type equals one, simplified type equals to this simple type, not wrapped in
 * `Power` or `Compound`. Empty-unit (dimensionless) is represented by empty
 * `Compound<>`.
 *
 * Specialization for simple type.
 */
template <typename T, int i>
class Simplify{
public:
    typedef T Type;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used to extract units form variables of qunatity and
 * non-quantity types. It assumes all non-quantity types to be dimensionless.
 *
 * Specialization for non-quantity types.
 */
template <typename T>
class UnitOf{
public:
    typedef Compound<> Type;
};

/**
 * @brief Helper class used to extract units form variables of qunatity and
 * non-quantity types. It assumes all non-quantity types to be dimensionless.
 *
 * Specialization for quantity types.
 */
template <typename Unit, typename T>
class UnitOf<Quantity<Unit, T>>{
public:
    typedef Unit Type;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used to extract dimension form a type representing a
 * compound unit.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `Dimension` subtype.
 *
 * Recursive Specialization for Compound units.
 */
template <typename ...Args, int i>
class DimensionOf<Compound<Args...>, i>{
private:
    typedef typename DimensionOf<Compound<Args...>, i-1>::Type basic;
    typedef typename DimensionOf<typename TypeAt<Compound<Args...>, i>::Type>::Type iDimension;
public:
    typedef typename Join<basic, iDimension>::Type Type;
    //!< Dimension of unit `T`;
};

/**
 * @brief Helper class used to extract dimension form a type representing a
 * compound unit.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `Dimension` subtype.
 *
 * Specialization that ends recursion.
 */
template <typename ...Args>
class DimensionOf<Compound<Args...>, -1>{
public:
    typedef Compound<> Type;
};

/**
 * @brief Helper class used to extract dimension form a type representing a
 * compound unit.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `Dimension` subtype.
 *
 * Specialization for power types.
 */
template <typename T, int pow, int i>
class DimensionOf<Power<T, pow>, i>{
public:
    typedef Power<typename DimensionOf<T>::Type, pow> Type;
};

/**
 * @brief Helper class used to extract dimension form a type representing a
 * compound unit.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `Dimension` subtype.
 *
 * Specialization for simple types.
 */
template <typename T, int i>
class DimensionOf{
public:
    typedef typename T::Dimension Type;
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Helper class used to compute ratio of values of two classes.
 * Result type is exatly the same as using basic variables if no data loss
 * occurs, or double if data loss occurs (ie. dividing two integrals.)
 *
 * If dividing integrals, where result is also an integral, result type is also
 * integral.
 *
 * Specialization for non-integral result types.
 */
template <typename T, typename U, bool integrals = std::is_integral<decltype(T::value)>::value && std::is_integral<decltype(U::value)>::value>
class RatioFactor{
public:
    static constexpr auto value = T::value/U::value;

    static constexpr inline auto getValue(){
        return value;
    }
};

/**
 * @brief Helper class used to compute ratio of values of two classes.
 * Result type is exatly the same as using basic variables if no data loss
 * occurs, or double if data loss occurs (ie. dividing two integrals.)
 *
 * If dividing integrals, where result is also an integral, result type is also
 * integral.
 *
 * Specialization for integral result types.
 */
template <typename T, typename U>
class RatioFactor<T,U,  true>{
private:
    //typedef typename std::conditional<T::value%U::value, double, decltype(T::value/U::value)>::type type;
    typedef typename std::conditional<T::value%U::value, double, decltype(U::value)>::type utype;
public:
    static constexpr auto value = T::value/utype(U::value);

    static constexpr inline auto getValue(){
        return value;
    }

};

/**
 * @brief Helper class used to invert ratio of a value of a class. Result type
 * is integral if value is `1` or `-1`, otherwise it's double;
 *
 * Specialization for non-integral result types.
 */
template <typename T, bool integral = std::is_integral<decltype(T::value)>::value>
class InvertFactor{
public:
    static constexpr auto value = 1/T::value;
};

/**
 * @brief Helper class used to invert ratio of a value of a class. Result type
 * is integral if value is `1` or `-1`, otherwise it's double;
 *
 * Specialization for integral result types.
 */
template <typename T>
class InvertFactor<T, true>{
private:
    typedef typename std::conditional<T::value == 1 || T::value == -1, decltype(T::value), double>::type ttype;
public:
    static constexpr auto value = 1/ttype(T::value);
};


/**
 * @brief Helper function that raises a value to given integer power.
 * @return `value` to the power `pow`
 *
 * It is used in factor calculation of powers of units.
 */
template <typename T, int pow, bool powlz=(pow<0)>
class RaiseToPower{
private:
    typedef RaiseToPower<T, pow-1> prevPow;
public:
    static constexpr auto value = prevPow::value * T::value;
};

template <typename T>
class RaiseToPower<T, 1, false>{
public:
    static constexpr auto value = T::value;
};

template <typename T>
class RaiseToPower<T, 0, false>{
public:
    static constexpr int value = 1;
};

template <typename T, int pow>
class RaiseToPower<T, pow, true>{
private:
    typedef RaiseToPower<T, -pow> prevPow;
public:
    static constexpr auto value = InvertFactor<prevPow>::value;
};


//template <typename T, int pow, bool powlz=(pow<0)>
//inline constexpr double power(T value){

//    return (pow?(power(value,pow-1)*value):1);
//}

//template <typename T>
//inline constexpr int power<T, 0, false>(T value){
//    return 1;
//}

//template <typename T, int pow>
//inline constexpr double power<T, pow, true>(T value){
//    return 1/power<-pow>(value);
//}


/**
 * @brief Helper class used to compute factor used to convert units.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `factor` static constant. Result is a multiplication of factors of all
 * simple units raised to powers in which those simple units appear in a unit
 * for which calculation is performed.
 *
 * Recursive specialization for Compound types.
 */
template <typename ...Args, int i>
class FactorOf<Compound<Args...>, i>{
private:
    typedef FactorOf<Compound<Args...>, i-1> basic;
    typedef FactorOf<typename TypeAt<Compound<Args...>, i>::Type> iFactor;
public:
    static constexpr auto value = basic::value*iFactor::value;
};

/**
 * @brief Helper class used to compute factor used to convert units.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `factor` static constant. Result is a multiplication of factors of all
 * simple units raised to powers in which those simple units appear in a unit
 * for which calculation is performed.
 *
 * Specialization that ends recursion.
 */
template <typename ...Args>
class FactorOf<Compound<Args...>, -1>{
public:
    static constexpr int value = 1;
};

/**
 * @brief Helper class used to compute factor used to convert units.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `factor` static constant. Result is a multiplication of factors of all
 * simple units raised to powers in which those simple units appear in a unit
 * for which calculation is performed.
 *
 * Specialization for power types.
 */
template <typename T, int pow, int i>
class FactorOf<Power<T, pow>, i>{
private:
    typedef FactorOf<T> basic;
public:
    static constexpr auto value = RaiseToPower<basic, pow>::value;
};

/**
 * @brief Helper class used to compute factor used to convert units.
 *
 * Input type must be a proper unit ie. all simple units used must define
 * `factor` static constant. Result is a multiplication of factors of all
 * simple units raised to powers in which those simple units appear in a unit
 * for which calculation is performed.
 *
 * Specialization for simple types.
 */
template <typename T, int i>
class FactorOf{
public:
   static constexpr auto value = T::factor;
};

//------------------------------------------------------------------------------------------------------------------

/** @endcond */
}

/**
 * @brief Class representing a power of a unit or a dimension.
 */
template <typename T, int pow>
class Power{
public:
    static const int power = Helper::PowerOf<Power<T,pow>>::value;
    //!< power to which `T` is raised to.
    typedef typename Helper::BasicOf<T>::Type basic;
    //!< Type raised to power.
};

//------------------------------------------------------------------------------------------------------------------

/**
 * @brief Class representing Compound unit or dimension.
 *
 * Compound types are types consisting of more than one simple type. Compound
 * class contains a list of types as template arguments. This list represents
 * list of units or dimensions.
 *
 * Note that a type is a compound type if it contains more than one simple type;
 * ie.
 *
 * ~~~~~~~~~~~~~{.cpp}
 * // T and U are simple types
 * Power<T, 2> // Not a compound type
 * Compound<Power<T,2>, U> // A compound type
 * Power<Compound<T,U>,3> // A compound type
 * Power<Compound<T>, 2> // Not a compound type
 * Power<Power<Compound<Power<T,2>>,2,3> // Not a compound type
 * Power<Power<Compound<Power<T,2>, U>,2,3> // A compound type
 * ~~~~~~~~~~~~~
 *
 * Distinction between capital-C Compound type (type based on Compound class
 * template), and compound type (type that contains more than one simple type)
 * is important in this documentation.
 */
template <typename ...Args>
class Compound{
public:
};

// ToDo: add some examples of how those work. It might be unclear from my
//       clinical description.

/**
 * @brief Template used in order to join two types int one compound type.
 *
 * Compound types passed are concatenated, not enclosed in outer Compound type.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * Join<Compound<A,B>, Compound<C, D>>; // is Compound<A,B,C,D>
 * Join<Compound<A,B>, Compound<>>; // is Compound<A,B>
 * Join<Compound<A,B>, C>; // is Compound<A,B,C>
 * Join<A, Compound<B, C>>; // is Compound<A,B,C>
 * Join<A, B>; // Is Compound<A, B>
 * ~~~~~~~~~~~~~~~~~~~~
 */

template <typename T, typename U>
using Join = typename Helper::Join<T, U>::Type;

/**
 * @brief Template used in order to flatten a type.
 *
 * Flattened compound type is a Compound type containing only non-compound
 * types. Flattened non-compound type is also a non-Compound type.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * Flatten<Compound<Compound<A,B>, Compound<C, D>>>; // is Compound<A,B,C,D>
 * Flatten<Compound<Compound<A,B>, Compound<B, A>>>; // is Compound<A,B,B,A>
 * Flatten<Compound<Compound<A,B>, Compound<>>>; // is Compound<A,B>
 * Flatten<Compound<Compound<A,B>, C>>; // is Compound<A,B,C>
 * Flatten<Compound<A, Power<Compound<B, C>,2>>; // is Compound<A,Power<B,2>,Power<C,2>>
 * Flatten<Compound<A, Power<Compound<B, Power<C,3>>,2>>; // is Compound<A,Power<B,2>,Power<C,6>>
 * Flatten<Compound<A, Power<Compound<B, Power<C,-1>>,2>>; // is Compound<A,Power<B,2>,C>
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using Flatten = typename Helper::Flatten<T>::Type;

/**
 * @brief Template used in order to simplify a type.
 *
 * Simplified type is a flattened type, that contains any simple type at mose
 * once. This means that all entries in an inputcompound type are converted into
 * a single entry in a output entry, raised to apropriate power.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * Simplify<Compound<A,B,A>>; //is Compound<Power<A,2>, B>
 * Simplify<Compound<Power<A,2>, B, A>>; // is Compound<Power<A,3>, B>
 * Simplify<Compound<Power<A,2>, Compound<B, A>>>; // is Compound<Power<A,3>, B>
 * Simplify<Power<Compound<Power<A,2>, Compound<B, A>>, 3>>; // is Compound<Power<A,9>, Power<B,3>>
 * Simplify<Compound<A>>; // is A
 * Simplify<Compound<Power<A, 5>>>; // is Power<A,5>
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using Simplify = typename Helper::Simplify<Flatten<T>>::Type;

/**
 * @brief Template used in order to invert a type.
 *
 * Tyype inversion means raising it to power of -1.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * Invert<Compound<A, Power<B,2>, Power<C, -3>>>; // is Compound<Power<A, -1>, Power<B, -2>, Power<C, -3>>
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using Invert = typename Helper::Raise<T, -1>::Type;

/**
 * @brief Template used check a unit of a variable.
 *
 * Variables other than Quantity are considered to be unitless.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 *
 * UnitOf<int>;                     // is Compound<>
 * UnitOf<double>;                  // is Compound<>
 * UnitOf<Quantity<Compound<>, double>>; // is Compound<>
 * UnitOf<Quantity<A, double>>; // is A
 * UnitOf<Quantity<Power<A,7>, double>>; // is Power<A,7>
 * UnitOf<Quantity<Compound<A, B>, double>>; // is Compound<A,B>
 * UnitOf<Quantity<Compound<Power<A, 2>, Power<B,-3>>>>; // is Compound<Power<A, 2>, Power<B,-3>>
 *
 * int i;
 * double j;
 * Quantity<Compound<>, double> k;
 * Quantity<A, double> l;
 * UnitOf<Quantity<Power<A,7>, double>> m;
 * Quantity<Compound<A, B>, double> n;
 * Quantity<Compound<Power<A, 2>, Power<B,-3>>> o;
 *
 * UnitOf<decltype(i)>; // is Compound<>
 * UnitOf<decltype(j)>; // is Compound<>
 * UnitOf<decltype(k)>; // is Compound<>
 * UnitOf<decltype(l)>; // is A
 * UnitOf<decltype(m)>; // is Power<A,7>
 * UnitOf<decltype(n)>; // is Compound<A,B>
 * UnitOf<decltype(o)>; // is Compound<Power<A, 2>, Power<B,-3>>
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using UnitOf = typename Helper::UnitOf<T>::Type;

/**
 * @brief Template used compute dimension of a unit.
 *
 * Variables other than Quantity are considered to be unitless.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * class Dim;
 * class Un1{
 *     public:
 *     typedef Dim Dimension;
 * };
 *
 * UnitOf<Un1>; // is Dim;
 * UnitOf<Compound<Un1>>; // is Compound<Dim>
 * UnitOf<Power<Un1, 3>>; // is Power<Dim, 3>
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using DimensionOf = typename Helper::DimensionOf<T>::Type;

/**
 * @brief Template used compute factor of a unit.
 *
 * Factor of a unit is used to convert variables between units of the same
 * dimension. Value of a quantity in unit `Un1` after conversion to value in
 * unit `Un2` equals value multiplied by ration of the factor of unit `Un1` to
 * the factor of unit `Un2`.
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * class Dim1;
 * class Dim2;
 *
 * class Un1{
 *     public:
 *     static const double factor = 3.12;
 *     typedef Dim1 Dimension;
 * };
 *
 * class Un2{
 *     public:
 *     static const double factor = 7.43;
 *     typedef Dim1 Dimension;
 * };
 *
 * class Un3{
 *     public:
 *     static const double factor = 5.55;
 *     typedef Dim2 Dimension;
 * };
 *
 * Quantity<Un1> i(17);
 * Quantity<Un2> j;
 * Quantity<Un3> k;
 * j = i; // j equals i.value()*FactorOf<Un1>/FactorOf<Un2>
 *        // j equals 17*(3.12/7.43);
 * k = i; // compiler error
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T>
using FactorOf = Helper::FactorOf<T>;

                                                   /**
                                                    *
                                                    */
template <typename T, typename U>
using RatioFactor = Helper::RatioFactor<T,U>;

template <typename T, typename U>
using RatioFactorOf = Helper::RatioFactor<FactorOf<T>,FactorOf<U>>;

/**
 * @brief Template used comapre units and dimensions.
 *
 * Units and dimensions are considered equal if after simplification have the
 * same
 *
 * ####Examples####
 * ~~~~~~~~~~~~~~~~~~~~{.cpp}
 * class Dim1;
 * class Dim2;
 *
 * class Un1{
 *     public:
 *     static const double factor = 3.12;
 *     typedef Dim1 Dimension;
 * };
 *
 * class Un2{
 *     public:
 *     static const double factor = 7.43;
 *     typedef Dim1 Dimension;
 * };
 *
 * class Un3{
 *     public:
 *     static const double factor = 5.55;
 *     typedef Dim2 Dimension;
 * };
 *
 * IsEqual<Un1, Un1>::value; // true
 * IsEqual<Un2, Un1>::value; // false
 * IsEqual<Un1, Un3>::value; // false
 * IsEqual<Power<Power<Un1, 3>, 2>,Compound<Power<Un1, 6>>>::value; // true
 * IsEqual<Power<Un1, 6>,Compound<Power<Un1, 6>>>::value; // true
 * IsEqual<Power<Power<Un1, 3>, 2>,Power<Compound<Un1>, 6>>::value; // true
 * IsEqual<Power<Power<Un1, 3>, 2>,Compound<Power<Un1, 7>>>::value; // false
 * IsEqual<Power<Power<Un1, 3>, 2>,Power<Compound<Un1>, 7>>::value; // false
 * IsEqual<Power<Power<Un1, 3>, 2>,Compound<Power<Un1, 6>, Power<Un2,4>>>::value; // false
 * IsEqual<Power<Power<Un1, 3>, 2>,Power<Compound<Un2>, 6>>::value; // false
 * IsEqual<Compound<Power<Un1, 3>>,Power<Un1, 3>>::value; // true

 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Un2, Un3>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Un2>>::value; // false
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Un2, Power<Un3,2>>>::value; // false
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Un2, Un3, Time>>::value; // false
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Un3, Un2>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Un2, Power<Un1, 3>, Un3>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Power<Compound<Power<Un1, 3>, Un2, Un3>>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 3>, Power<Un2>, Power<Un3>>>::value; // true

 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Power<Un1, 2>, Un3, Un1, Un2>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Compound<Un2, Un1, Un1, Un3, Un1>>::value; // true
 * IsEqual<Compound<Power<Un1, 3>, Un2, Un3>,Power<Compound<Power<Un1, 3>, Power<Un2,2>, Un3, Power<Un2, -1>>>>::value; // true

 * IsEqual<DimensionOf<Compound<Power<Un1, 3>, Un3>>,DimensionOf<Compound<Power<Un2, 2>, Un1, Un3>>>::value; // true
 * IsEqual<DimensionOf<Compound<Power<Un1, 3>, Un3>>,DimensionOf<Compound<Power<Un2, 2>, Un3, Un3>>>::value; // false
 * IsEqual<DimensionOf<Compound<Power<Un1, 3>, Un3>>,Compound<Power<Dim1, 3>, Dim2>>::value; // true
 * ~~~~~~~~~~~~~~~~~~~~
 */
template <typename T, typename U>
using IsEqual = Helper::IsEqual<T, U>;

//------------------------------------------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------------------------------------




#endif // UNITS_H
