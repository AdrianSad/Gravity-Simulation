#pragma once
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

class hudObject : public sf::Drawable {

public:

	virtual void update(float elapsedTime, Universe universe, RenderWindow & window)=0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};
