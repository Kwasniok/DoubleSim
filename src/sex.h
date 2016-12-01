//
//  sex.h
//  double sim
//
//  Created by Jens Kwasniok on 29.05.15.
//
//

#ifndef __double_sim__sex__
#define __double_sim__sex__

#include <iostream>
#include "aux_enum_alg.h"

enum class Sex /* : bool */ {
	male = 0,
	female = 1,

	first = 0,
	last = 1
	// no none possible
};

/// convert number to sex
constexpr inline Sex to_sex(std::underlying_type_t<Sex> n) {
	return to_enum_with_clamp<Sex>(n);
}

/// @return true, if gives sexes complement for a potentiallay reproducing couple
constexpr inline bool complement(Sex a, Sex b) {
	return (a == Sex::male && b == Sex::female) ||
		   (a == Sex::female && b == Sex::male);
}

std::ostream& operator<<(std::ostream& os, Sex s);


#endif /* defined(__double_sim__sex__) */
