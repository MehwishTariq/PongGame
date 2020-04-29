#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"


class Paddle
{
private:
	sf::RectangleShape pad;
	const float speed = 0.7f;

public:
	Paddle();
	~Paddle();
	
	void paddlePos(float x, float y);
	void borderCollision();
	void paddleMove(sf::Keyboard::Key &key);
	void drawOn(sf::RenderWindow &window);
	bool ballCollision(Ball &ball);
};

