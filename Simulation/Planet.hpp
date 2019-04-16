#pragma once
#ifndef Planet_hpp
#define Planet_hpp
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Planet :
	public CircleShape {

private:
	int m;
	int r;
	Vector2<double> acc;
	Vector2<double> vel;

public:
	Planet(int mass, int r);

	int getMass();
	Vector2<double> getVel() const;

	void addVel(Vector2<double> velocity);

	void setVel(Vector2<double> velocity);

	Vector2<double> getFinalForce(vector<Planet *> planets);

	void update(double dt, vector<Planet*> planets);

};

#endif // !Planet_hpp