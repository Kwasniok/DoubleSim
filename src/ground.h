//
//  ground.h
//  double sim
//
//  Created by Jens Kwasniok on 08.06.15.
//
//

#ifndef __double_sim__ground__
#define __double_sim__ground__

enum class Ground_Type /* : char */ {
	
	desert = 1,
	hills = 2,
	mountain = 3,
	grass = 4,
	swamp = 5,
	forest = 6,

	first = 1,
	last = 6,


	dfault = grass,
};

/// @return food factor for a given type of ground
/// @see min_food_fac_ground, max_food_fac_ground
static inline double get_food_fac_for_ground(Ground_Type g) noexcept;
static constexpr double min_food_fac_ground = 0.0;
static constexpr double max_food_fac_ground = 1.5;

inline double get_food_fac_for_ground(Ground_Type g) noexcept {
	
	switch (g) {
		case Ground_Type::desert:   return 0.01;
		case Ground_Type::hills:    return 0.33;
		case Ground_Type::mountain: return 0.20;
		case Ground_Type::grass:    return 1.00;
		case Ground_Type::swamp:    return 0.20;
		case Ground_Type::forest:   return 1.00;
	}
}

#endif /* defined(__double_sim__ground__) */
