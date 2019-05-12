#include "PlanetInfo.hpp"
#include <iostream>
#include <iomanip> 
PlanetInfo::PlanetInfo(){

	font.loadFromFile("fonts/Pixel.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.setPosition(250, 10);

}

void PlanetInfo::update(float elapsedTime, Universe universe, RenderWindow & window) {

	Planet * planet = universe.getPlanet(sf::Vector2<double>(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y));

	if (planet) {
		text.setString("Speed : " + std::to_string((float)planet->getVel().x) + ", " + std::to_string((float)planet->getVel().y) +
			"\nPosition : " + std::to_string((int)planet->getPosition().x) + ", " + std::to_string((int)planet->getPosition().y)
			+ "\nMass : " + std::to_string(planet->getMass()));
	}
	else {
		text.setString("Select planet to see more information");
	}
}

void PlanetInfo::draw(sf::RenderTarget &target, sf::RenderStates states)const {

	target.draw(text, states);

}