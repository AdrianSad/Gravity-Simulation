#include <iostream>
#include <cmath>
#include <ctime>
#include "Planet.hpp"
#include "Universe.hpp"


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
	auto universe = Universe(1000.f);
	srand(time(NULL));

	sf::Clock deltaClock;
	double elapsedTime;
	bool leftClick = false, leftReleased = false;
	double xPressed, yPressed, xReleased, yReleased;

	RenderWindow window(sf::VideoMode(800, 800), "Gravity Simulation");

	Texture wikTex;
	if (!wikTex.loadFromFile("wiktor.jpg"))
	{
		cout << "image error" << endl;
	}
	sf::Sprite sprite;
	sprite.setTexture(wikTex);

	Planet sun = Planet(1000000000, 45);
	Planet earth = Planet(2, 10);
	Planet mars = Planet(1, 5);
	mars.setFillColor(Color::Red);
	mars.setVel(Vector2<double>(0.f, -0.02));
	mars.setPosition(600.f, 400.f);
	earth.setPosition(150.f, 400.f);
	earth.setFillColor(Color::Blue);
	earth.setVel(Vector2<double>(0.f, -0.01));
	//sun.setFillColor(Color::Yellow);
	sun.setPosition(400.f, 400.f);
	sun.setTexture(&wikTex);
	planets.push_back(&sun);
	planets.push_back(&mars);
	planets.push_back(&earth);

	window.setFramerateLimit(60);
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

					/*double randomX = rand() % 400;
					double randomY = rand() % 400;
					planets.push_back(Planet(100, 5, Pos(randomX, randomY)));*/

					xPressed = event.mouseButton.x;
					yPressed = event.mouseButton.y;
					leftClick = true;

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
		for (auto &p : planets) {
			window.draw((*p));
		}
		refresh(elapsedTime, planets);

		if (leftClick) {

			drawLine(window, xPressed, yPressed, xReleased, yReleased);
		}

		if (leftReleased) {
			auto * temp = new Planet(1, 5);
			temp->setFillColor(Color::White);
			temp->setPosition((float)xReleased, (float)yReleased);
			temp->addVel(Vector2<double>((xPressed - xReleased)/1000, (yPressed - yReleased)/1000));
			planets.push_back(temp);
			leftReleased = false;
		}
		window.display();
	}

	return 0;
}