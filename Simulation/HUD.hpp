#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "hudObject.hpp"

class HUD : public sf::Drawable {

private:
	vector<hudObject*> arr;

public:
	void addObject(hudObject *obj);
	void update(float elapsedTime, RenderWindow & window, Universe universe);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};
