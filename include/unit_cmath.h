#ifndef UNIT_CMATH_H
#define UNIT_CMATH_H

#include <cmath>
#include "quantity.h"

namespace LibUnit{

template <typename Unit, typename T>
inline auto  modf(Quantity<Unit, T> q, T* intpart){
    return Quantity<Unit, decltype(std::modf(q.t, intpart))>
            (std::modf(q.t, intpart));
}

template <typename Unit, typename T, typename U, typename T2>
inline auto modf(Quantity<Unit, T> q, Quantity<U, T2>* intpart){
    Quantity<Unit, T> intu;
    Quantity<Unit, decltype(std::modf(q.value(), &intu.ref()))> result
            (std::modf(q.value(), &intu.ref()));

    *intpart = intu;
    return result;
}

template <typename Unit, typename T>
inline auto  ceil(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::ceil(q.value()))>
            (std::ceil(q.value()));
}

template <typename Unit, typename T>
inline auto  floor(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::floor(q.value()))>
            (std::floor(q.value()));
}

template <typename Unit, typename T, typename U, typename T2>
inline auto  fmod(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::fmod(q.value(), qp))>
            (std::fmod(q.value(), qp.value()));
}

template <typename Unit, typename T>
inline auto  trunc(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::trunc(q.value()))>
            (std::trunc(q.value()));
}

template <typename Unit, typename T>
inline auto  round(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::round(q.value()))>
            (std::round(q.value()));
}

template <typename Unit, typename T>
inline auto lround(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::lround(q.value()))>
            (std::lround(q.value()));
}

template <typename Unit, typename T>
inline auto llround(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::llround(q.value()))>
            (std::llround(q.value()));
}

template <typename Unit, typename T>
inline auto rint(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::rint(q.value()))>
            (std::rint(q.value()));
}

template <typename Unit, typename T>
inline auto lrint(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::lrint(q.value()))>
            (std::lrint(q.value()));
}

template <typename Unit, typename T>
inline auto llrint(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::llrint(q.value()))>
            (std::llrint(q.value()));
}

template <typename Unit, typename T>
inline auto nearbyint(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::nearbyint(q.value()))>
            (std::nearbyint(q.value()));
}

template <typename Unit, typename T>
inline auto remainder(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::remainder(q.value()))>
            (std::remainder(q.value()));
}

template <typename Unit, typename T, typename U, typename T2>
inline auto remquo(Quantity<Unit, T> q, Quantity<U, T2> p, Quantity<Unit, int>* quot){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::remquo(q.value(), qp, &quot->ref()))>(
            (std::remquo(q.value(), qp, &quot->ref())));
}

// ToDo: does this even make sense?
template <typename Unit, typename T, typename U, typename T2>
inline auto copysign(Quantity<Unit, T> q, Quantity<U, T2> p){
    return Quantity<Unit, decltype(std::copysign(q.value(), p.value()))>
            (std::copysign(q.value(), p.value()));
}

// ToDo: figure out possibilites for different NAN-s for different types.

template <typename Unit, typename T, typename U, typename T2>
inline auto nextafter(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::nextafter(q.value(), qp))>
            (std::nextafter(q.value(), qp));
}

template <typename Unit, typename T, typename U>
inline auto nexttoward(Quantity<Unit, T> q, Quantity<U, long double> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::nexttoward(q.value(), qp))>
            (std::nexttoward(q.value(), qp));
}

template <typename Unit, typename T, typename U>
inline auto fdim(Quantity<Unit, T> q, Quantity<U, long double> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::fdim(q.value(), qp))>
            (std::fdim(q.value(), qp));
}

template <typename Unit, typename T, typename U, typename T2>
inline auto fmin(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::fmin(q.value(), qp))>
            (std::fmin(q.value(), qp));
}

template <typename Unit, typename T, typename U, typename T2>
inline auto fmax(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return Quantity<Unit, decltype(std::fmax(q.value(), qp))>
            (std::fmax(q.value(), qp));
}

template <typename Unit, typename T>
inline auto fabs(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::fabs(q.value()))>
            (std::fabs(q.value()));
}

template <typename Unit, typename T>
inline auto abs(Quantity<Unit, T> q){
    return Quantity<Unit, decltype(std::abs(q.value()))>
            (std::abs(q.value()));
}

template <typename Unit, typename T, typename U, typename T2, typename V, typename T3>
inline auto fma(Quantity<Unit, T> q, Quantity<U, T2> p, Quantity<V, T3> r){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    auto qr = Quantity<Unit, T>::template convert<V>(r.value());
    return Quantity<Unit, decltype(std::fma(q.value(), qp, qr))>
            (std::fma(q.value(), qp, qr));
}

template <typename Unit, typename T>
inline int fpclassify(Quantity<Unit, T> q){
    return std::fpclassify(q.value());
}

template <typename Unit, typename T>
inline bool isfinite(Quantity<Unit, T> q){
    return std::isfinite(q.value());
}

template <typename Unit, typename T>
inline bool isinf(Quantity<Unit, T> q){
    return std::isinf(q.value());
}

template <typename Unit, typename T>
inline bool isnan(Quantity<Unit, T> q){
    return std::isnan(q.value());
}

template <typename Unit, typename T>
inline bool isnormal(Quantity<Unit, T> q){
    return std::isnormal(q.value());
}

template <typename Unit, typename T>
inline bool signbit(Quantity<Unit, T> q){
    return std::signbit(q.value());
}

template <typename Unit, typename T, typename U, typename T2>
inline bool isgreater(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::isgreater(q.value(), qp);
}

template <typename Unit, typename T, typename U, typename T2>
inline bool isgreaterequal(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::isgreaterequal(q.value(), qp);
}

template <typename Unit, typename T, typename U, typename T2>
inline bool isless(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::isless(q.value(), qp);
}

template <typename Unit, typename T, typename U, typename T2>
inline bool islessequal(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::islessequal(q.value(), qp);
}

template <typename Unit, typename T, typename U, typename T2>
inline bool islessgreater(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::islessgreater(q.value(), qp);
}

template <typename Unit, typename T, typename U, typename T2>
inline bool isunordered(Quantity<Unit, T> q, Quantity<U, T2> p){
    auto qp = Quantity<Unit, T>::template convert<U>(p.value());
    return std::isunordered(q.value(), qp);
}


}
#endif // UNIT_CMATH_H
