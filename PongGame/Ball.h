#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::RectangleShape ball;
	float speed = 0.2f;
	float dx,dy;
	
public:
	Ball();
	~Ball();

	void ballPos(float x, float y);
	void drawOn(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	bool borderCollision();
	float deflectBorder();
	float getAngle();
	void velocity(float angle);
	float deflect(int playerNo);
	sf::FloatRect getBounds();
	bool sideBorder();

};

