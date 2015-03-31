#ifndef QUANTITY_H
#define QUANTITY_H

#include "unitmanip.h"
#include <utility>
#include <iosfwd>

//#include <iostream>
#include <typeinfo>

/**
 * @file quantity.h
 */

namespace LibUnit{

/** @cond DOXYGEN_EXCLUDE */
template <typename Unit, typename T = double>
class Quantity;
/** @endcond */

template <typename Unit, typename T>
inline std::ostream& operator<<(std::ostream& s, const Quantity<Unit,T>& q);

template <typename Unit, typename T>
inline std::istream& operator>>(std::istream& s, const Quantity<Unit,T>& q);

template <typename T>
inline auto value(const T& t);

/**
 * @brief Quantity class represents a variable of type T coupled with a unit.
 *
 * Template parameters:
 *  - Unit: type describing unit in which quantity is expressed.
 *  - T:    Underlying type that is used to store the value.
 *
 * Quantity is one of core classes of LibUnit. It contains a value of underlying type. It's template parameter
 * describes unit in which stored value is expressed.
 *
 * All mathematical operator avialable in C/C++ are overloaded in such a way that the results obey regular unit
 * arithmetics. If requested operation cannot be performed, compilation error is generated.
 *
 * All methods of this class are declared inline and (hopefully) a good compiler should be able to generate
 * identical code as when working directly on a variable of nderlying type.
 *
 * ###Standard conversions###
 * Whenever required, while performig arythmetics on quantities of different unit in LibUnit, one of the quantities
 * must be converted to the same unit as the other. Unit conversion is only possible if dimensions of both units
 * are the same.
 *
 * In order to compute value of quantity in unit `V`, representing the quantity in unit `U`, the ratio of
 * factor of unit `U` to the factor of unit `V` is computed. Then value of quantity in unit `U` is then multiplied
 * by this ratio, yieldig value of quantity in unit `V`.
 *
 * If underlying type of assigned quantities are different, standard type coercion is performed. If a result of a
 * computation is a quantity computed from a set of quantities, then underlying type of such quantity is the same
 * as a type of a result of equivalent computation performed directly upon variables of underlying types _including
 * unit conversion_.
 *
 * Attempting to use units with different dimensions in above circumstances will cause compilation error.
 * This allows for compile-time unit checking, and is one of the main motivation for LibUnit.
 *
 *
 */
template <typename Unit, typename T>
class Quantity{
private:
    T t;

    template <typename U>
    inline void checkComaptible() const{
        static_assert(IsEqual<DimensionOf<U>, DimensionOf<Unit>>::value, "Quantities of unequal dimensions!!!");
    }

    template <typename U>
    inline void checkNoUnit() const{
        static_assert(IsEqual<DimensionOf<U>, Compound<>>::value, "Dimensionless quantity required!!!");
    }

    template <typename T2>
    static inline auto value(const T2& t){
        return t;
    }

    template <typename U, typename T2>
    inline auto value(const Quantity<U, T2>& q){
        return q.value();
    }

public:
    /**
     * @brief Contructs Quantity with non-initialized value.
     */
    inline Quantity(){}

    /**
     * @brief Contructs a Quantity from quantity of the same unit but different underlying type.
     *
     * Standard (implicit) conversion between underlying types is performed.
     */
    template <typename T2>
    inline Quantity(const Quantity<Unit, T2>& q)
        :t(q.value())
    {}

    /**
     * @brief Contructs a quantity from quantity of the same dimension but different underlying type.
     *
     * Standard (implicit) conversion between underlying types is performed. Scaling between different units of the same
     * dimension is performed.
     *
     * If dimension of quantity q is different than dimension of constructed quantity, compilation error is generated.
     */
    template <typename U, typename T2>
    inline Quantity(const Quantity<U, T2>& q)
        :t(Convert<U, Unit>::value(q.value()))
    {
        checkComaptible<U>();
    }


    /**
     * @brief Constructs a quantity with a given value.
     *
     * No conversions are performed on the value.
     */
    inline explicit Quantity(T value)
        :t(value)
    {}

    /**
     * @brief Assigns a quantity from quantity of the same dimension but different underlying type.
     *
     * Standard (implicit) conversion between underlying types is performed. Scaling between different units of the same
     * dimension is performed.
     *
     * If dimension of quantity q is different than dimension of assigned quantity, compilation error is generated.
     */
    template <typename U, typename T2>
    inline Quantity& operator=(const Quantity<U, T2>& q)
    {
        checkComaptible<U>();
        t = Convert<U, Unit>::value(q.value());
        return *this;
    }

