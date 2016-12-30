//
//  settlement.cpp
//  double sim
//
//  Created by Jens Kwasniok on 27.05.15.
//
//

#include "settlement.h"
#include <map>
#include "rand.h"

bool Settlement::arrives(Person&& p) {
	add(std::move(p));
	return true;
}

bool Settlement::departs(Person& p) {
	return remove(p);
}

void Settlement::tick_remove_dead(const Time time) {
	
	for (auto& p : persons) {
		if (p.dead()) {
			std::swap(persons.back(), p);
			persons.pop_back();
			--living_persons;
		}
	}
}

void Settlement::tick_birth(const Time time) {
	
	for (int t=0; t < persons.size(); ++t) {
		auto i = Random<unsigned long>::get_rand_lin(persons.size());
		Person& p1 = persons[i];
		i = Random<unsigned long>::get_rand_lin(persons.size());
		Person& p2 = persons[i];
		Person mp;
		if (Person::birth_from_couple(mp, p1, p2, time)) {
			persons.push_back(std::move(mp));
			++living_persons;
			++total_living_persons;
		}
	}
}

void Settlement::tick(const Time time) {
	
	if (living_persons > food_resources) {
		for (signed i=0; i < living_persons - food_resources; ++i) {
			auto j = Random<persons_index_t>::get_rand_lin(persons.size()-1);
			double c = 10.0 * (1.5 - double(persons[j].health() - Person::min_health)
							   / double(Person::max_health - Person::min_health));
			if (Chance::one_per(c)) {
				persons[j].kill();
			}
		}
	}
	
	tick_remove_dead(time);
	tick_birth(time);
}

double Settlement::local_birth_fac() const noexcept {
	
	double lbf;
	if (living_persons != 0) {
		lbf = double(food_resources) / double(living_persons);
	} else {
		lbf = double(food_resources);
	}
	lbf *= ground.habitability_fac();

	return clamp(lbf, min_local_birth_fac, max_local_birth_fac);
}
