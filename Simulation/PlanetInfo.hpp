#pragma once
#include "hudObject.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

class PlanetInfo : public hudObject{

private:

	sf::Font font;
	sf::Text text;

public :
	PlanetInfo();
	void update(float elapsedTime, Universe universe, RenderWindow & window);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
};

