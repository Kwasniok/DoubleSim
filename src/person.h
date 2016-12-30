//
//  person.h
//  double sim
//
//  Created by Jens Kwasniok on 25.05.15.
//
//

#ifndef __double_sim__person__
#define __double_sim__person__

#include <iostream>

#include "rand.h"
#include "units.h"
#include "sex.h"

class Person {
	
public:
	
	using Id = unsigned int;
	
private:
	
	static Id id_counter;
	// distributions for various variables used for random changes of a person:
	// - All distributions are ment to represent the average person. These values a uesed as a basis
	// for random decicions when simulating a tick for a person and can be combined with the state
	// of the person e.g. its health, strangeness etc..
	/// age when dieing relative to bith date
	static std::binomial_distribution<Time> death_age_dist;
	/// age when giving birth relative to minimal age when someone is able to give birth
	static std::binomial_distribution<Time> birth_age_dist;
	/// used as basis to change a health status
	static std::uniform_int_distribution<signed> status_change_health_dist;

	// data representing a person:
	/// unique id of a person
	Id _id = 0;
	/// birth date
	Time _birth_date = 0;
	/// date of last birth given by a person
	Time _last_gave_birth_date = 0;
	/// health of a person greather means better
	/// @see min_health, max_health
	signed _health = 50;
	/// starngeness is used to add extra randomness and make persons more unique
	signed _strangeness = 0;
	/// whether a person is alive
	bool _alive = true;
	/// represents (biolocical) sex
	Sex _sex;
	
public:
	
	Person(const Sex sex, const Time birth_date, const signed strangeness) noexcept
		: _id(++id_counter), _sex(sex), _birth_date(birth_date), _strangeness(strangeness) { }
	Person(const Sex sex, const Time birth_date, const signed strangeness, signed health) noexcept
		: _id(++id_counter), _sex(sex), _birth_date(birth_date), _strangeness(strangeness), _health(health) { }

	Person(Person&& rhs) = default;
	Person& operator=(Person&& rhs) = default;

	bool operator==(const Person& rhs) const {return _id == rhs._id;}

	/// simulate one step in time (i.e. a year)
	void tick(const Time time);

	// age
	Time birth_date() const noexcept {return _birth_date;}
	Time age(const Time time) const noexcept {return time - _birth_date;}
	// birth
	bool can_give_birth(const Time time) const noexcept;
	void mark_as_gave_last_birth(const Time time) {_last_gave_birth_date = time;}
	// health
	signed health() const noexcept {return _health;}
	// strangeness
	signed strangeness() const noexcept {return _strangeness;}
	// alive
	bool alive() const noexcept {return _alive;}
	bool dead() const noexcept {return !alive();}
	void kill() noexcept {_alive = false;}
	// sex
	Sex sex() const {return _sex;}
	bool has_sex(Sex s) const noexcept {return _sex == s;}
	

	/// maximum age for an average person
	static constexpr Time max_age = 120 * years;
	/// minimal age for a person to give birth
	static constexpr Time min_birth_age = 20 * years;
	/// minimal time between for a person between to births
	static constexpr Time min_rebirth_span = 1 * years;
	/// maximal health for a person
	static constexpr signed max_health = 100;
	/// minimal age for a person
	static constexpr signed min_health = 0;

	/// @return a random age when an average person could die
	static Time rand_death_age()
		{return death_age_dist(rand_num_gen);}
	/// @return a random age when an average person could give birth
	static Time rand_birth_age()
		{return Person::min_birth_age + birth_age_dist(rand_num_gen);}
	/// @return a random change in health for an average person
	static signed rand_health_change()
		{return status_change_health_dist(rand_num_gen);}
	/// @return a random sex for an average person
	static Sex rand_sex()
		{return to_sex(death_age_dist(rand_num_gen) % (to_number(Sex::last) +1));}
	
	/// a coulpe must match the following conditions to be able to give birth:
	///		(i)  the sexes must complement each other
	///		(ii) both must be able to give birth
	/// @return true iff couple can give birth
	static bool can_give_birth(const Person& parent1, const Person& parent2, const Time time);
	/// creates a new person from a given coulpe regardless if iit can give birth
	/// (check can_give_birth for couple before)
	/// @see complement, can_give_birth
	static Person forced_birth_from_couple(Person& parent1, Person& parent2, const Time time);
	
	// io
	friend std::ostream& operator<<(std::ostream& os, const Person& p);
	
};

std::ostream& operator<<(std::ostream& os, const Person& p);

#endif /* defined(__double_sim__person__) */
