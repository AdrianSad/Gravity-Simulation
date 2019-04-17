#include "Universe.hpp"
#include <cstdlib>

Universe::Universe(float speed) :
	worldSpeed(speed) {}

Universe::addPlanet(Vector2<double> position, Vector2<double> velocity) {

	auto tab[] = { Color::Red, Color::Blue, Color::Cyan, Color::Green, Color::White, Color::Purple };
	auto color = tab[rand() % 6];
	auto * temp = new Planet(1, 5);
	temp->setFillColor(color);
	temp->setPosition((float)position);
	temp->addVel(velocity);
	planets.push_back(temp);

}

void Universe::getPlanet(Vector2<double> mousePosition) const {


	/*for (auto & planet : planets) {



	}*/

}

float Universe::getSpeed() const {

	return worldSpeed;

}

void Universe::increaseSpeed() {

	worldSpeed *= 2;
}

void Universe::decreaseSpeed() {

	worldSpeed /= 2;
}

void Universe::refresh(double dt) {

	for (auto & object : planets) {

		object->update(dt * worldSpeed, planets);
	}
}

