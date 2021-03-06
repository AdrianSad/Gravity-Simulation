#include "Universe.hpp"
#include <cstdlib>
#include <cmath>

Universe::Universe(float speed) :
	worldSpeed(speed) {}

void Universe::addPlanet(Vector2f position, Vector2<double> velocity) {

	Color tab[] = { Color::Red, Color::Blue, Color::Cyan, Color::Green, Color::White, Color::Magenta };
	auto color = tab[rand() % 6];
	auto * temp = new Planet(1, 5);
	temp->setFillColor(color);
	temp->setPosition(position);
	temp->addVel(velocity);
	planets.push_back(temp);

}

void Universe::addPlanet(Planet * obj) {

	planets.push_back(obj);

}

Planet* Universe::getPlanet(Vector2<double> mousePosition) const {


	for (auto & planet : planets) {

		if (sqrt((planet->getPosition().x - mousePosition.x)*(planet->getPosition().x - mousePosition.x) + (planet->getPosition().y - mousePosition.y)*(planet->getPosition().y - mousePosition.y)) < planet->getRadius()) {

			return planet;
		}
	}
	return NULL;

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

vector<Planet*> Universe::getPlanets() const {

	return planets;
}

