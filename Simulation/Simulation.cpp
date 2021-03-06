#include <iostream>
#include <cmath>
#include <ctime>
#include "Planet.hpp"
#include "Universe.hpp"
#include "HUD.hpp"
#include "FPS.hpp"
#include "hudObject.hpp"
#include "PlanetInfo.hpp"


void drawLine(RenderWindow & window ,int x1, int y1, int x2, int y2) {

	Vertex line[] =
	{
		Vertex(sf::Vector2f(x1, y1)),
		Vertex(sf::Vector2f(x2, y2))
	};

	window.draw(line, 5, sf::Lines);
}

int main()
{
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(800, 800), "Gravity Simulation");
	window.setFramerateLimit(60);

	sf::Clock deltaClock;
	double elapsedTime;
	bool leftClick = false, leftReleased = false;
	double xPressed, yPressed, xReleased, yReleased;

	auto hud = HUD();
	auto universe = Universe(1000.f);
	auto sun = Planet(1000000000, 45);
	auto earth = Planet(2, 10);
	auto mars = Planet(1, 5);
	auto fps = FPS();
	auto planetInfo = PlanetInfo();
	hud.addObject(&fps);
	hud.addObject(&planetInfo);

	mars.setFillColor(Color::Red);
	mars.setVel(Vector2<double>(0.f, -0.02));
	mars.setPosition(600.f, 400.f);
	earth.setPosition(150.f, 400.f);
	earth.setFillColor(Color::Blue);
	earth.setVel(Vector2<double>(0.f, -0.01));
	sun.setFillColor(Color::Yellow);
	sun.setPosition(400.f, 400.f);

	universe.addPlanet(&sun);
	universe.addPlanet(&earth);
	universe.addPlanet(&mars);

	while (window.isOpen())
	{

		elapsedTime = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed){

				if (event.mouseButton.button == Mouse::Left && leftClick == false) {

					xPressed = event.mouseButton.x;
					yPressed = event.mouseButton.y;
					leftClick = true;

				}
			}

			if (event.type == Event::MouseButtonPressed) {

				if (event.mouseButton.button == Mouse::Right) {

					universe.getPlanet(Vector2<double>(event.mouseButton.x, event.mouseButton.y));
				}
			}

			if (event.type == Event::MouseMoved) {

				xReleased = event.mouseMove.x;
				yReleased = event.mouseMove.y;
			}

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {

				leftReleased = true;
				leftClick = false;
			}
		}

		window.clear();
		universe.refresh(elapsedTime);
		hud.update(elapsedTime, window, universe);
		window.draw(hud);

		for (auto &p : universe.getPlanets()) { // <- do klasy hud
			window.draw((*p));
		}

		if (leftClick) { // <- do innej 

			drawLine(window, xPressed, yPressed, xReleased, yReleased);
		}

		if (leftReleased) {

			universe.addPlanet(Vector2f((float)xReleased, (float)yReleased), Vector2<double>((xPressed - xReleased) / 1000, (yPressed - yReleased) / 1000));
			leftReleased = false;
		}
		window.display();
	}

	return 0;
}