//
//  settlement.cpp
//  double sim
//
//  Created by Jens Kwasniok on 27.05.15.
//
//

#include "settlement.h"
#include <map>

bool Settlement::arrives(Person&& p) {
	add(std::move(p));
	return true;
}

bool Settlement::departs(Person& p) {
	return remove(p);
}

unsigned remove_dead(std::vector<Person>& ps) {
	
	unsigned total_deaths = 0;
	for (auto& p : ps) {
		if (p.dead()) {
			std::swap(ps.back(), p);
			ps.pop_back();
			++total_deaths;
		}
	}
	
	return total_deaths;
}

unsigned birth(std::vector<Person>& ps, const signed time, double bf) {
	
	unsigned total_births = 0;
	
	std::map<Sex, unsigned> sx_can_give_birth;
	for (auto& p : ps) {
		if (p.can_give_birth(time)) {
			++sx_can_give_birth[p.sex()];
		}
	}
	
	auto s_can_give_birth = sx_can_give_birth[Sex::male] + sx_can_give_birth[Sex::female];
	
	if (ps.size() > 2) {
		for (int t=0; t < s_can_give_birth * bf; ++t) {
			auto i = Random<unsigned long>::get_rand_lin(ps.size());
			Person& p1 = ps[i];
			i = Random<unsigned long>::get_rand_lin(ps.size());
			Person& p2 = ps[i];
			Person mp;
			if (Person::birth_from_couple(mp, p1, p2, time)) {
				ps.push_back(std::move(mp));
				++total_births;
			}
		}
	}
	
	return total_births;
}

void Settlement::tick(const unsigned time) {
	unsigned food_res = food_resources;

	for (auto& p : persons) {

		p.tick(time);

		// TODO: find better algorithm for limited resources (sort by health?)
		//* I.
		if (p.alive()) {
			if (food_res > 0)
				--food_res;
			else
				p.kill();
		}
		//*/
	}
	auto d = remove_dead(persons);
	auto b = birth(persons, time, birth_fac * get_local_birth_fac());
	living_persons -= d;
	living_persons += b;
	total_living_persons += b;
}

double Settlement::get_local_birth_fac() const noexcept {
	double lbf;

	if (living_persons != 0)
		lbf = static_cast<double>(food_resources) / static_cast<double>(living_persons);
	else
		lbf = static_cast<double>(food_resources);

	return clamp(lbf, min_local_birth_fac, max_local_birth_fac);
}

/*
 double Settlement::get_local_death_fac() const noexcept {
	double ldf;
 
	if (food_resources != 0)
 ldf = static_cast<double>(living_persons) / static_cast<double>(food_resources);
	else
 ldf = static_cast<double>(living_persons);
 
	return clamp(ldf, min_local_death_fac, max_local_death_fac);
 }
 */