    /**
     * @brief Adds a quantity of the same dimension but different underlying type.
     * @return quantity instance of the same unit as leftside quantity.
     *
     * Standard (implicit) conversion between underlying types and scaling between different
     * units of the same dimension is performed before addition.
     *
     * If dimensions of added quantities are different, compilation error is generated.
     */
    template <typename U, typename T2>
    inline auto operator+(const Quantity<U, T2>& q) const
    {
        checkComaptible<U>();
        auto val = t + Convert<U, Unit>::value(q.value());
        return Quantity<Unit, decltype(val)>(val);
    }

    /**
     * @brief Subtracts a quantity of the same dimension but different underlying type.
     * @return quantity instance of the same unit as leftside quantity.
     *
     * Standard (implicit) conversion between underlying types and scaling between different
     * units of the same dimension is performed before addition.
     *
     * If dimensions of subtracted quantities are different, compilation error is generated.
     */
    template <typename U, typename T2>
    inline auto operator-(const Quantity<U, T2>& q) const
    {
        checkComaptible<U>();
        auto val = t - Convert<U, Unit>::value(q.value());
        return Quantity<Unit, decltype(val)>(val);
    }

    // Does nothing.
    /**
     * @brief Integer promotion operator.
     * @return quantity of the same unit and underlying type same as integer promotion of
     *         underlying type of promoted quantity.
     *
     * Performs integer promotion on held value and returns qunatity of the same unit and
     * apropriate underlying type.
     */
    inline auto operator+() const
    {
        auto val = +t;
        return Quantity<Unit, decltype(val)>(val);
    }

    /**
     * @brief Additive inverse operator.
     * @return quantity of the same unit and underlying type same as additive inverse of
     *         underlying type of inversed quantity.
     *
     * Performs additive inversion on held value and returns qunatity of the same unit and
     * apropriate underlying type.
     */
    inline Quantity operator-() const
    {
        auto val = -t;
        return Quantity<Unit, decltype(val)>(val);
    }

    /**
     * @brief Division rest operator.
     * @return quantity instance of the same unit as leftside quantity.
     *
     * Standard (implicit) conversion between underlying types and scaling between different
     * units of the same dimension is performed before division.
     *
     * If dimensions of divided quantities are different, compilation error is generated.
     */
    template <typename U, typename T2>
    inline auto operator%(const Quantity<U, T2>& q) const
    {
        checkComaptible<U>();
        auto val = t % Convert<U, Unit>::value(q.value());
        return Quantity<Unit, decltype(val)>(val);
    }

    /**
     * @brief Division rest operator.
     * @return quantity instance of the same unit as leftside quantity.
     *
     * Overload for non-quantity values. Since non-quantity values have no unit attached, no
     * conversions is being performed.
     */
    template <typename U>
    inline auto operator%(const U& u) const
    {
        auto val = t%u;
        return Quantity<Unit, decltype(val)>(val);
    }

    /**
     * @brief Increment operator.
     * @return reference to this quantity.
     *
     * Increments stored value.
     */
    inline Quantity& operator++(){
        ++t;
        return *this;
    }

    /**
     * @brief Increment operator.
     * @return copy of the quantity before incremntation.
     *
     * Increments stored value.
     */
    inline Quantity operator++(int){
        T val = t;
        t++;
        return Quantity(val);
    }

    /**
     * @brief Decrement operator.
     * @return reference to this quantity.
     *
     * Decrements stored value.
     */
    inline Quantity& operator--(){
        --t;
        return *this;
    }

