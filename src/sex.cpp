//
//  sex.cpp
//  double sim
//
//  Created by Jens Kwasniok on 29.05.15.
//
//

#include "sex.h"

using namespace std;

ostream& operator<<(ostream& os, Sex s) {
	switch (s) {
		case Sex::male:   os << "male"; break;
		case Sex::female: os << "female"; break;
	}
	return os;
}
