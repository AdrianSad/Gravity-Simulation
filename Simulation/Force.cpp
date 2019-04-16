#include "Force.hpp"

	Force::Force(double dist, int m1, int M2)
		: r(dist),
		m(m1),
		M(M2) {}

	double Force::getForce() {
		return (G*M*m) / r;
	}
