//
//  aux_algorithms.h
//  double sim
//
//  Created by Jens Kwasniok on 28.05.15.
//
//

#ifndef double_sim_aux_algorithms_h
#define double_sim_aux_algorithms_h

#include <vector>
#include <assert.h>

/// remove an element from a vector
/// (removes first appearing instance)
template<typename T>
bool inline remove(std::vector<T>& c, T& e) {
	for (auto& x : c) {
		if (x == e) {
			std::swap(x, c.back());
			c.pop_back();
			return true;
		}
	}
	return false;
}

/// clamp a value such that min <= clamp(v) <= max
template <typename  T>
T inline clamp(T v, T min, T max) {
	assert(min <= max && "min must be smaller or equal to max");
	if (v < min) v = min;
	if (v > max) v = max;

	return v;
}

#endif
