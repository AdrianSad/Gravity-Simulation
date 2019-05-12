#pragma once
#define Universe_hpp
#include "Planet.hpp"

class Universe {

private:
	float worldSpeed;
	vector<Planet*> planets;

public:
	Universe(float speed);

	void addPlanet(Vector2f position, Vector2<double> velocity);
	void addPlanet(Planet * obj);
	Planet* getPlanet(Vector2<double> mousePosition) const;
	float getSpeed() const;
	void increaseSpeed();
	void decreaseSpeed();
	void refresh(double dt);
	vector<Planet*> getPlanets() const;
};

