#ifndef KLINGON_HEADER
#define KLINGON_HEADER


#include <cstdlib>

namespace StarTrek {

class Klingon {
protected:
	int distance_;
	int energy_;

public:	
	Klingon() : distance_(100 + rand() % 4000), energy_(1000+ rand() % 2000) {
	}

	virtual ~Klingon() {
        }

	int distance(void) {
		return distance_;
	}

	int energy(void) {
		return energy_;
	}

	void energy(int value) {
		energy_ = value;
	}

	virtual void destroy(void); 
};
}

#endif
