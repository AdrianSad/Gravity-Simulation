#include "HUD.hpp"

void HUD::addObject(hudObject *obj) {

	arr.push_back(obj);
}

void HUD::update(float elapsedTime, RenderWindow & window, Universe universe) {

	for (auto hudObj : arr) {

		hudObj->update(elapsedTime, universe, window);
	}

}

 void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	 for (auto & obj : arr) {

		 target.draw(*obj,states);
	 }

}