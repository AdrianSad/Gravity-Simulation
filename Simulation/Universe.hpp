#pragma once
#ifndef Universe_hpp
#define Universe_hpp
#include "Planet.hpp"

class Universe {

private:
	float worldSpeed;
	vector<Planet*> planets

public:
	Universe(float speed);

	void addPlanet(Vector2<double> position, Vector2<double> velocity);
	void getPlanet(Vector2<double> mousePosition) const;
	float getSpeed() const;
	void increaseSpeed();
	void decreaseSpeed();
	void refresh(double dt);
};

#endif // !Universe_hpp
