//
//  rand.h
//  double sim
//
//  Created by Jens Kwasniok on 28.05.15.
//
//

#ifndef __double_sim__rand__
#define __double_sim__rand__

#include <random>

using rand_num_gen_t = std::default_random_engine;

namespace {
	constexpr rand_num_gen_t::result_type seed = 253867682;
	rand_num_gen_t rand_num_gen {seed};
}

template <typename T>
class Random {
	static std::uniform_int_distribution<T> lin_dist;
	static std::binomial_distribution<T> gauss_dist;

public:

	/// @return random value between 0 and numeric_limits<T>::max() with linear distribution
	static inline T get_rand_lin() {
		return lin_dist(rand_num_gen);
	}
	
	/// @return random value between 0 and b with linear distribution
	static inline T get_rand_lin(T b) {
		return lin_dist(rand_num_gen) % (b + 1);
	}
	
	/// @return random value between a and b with linear distribution
	static inline T get_rand_lin(T a, T b) {
		return lin_dist(rand_num_gen) % (b - a + 1) + a;
	}
	
	/// @return random value between a and b with linear distribution
	static inline T get_rand_gauss(T a, T b) {
		return gauss_dist(rand_num_gen) * float(b - a) + a;
	}
};

template <typename T>
std::uniform_int_distribution<T> Random<T>::lin_dist;
template <typename T>
std::binomial_distribution<T> Random<T>::gauss_dist {T(100), 0.5};

#endif /* defined(__double_sim__rand__) */
