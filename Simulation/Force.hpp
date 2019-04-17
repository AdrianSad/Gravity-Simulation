#pragma once

class Force {

private:
	const double G = 0.00000000006674;
	double r;
	int m;
	int M;

public:
	Force(double dist, int m1, int M2);
	double getForce();

};

