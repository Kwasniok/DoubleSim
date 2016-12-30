//
//  person.cpp
//  double sim
//
//  Created by Jens Kwasniok on 25.05.15.
//
//

#include "person.h"
#include <map>

using namespace std;

unsigned Person::id_counter = 1;
/// death is more common when a person gets old
binomial_distribution<Time> Person::death_age_dist {Person::max_age, 0.8};
/// giving bith is more common for younger people
binomial_distribution<Time> Person::birth_age_dist {Person::max_age - Person::min_birth_age, 0.3};
/// linear distribution across all possible states
uniform_int_distribution<signed> Person::status_change_health_dist {-Person::max_health, +Person::max_health};


void Person::tick(const signed int time) {
	
	if (!_alive) return;

	// update health
	_health += rand_health_change();
	if (_health < min_health) _health = min_health;
	if (_health > max_health) _health = max_health;
	
	// update alive
	auto rand_d_age = rand_death_age() + _health;
	if (rand_d_age > max_age) rand_d_age = max_age;
	if (age(time) > rand_d_age) {
		kill();
	}
}

bool Person::can_give_birth(const signed time) const noexcept {
	
	if (dead() || age(time) < min_birth_age) return false;

	switch (_sex) {
		case Sex::female:
			if (time - _last_gave_birth_date < min_rebirth_span) return false; // fall through intended
		case Sex::male:
			auto rand_b_age = rand_birth_age();
			rand_b_age -= _health / 2;
			if (rand_b_age < min_birth_age) rand_b_age = min_birth_age;
				return age(time) > rand_b_age;
	}
}

bool Person::can_give_birth(const Person& p1, const Person& p2, const Time time) {
	// conditions for sucessfull birth:
	// 1. sexes complement each other
	// 2. both can give birth
	return complement(p1.sex(), p2.sex()) && p1.can_give_birth(time) && p2.can_give_birth(time);
}

Person Person::forced_birth_from_couple(Person& p1, Person& p2, const signed time)
{
	p1._last_gave_birth_date = time;
	p2._last_gave_birth_date = time;

	Sex sx = Person::rand_sex();

	signed sn;
	if (Random<bool>::get_rand_lin())
		sn = p1._strangeness;
	else
		sn = p2._strangeness;

	return {sx, time, sn};
}

ostream& operator<<(ostream& os, const Person& p) {
	os << "{id=" << p._id
	<< ", date_birth=" << p._birth_date
	<< ", strangeness=" << p._strangeness
	<< ", health=" << p._health
	<< ", last_born_date=" << p._last_gave_birth_date
	<< ", alive=" << p._alive
	<< ", sex=" << p._sex << "}";
	return os;
}
