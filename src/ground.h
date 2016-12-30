//
//  ground.h
//  double sim
//
//  Created by Jens Kwasniok on 08.06.15.
//
//

#ifndef __double_sim__ground__
#define __double_sim__ground__

#include <iostream>
#include "units.h"

class Ground {
	
public:
	static constexpr char DEFAULT = 1;
	static constexpr char GRASS = 1;
	static constexpr char DESERT = 2;
	static constexpr char HILLS = 3;
	static constexpr char MOUNTAINS = 4;
	static constexpr char SWAMP = 5;
	static constexpr char FOREST = 6;
	
private:
	char _val;
	
public:
	
	Ground(char val) : _val(val) { };
	
	inline void operator=(const char val) {
		_val = val;
	}
	
	inline bool operator==(const Ground rhs) const {
		return _val == rhs._val;
	}
	
	static constexpr double min_habitability_fac = 0.00;
	static constexpr double max_habitability_fac = 1.50;
	/// @return quality of habitability on this type of ground
	/// 0.0 := no habitability, 1.0 := default habitability
	/// @see min_habitability_fac, max_habitability_fac
	inline double habitability_fac() const noexcept {
		
		switch (_val) {
			case Ground::GRASS:     return 1.00;
			case Ground::DESERT:    return 0.01;
			case Ground::HILLS:     return 0.33;
			case Ground::MOUNTAINS: return 0.20;
			case Ground::SWAMP:     return 0.20;
			case Ground::FOREST:    return 1.00;
		}
		
		return 0.00;
	}
	
	static constexpr double min_travel_time_fac = 0.00;
	/// @return travel time factor for a given type of ground
	/// 1 := normal travel speed
	/// @see min_travel_time_fac
	inline double travel_time_fac() const noexcept {
		
		switch (_val) {
			case Ground::GRASS:     return 1.00;
			case Ground::DESERT:    return 5.00;
			case Ground::HILLS:     return 2.00;
			case Ground::MOUNTAINS: return 6.00;
			case Ground::SWAMP:     return 3.00;
			case Ground::FOREST:    return 1.50;
		}
		
		return 0.00;
	}
	
	static constexpr Velocity_f normal_travel_velocity = 17.06; // TODO: MOVE TO TRAVEL RELATED FILE!
	
	std::ostream& operator<<(std::ostream& os) const;
	
};

#endif /* defined(__double_sim__ground__) */
