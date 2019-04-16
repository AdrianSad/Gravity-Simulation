#include <SFML/System.hpp>
#include "Planet.hpp"
#include "Force.hpp"

Planet::Planet(int mass, int r) : CircleShape(r) {
	m = mass;
	this->setOrigin(r, r);
	acc = Vector2<double>(0.f, 0.f);
	vel = Vector2<double>(0.f, 0.f);
}

int Planet::getMass() { return m; }
Vector2<double> Planet::getVel() const { return vel; }

void Planet::addVel(Vector2<double> velocity) {

	vel += velocity;
}

void Planet::setVel(Vector2<double> velocity) {
	vel = velocity;
}

Vector2<double> Planet::getFinalForce(vector<Planet *> planets) {

	Vector2<double> result = Vector2<double>(0.f, 0.f);
	Vector2<double> dir;

	for (auto & planet : planets) {

		if (planet != this) {
			dir = (Vector2<double>)(planet->getPosition() - this->getPosition());
			auto f = Force(dir.x * dir.x + dir.y * dir.y, this->getMass(), planet->getMass());
			result += f.getForce() / this->getMass() * (dir / (double)sqrt(dir.x * dir.x + dir.y * dir.y));
		}
	}
	return result;
}

void Planet::update(double dt, vector<Planet*> planets) {

	this->addVel(this->getFinalForce(planets)*dt);
	this->move(this->getVel().x*dt, this->getVel().y*dt);
}