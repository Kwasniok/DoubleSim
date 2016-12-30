//
//  ground.cpp
//  double sim
//
//  Created by Jens Kwasniok on 08.06.15.
//
//

#include "ground.h"

std::ostream& Ground::operator<<(std::ostream &os) const {
	
	std::string s;
	
	switch (_val) {
		case Ground::GRASS:     s = "grass";     break;
		case Ground::DESERT:    s = "desert";    break;
		case Ground::HILLS:     s = "hills";     break;
		case Ground::MOUNTAINS: s = "mountains"; break;
		case Ground::SWAMP:     s = "swamp";     break;
		case Ground::FOREST:    s = "forest";    break;
		default:                s = "UNDEFINED"; break;
	}
	
	os << "ground<" << s << ">";
	
	return os;
}
