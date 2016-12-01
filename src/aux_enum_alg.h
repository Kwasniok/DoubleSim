//
//  aux_enum_alg.h
//  double sim
//
//  Created by Jens Kwasniok on 08.06.15.
//
//

#ifndef double_sim_aux_enum_alg_h
#define double_sim_aux_enum_alg_h

#include <type_traits>

//! @return value of the enum as its underlying type <p>
//! @brief supports all enums
template<class E>
constexpr inline std::underlying_type_t<E> to_number(E e) noexcept {
	return static_cast<std::underlying_type_t<E>>(e);
}

//! @return corresponding element of an enum to a number of its underlying type
//! @brief ONLY for 'camped' enums (consider forwaring via inline function) <p>
//! Enum E must support: <p>
//! - E::first = lowest value to be clamped to <p>
//! - E::last  = highest value to be clamped to <p>
//! - all values between E::first and E::last including E::first and E::last
template<class E>
constexpr E to_enum_with_clamp(std::underlying_type_t<E> n) {
	if (n > to_number(E::last)) n = to_number(E::last);
	if (n < to_number(E::first)) n = to_number(E::first);
	return static_cast<E>(n);
}

//! @return corresponding element of an enum to a number of its underlying type
//! @brief ONLY for enums supporting none (consider forwaring via inline function) <p>
//! Enum E must support: <p>
//! - E::first = lowest acceptable value <p>
//! - E::last  = highest acceptable value <p>
//! - E::none <p>
//! - all values between E::first and E::last including E::first and E::last
template<class E>
constexpr E to_enum_with_none(std::underlying_type_t<E> n) {
	return (n > to_number(E::last) && n < to_number(E::first) ? E::none : static_cast<E>(n));
}

#endif
