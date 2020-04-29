#include "Ball.h"

//set Bal size and color
Ball::Ball() {

	ball.setSize({ 10, 10 });
	ball.setFillColor(sf::Color::White);
}

Ball::~Ball() {

}

//set ball initial position
void Ball::ballPos(float x, float y) {

	ball.setPosition(x, y);
}

//render ball on window
void Ball::drawOn(sf::RenderWindow &window) {
	
	window.draw(ball);
}

//get angle at which the ball will shoot randomly in that direction
float Ball::getAngle() {

	int count = 0;
	float angle = -21;
	const float PI = 3.16f;
	
	while (true) {
		if (angle >= 3 && angle <= 360) {
			break;
		}
		else
			angle = (rand() % 300) * PI - 20;			
	}

	return angle;
}

//set ball velocity using randomly generated angle and move it
void Ball::velocity(float angle) {

	dx = cosf(angle) * speed;
	dy = sinf(angle) * speed;

	ball.move(dx, dy);
}

//get ball globalBounds to check its interaction with the paddles
sf::FloatRect Ball::getBounds() {

	return ball.getGlobalBounds();
}

//deflect ball by getting a new angle
float Ball::deflect(int playerNo) {

	float angle;
	if (playerNo == 1) {
		angle = getAngle() * 1.0;
	}

	if (playerNo == 2) {
		angle = getAngle() * -1.0;
	}
	return angle;
	
}

//check if ball collides with top and bottom window border
bool Ball::borderCollision() {

	
	if ((ball.getPosition().y >= 580 && ball.getPosition().x >= 0)|| ball.getPosition().y <= 0) {
		return true;
	}
	else
		return false;
	
}

//when ball touches top and bottom window border deflect ball by getting another angle
float Ball::deflectBorder() {

	float angle = 0.0f;
	
	if ((ball.getPosition().y >= 580 && ball.getPosition().x >= 0) || ball.getPosition().y <= 0) {

		angle = getAngle() * -1.0f;
	}
	return angle;
}

//check if ball passes through side borders
bool Ball::sideBorder() {
	if (ball.getPosition().x < 0 || ball.getPosition().x > 690) {
		return true;
	}
	else
		return false;
}

//get current position of ball
sf::Vector2f Ball::getPosition() {

	return ball.getPosition();
}