    /**
     * @brief Decrement operator.
     * @return copy of the quantity before decremntation.
     *
     * Decrements stored value.
     */
    inline Quantity operator--(int){
        T val = t;
        t--;
        return Quantity(val);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /**
     * @name Comparison operators.
     *
     * Perform comparison between quantities of the same dimension and possibly
     * different underlying types.
     *
     * Standard (implicit) conversion between underlying types and scaling
     * between different units of the same dimension is performed before
     * comparisons.
     *
     * If dimensions of compared quantities are different, compilation error is
     * generated.
     */
    //@{
    template <typename U, typename T2>
    inline bool operator==(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t == Convert<U, Unit>::value(q.value());
    }

    template <typename U, typename T2>
    inline bool operator!=(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t != Convert<U, Unit>::value(q.value());
    }

    template <typename U, typename T2>
    inline bool operator>(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t > Convert<U, Unit>::value(q.value());
    }

    template <typename U, typename T2>
    inline bool operator<(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t < Convert<U, Unit>::value(q.value());
    }

    template <typename U, typename T2>
    inline bool operator>=(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t >= Convert<U, Unit>::value(q.value());
    }

    template <typename U, typename T2>
    inline bool operator<=(const Quantity<U, T2>& q) const{
        checkComaptible<U>();
        return t <= Convert<U, Unit>::value(q.value());
    }

    //@}

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    // Logical and bit-wise operators are rather useless here.

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /**
     * @brief Addition assignment operator.
     *
     * Performs addition assignment between quantities of the same dimension and different underlying type.
     *
     * Standard (implicit) conversion of underlying type and scaling is performed before addition if second
     * opearand has different unit.
     *
     * If dimensions of operands are different, compilation error is generated.
     */

    template <typename U, typename T2>
    Quantity& operator+=(const Quantity<U, T2>& q){
        checkComaptible<U>();
        t += Convert<U, Unit>::value(q.value());
        return *this;
    }

    /**
     * @brief Subtraction assignment operator.
     *
     * Performs subtraction assignment between quantities of the same dimension and different underlying type.
     *
     * Standard (implicit) conversion of underlying type and scaling is performed before subtraction if second
     * opearand has different unit.
     *
     * If second operand is not dimensionless, compilation error is generated.
     */
    template <typename U, typename T2>
    Quantity& operator-=(const Quantity<U, T2>& q){
        checkComaptible<U>();
        t -= Convert<U, Unit>::value(q.value());
        return *this;
    }



    /**
     * @brief Multiplication assignment operator.
     *
     * Performs multiplication assignment between quantity and non-quantity or
     * dimensionless quantity.
     *
     * Non-quantity operand has no unit, so no scaling is performed.
     *
     * If second operand is not dimensionless, compilation error is generated.
     */
    template <typename T2>
    Quantity& operator*=(const T2& q){
        checkNoUnit<UnitOf<T2>>();
        t *= value(q);
        return *this;
    }

    /**
     * @brief Division assignment operator.
     *
     * Performs division assignment between quantity and non-quantity or
     * dimensionless quantity.
     *
     * Non-quantity operand has no unit, so no scaling is performed.
     *
     * If second operand is not dimensionless, compilation error is generated.
     */
    template <typename T2>
    Quantity& operator/=(const T2& q){
        checkNoUnit<UnitOf<T2>>();
        t /= value(q);
        return *this;
    }


    /**
     * @brief Division rest assignment operator.
     *
     * Performs division rest assignment between quantity and non-quantity or
     * dimensionless quantity.
     *
     * Non-quantity operand has no unit, so no scaling is performed.
     *
     * If second operand is not dimensionless, compilation error is generated.
     */
    template <typename T2>
    Quantity& operator%=(const T2& q){
        checkNoUnit<UnitOf<T2>>();
        t %= value(q);
        return *this;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /**
     * @name Additional operators.
     *
     * Provided for ease of use for different underlying types. These operators
     * perform same operations as used on underlying types of operands. No
     * conversions or compiler errors are genereated by LibUnit.
     */
    //@{
    template <typename U>
    inline auto operator[](const U& u){
        return t[u];
    }

    template <typename U>
    inline auto operator[](const U& u) const{
        return t[u];
    }

    inline auto operator*(){
        return *t;
    }

    inline auto operator*() const{
        return *t;
    }

    // ToDo: pointers?
    inline auto operator->(){
        return t.operator->();
    }

    // ToDo: pointers?
    inline auto operator->() const{
        return t.operator->();
    }

    template <typename U>
    inline auto operator->*(const U& u){
        return t->*u;
    }

    template <typename U>
    inline auto operator->*(const U& u) const{
        return t->*u;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    template <typename ...Args>
    inline auto operator()(Args&&... args){
        return t(std::forward<Args>(args)...);
    }

    template <typename ...Args>
    inline auto operator()(Args&&... args) const{
        return t(std::forward<Args>(args)...);
    }

    template <typename ...Args>
    inline auto operator()(const Args&... args){
        return t(args...);
    }

    template <typename ...Args>
    inline auto operator()(const Args&... args) const{
        return t(args...);
    }
    //@}

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /**
     * @brief Conversion to underlying type operator
     * @return internal value of quantity.
     *
     * No conversions or compiler errors are genereated by LibUnit.
     */
    explicit operator T() const{
        return t;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /**
     * @brief Internal value of quantity.
     * @return internal value of quantity.
     *
     * No conversions or compiler errors are genereated by LibUnit.
     */
    inline T value() const{
        return t;
    }

    /**
     * @brief Reference to internal value of quantity.
     * @return reference to internal value of quantity.
     *
     * Can be used to change value of quantity without dimension checking.
     * Use with caution.
     */
    inline T& ref(){
        return t;
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------

    /*/**
     * @brief Static function used to convert values of known units.
     *
     * Converts a value in unit `U` into a value in unit `Unit`.
     */
    /*template <typename U, typename T2>
    static inline constexpr auto convert(T2 t){
        return t * ((decltype(RatioFactorOf<U, Unit>::value)) RatioFactorOf<U, Unit>::value);
    }*/

    friend std::ostream& operator<< <Unit, T>(std::ostream&, const Quantity<Unit, T>&);
    friend std::istream& operator>> <Unit, T>(std::istream&, const Quantity<Unit, T>&);
};

/**
 * @brief Quantity multiplication operator.
 * @return Quantity of correct unit and underlying type same as result of
 * multiplication of underlying types of operands.
 */
template <typename Unit, typename T, typename U, typename T2>
inline auto operator*(const Quantity<Unit, T>& p, const Quantity<U, T2>& q)
{
    auto val = p.value()*q.value();
    return Quantity<Simplify<Join<Unit, U>>, decltype(val)>(val);
}

/**
 * @brief Quantity multiplication operator.
 * @return Quantity of same unit as first operand and underlying type same as
 * result of multiplication of underlying type of first operand and second
 * operand.
 */
template <typename Unit, typename T, typename U>
inline auto operator*(const Quantity<Unit, T>& p, const U& u)
{
    auto val = p.value()*u;
    return Quantity<Unit, decltype(val)>(val);
}

/**
 * @brief Quantity multiplication operator.
 * @return Quantity of same unit as second operand and underlying type same as
 * result of multiplication of underlying type of second operand and first
 * operand.
 */
template <typename U, typename Unit, typename T>
inline auto operator*(const U& u, const Quantity<Unit, T>& p)
{
    auto val = p.value()*u;
    return Quantity<Unit, decltype(val)>(val);
}

/**
 * @brief Quantity division operator.
 * @return Quantity of correct unit and underlying type same as result of
 * division of underlying types of operands.
 */
template <typename Unit, typename T, typename U, typename T2>
inline auto operator/(const Quantity<Unit, T>& p, const Quantity<U, T2>& q)
{
    auto val = p.value()/q.value();
    return Quantity<Simplify<Join<Unit, Invert<U>>>, decltype(val)>(val);
}

/**
 * @brief Quantity division operator.
 * @return Quantity of first operand's inverted unit and underlying type same as
 * result of division of underlying type of first operand and second operand.
 */
template <typename Unit, typename T, typename U>
inline auto operator/(const Quantity<Unit, T>& p, const U& u)
{
    auto val = p.value()/u;
    return Quantity<Unit, decltype(val)>(val);
}

/**
 * @brief Quantity division operator.
 * @return Quantity of second operand's inverted unit and underlying type same
 * as result of division of underlying type of second operand and first operand.
 */
template <typename U, typename Unit, typename T>
inline auto operator/(const U& u, const Quantity<Unit, T>& p)
{
    auto val = u/p.value();
    return Quantity<Invert<Unit>, decltype(val)>(val);
}

/**
 * @brief Ostream output operator overload
 *
 * Outputs internal value of quantity.
 */
template <typename Unit, typename T>
inline std::ostream& operator<<(std::ostream& s, const Quantity<Unit,T>& q){
    s << q.t;
    return s;
}

/**
 * @brief Istream input operator overload
 *
 * Reads internal value of quantity from istream.
 */
template <typename Unit, typename T>
inline std::istream& operator>>(std::istream& s, const Quantity<Unit,T>& q){
    s >> q.t;
    return s;
}

}


#endif // QUANTITY_H
