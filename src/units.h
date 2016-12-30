//
//  units.h
//  double sim
//
//  Created by Jens Kwasniok on 27.11.16.
//
//

#ifndef time_t_h
#define time_t_h

/// integer representing time
/// 1 unit := 1 day
/// (Time is measured globally relavtive to an arbitrary point represented by 0
/// e.g. the start of a simulation.)
using Time = int;

/// floating point number representing time
/// 1 unit := 1 day
/// (Time is measured globally relavtive to an arbitrary point represented by 0
/// e.g. the start of a simulation.)
using Time_f = double;

/// integer representing measurements in length
/// 1 unit := fantasitc mile ≈ sqrt(2)km
using Length = int;

/// floating point number representing measurements in length
/// 1 unit := fantasitc mile ≈ sqrt(2)km
using Length_f = double;

/// integer representing measurements in speed
/// 1 unit := fantasitc mile per day
using Velocity = int;

/// floating point number representing measurements in speed
/// 1 unit := fantasitc mile per day
using Velocity_f = double;

constexpr Time years = 360;
constexpr Time months = 30;
constexpr Time days = 1;

constexpr Length fantastic_miles = 1;

#endif /* time_t_h */
