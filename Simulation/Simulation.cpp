#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
using namespace std;
using namespace sf;

struct Pos {
	float x, y;
	Pos(float xPos,float yPos) 
		: x(xPos),
		y(yPos) {}
	Pos(){}

	Pos & operator +=(const Pos & pos){
		this->x += pos.x;
		this->y += pos.y;
		return * this;
	}
};

class Force {

	const double G = 0.00000000006674;
	double r;
	int m;
	int M;
	Pos p1, p2;

public:
	Force(double dist, int m1, int M2)
		: r(dist),
		m(m1),
		M(M2) {}

	double getForce() {
		//r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
		//cout << "Force: " << " r: " << r  << " m: "<< m << " M: " << M << " f: "<<(G*M*m) / r << endl;
		return (G*M*m) / r;
	}

};

class Planet :
public CircleShape{

	int m;
	int r;
	Vector2<double> acc;
	Vector2<double> vel;

public:
	Planet(int mass, int r): CircleShape(r){
		m = mass;
		this->setOrigin(r, r);
		acc = Vector2<double>(0.f, 0.f);
		vel = Vector2<double>(0.f, 0.f);
	}

	int getMass() { return m; }
	Vector2<double> getVel() const { return vel; } ;
	Vector2<double> getVel() { return vel; }

	void addVel(Vector2<double> velocity){
	
		vel += velocity;
		//cout << "vel: " << vel.x << " " << vel.y << endl;
	}

	void setVel(Vector2<double> velocity) {
			vel = velocity;
	}

	Vector2<double> getFinalForce(vector<Planet *> planets) {

		Vector2<double> result = Vector2<double>(0.f,0.f);
		Vector2<double> dir;

		for (auto & planet : planets) {
			
			if (planet != this) {
				//cout << "&planet " << planet << " this " << this << endl;
				dir = (Vector2<double>)(planet->getPosition()-this->getPosition());
				//cout << "dir: " << dir.x << " " << dir.y << endl;
				Force f = Force(dir.x * dir.x + dir.y * dir.y, this->getMass(), planet->getMass());
				result += f.getForce() / this->getMass() * (dir / (double)sqrt(dir.x * dir.x + dir.y * dir.y));
				//cout << result.x << " " << result.y << endl;
			}
		}
		return result;
	}

	void update(double dt, vector<Planet*> planets) {

		this->addVel(this->getFinalForce(planets)*dt);
		this->move(this->getVel().x*dt, this->getVel().y*dt);
	}

};


void refresh(double dt, vector<Planet*> planets) {

	for (auto & object : planets){

		object->update(dt * 5000, planets);
	}

	/*for (auto p = planets.begin(); p != planets.end(); p++) {
		
		vector<Planet>::iterator temp = planets.begin();
		bool not_fall = true;
		Vector2<double> result;

		for (auto p2 = planets.begin(); p2 != planets.end(); p2++) {

			if (p2 == p) continue;
			
			double d = sqrt((p2->getPos().x - p->getPos().x)*(p2->getPos().x - p->getPos().x) + (p2->getPos().y - p->getPos().y)*(p2->getPos().y - p->getPos().y));

			if (d > p->getRadius()) {

				//p->setVel(Pos(0.03 * p2->getMass() / (d*d) * (p2->getVel().x - p->getVel().x) / d, 0.03 * p2->getMass() / (d*d) * (p2->getVel().y - p->getVel().y) / d));
				//cout << "vx = " << 0.03 * p2->getMass() / (d*d) * (p2->getVel().x - p->getVel().x) << "  vy = " << 0.03 * p2->getMass() / (d*d) * (p2->getVel().y - p->getVel().y) / d << endl;

				Vector2<double> dir(p2->getVel().x - p->getVel().x, p2->getPos().y - p->getPos().y);
				Force f = Force(dir.x * dir.x + dir.y * dir.y, p->getMass(), p2->getMass());
				//double acceleration = f.getForce() / p2->getMass();
				//p2->addVel(Pos(acceleration*dt,acceleration*dt));
				//result.x += f.getForce() / p2->getMass() * (dir.x / sqrt(dir.x * dir.x + dir.y * dir.y));
				//result.y += f.getForce() / p2->getMass() * (dir.y / sqrt(dir.x * dir.x + dir.y * dir.y));
				result += f.getForce() / p2->getMass() * (dir/ sqrt(dir.x * dir.x + dir.y * dir.y));

			}
			else {
				not_fall = false;
				temp = p2;
			}
		}

		if (not_fall) {

			p->addVel(Pos(result.x*dt,result.y*dt));
			p->update(dt);
			cout << result.x << " " << result.y << endl;

		}else {

			//p->addRadius(temp->getRadius());
			temp = planets.erase(temp);
			
		}

}*/
}

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
	vector<Planet*> planets;
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
		//sf::Time dt = deltaClock.restart();

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