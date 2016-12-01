//
//  settlement.h
//  double sim
//
//  Created by Jens Kwasniok on 27.05.15.
//
//

#ifndef __double_sim__settlement__
#define __double_sim__settlement__

#include "person.h"
#include "aux_algorithms.h"
#include "ground.h"

class Settlement {
	
public:
	
	/// container type to represent the persons living in a settlement
	using persons_index_t = std::vector<Person>::size_type;
	
private:
	
	/// persons living in a settlement
	std::vector<Person> persons;
	/// amount of living persons in a settlement
	unsigned living_persons = 0;
	/// amount of all persons lived in a stettlement
	unsigned total_living_persons = 0;
	/// ground type a settlement is bild upon
	Ground_Type ground = Ground_Type::dfault;
	/// amount of food resoures (1 unit := resources for 1 person to live)
	unsigned food_resources = 0;

public:
	
	Settlement(unsigned food_res) : food_resources(food_res) { }

	// persons
	const std::vector<Person>& get_persons() const noexcept {return persons;}
	persons_index_t get_persons_amount() const _NOEXCEPT {return persons.size();}
	unsigned get_persons_alive() const noexcept {return living_persons;}
	unsigned get_persons_total() const noexcept {return total_living_persons;}
	
	// ground
	Ground_Type get_ground() const noexcept {return ground;}
	void set_ground(Ground_Type g) noexcept {ground = g;}
	
	// resurces
	void set_food_resources(unsigned res) noexcept {food_resources = res;}
	void add_food_resources(unsigned res) noexcept {food_resources += res;}
	void remove_food_resources(unsigned res) noexcept
		{if (res >= food_resources) food_resources = 0; else food_resources -= res;}
	void change_food_resources(signed res) noexcept
		{if (res >= 0) add_food_resources(res); else remove_food_resources(-res);}
	unsigned get_food_resources() const noexcept {return food_resources;}

	// person
	// person created / deleted (must be accepted)
	/// forces adding a person to a settlement
	void add(Person&& p)
	{if (p.alive()) {++living_persons; ++total_living_persons;} persons.push_back(std::move(p));}
	/// forces removal of a person from a settlement
	bool remove(Person& p)
		{if (p.alive()) --living_persons; return ::remove(persons, p);}
	// person moving from settlement to settlement (might not be accepted)
	/// adds a person to a settlement (might not be accepted)
	/// @return true iff addition was accepted
	bool arrives(Person&& p);
	/// removes a person from a settlement (might not be accepted)
	/// @return true iff addition was removed
	bool departs(Person& p);

	/// simulate one step in time (i.e. a year)
	void tick(const unsigned time);

	/// global birth factor used to controll birth rate
	/// #births tried per year = #males & females who can give birth / (birth_fac * local_birth_fac)
	static constexpr double birth_fac = 2.0 / 10.0; /// (empirical value)
	static constexpr double min_local_birth_fac = 0.00; // no birth
	static constexpr double max_local_birth_fac = 2.00; // twice as normal
	/// @return birth factor for a settlement claped to min/max values
	/// @see min_local_birth_fac, max_local_birth_fac
	double get_local_birth_fac() const noexcept;

	// local death factor
	static constexpr double min_local_death_fac = 0.25; // less deaths
	static constexpr double max_local_death_fac = 2.00; // twice as normal

};

#endif /* defined(__double_sim__settlement__) */
