#include "Paddle.h"


//initialize size and color of the paddle
Paddle::Paddle() {

	pad.setSize({ 10,70 });
	pad.setFillColor(sf::Color::White);
}

Paddle::~Paddle() {

}

//set first position of paddle
void Paddle::paddlePos(float x,float y){
	 
	pad.setPosition(x, y);
}

//render the paddles on the windows referenced
void Paddle::drawOn(sf::RenderWindow &window) {
	window.draw(pad);
}

//if paddle collides with border up or down it stops there
void Paddle::borderCollision() {

	if (pad.getPosition().y <= 0) {
		pad.setPosition(pad.getPosition().x, pad.getPosition().y + 5);
	}
	if (pad.getPosition().y >= 530) {
		pad.setPosition(pad.getPosition().x, pad.getPosition().y - 5);
	}
}

//moves paddles according to each key 
void Paddle::paddleMove(sf::Keyboard::Key &key) {

	if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
		pad.move(0, -speed);
	}

	if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
		pad.move(0, speed);
	}
}

//check if ball collides with any paddle
bool Paddle::ballCollision(Ball &ball) {

	if (pad.getGlobalBounds().intersects(ball.getBounds())) {
		return true;
	}
	else
		return false;
}