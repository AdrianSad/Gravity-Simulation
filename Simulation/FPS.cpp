#include "FPS.hpp"
#include <iostream>

FPS::FPS() {
	
	font.loadFromFile("fonts/Pixel.ttf");
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);
}

void FPS::update(float elapsedTime, Universe universe, RenderWindow & window) {

	text.setString(std::to_string((int)(1.f / elapsedTime)) + " fps\n" +
		"Universe speed : x" + std::to_string(universe.getSpeed()));

}

void FPS::draw(sf::RenderTarget &target, sf::RenderStates states)const {

	target.draw(text, states);
}