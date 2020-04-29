// PongGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

//function declarations
void update(int p1s,int p2s, sf::RenderWindow &window);
void playAgain(int player, char gS,sf::RenderWindow &window,sf::Font font);


int main()
{
	//globally initialize a window
	sf::RenderWindow window(sf::VideoMode(700, 600), "Pong");

	//setting scores to '0' for both players
	int p1s = 0, p2s = 0;

	//passing the scores and window to 'update' function
	update(p1s, p2s, window);

	return 0;

};

/*
	Function Definitions
*/

//this function is the main function
	void update(int p1s,int p2s,sf::RenderWindow &window) {

		//intializing following variables for further use
		sf::Event Event;
		sf::Keyboard::Key key;
		sf::Font font;
		font.loadFromFile("arial.ttf");

		//initializing user-defined classes objects.
		Paddle p1, p2;
		Ball ball;
		Score welcome(font), p1_s(font), p2_s(font),winner(font);

		//setting the user object's positions
		p1.paddlePos(20, 40);
		p2.paddlePos(700 - 20, 600 - 90);
		ball.ballPos(700 / 2 + 10, 600 / 2 + 10);
		welcome.mainText();
		p1_s.setScore(1);
		p2_s.setScore(2);

		//passing the scores from function to a local variable to be manipulated
		int p1Score = p1s;
		int p2Score = p2s;
		char c[2];
		
		//declaring local variables for angle and gameState
		//gameState: helps in doing things once or keep it doing
		float angle;
		char gameState = 's';

		
		//type casting the 'int' to 'char' and use setScore() to set strings of player 1 & 2 scores
		sprintf_s(c, "%d", p1Score);
		p1_s.setScore(c[0], 340 - 30, 600 / 2 - 20);
		sprintf_s(c, "%d", p2Score);
		p2_s.setScore(c[0], 350 + 40, 600 / 2 - 20);
		
		//main game loop 
		while (window.isOpen()) {

			//check window Events if closed event is triggered window will be closed
			while (window.pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
					window.close();

				}
			}

			//clear windows with a black color
			window.clear();

			//render all objects on the window
			welcome.drawOn(window);
			p1_s.drawOn(window);
			p2_s.drawOn(window);
			p1.drawOn(window);
			p2.drawOn(window);
			ball.drawOn(window);

			//display all objects on window
			window.display();

			//since we only need angle once when game starts, therefore we use gameState variable for this
			//once 'Enter' key is pressed the ball will get a random angle and assign to 'angle' and change 'gameState' so that this block will not work again
			if (gameState == 's' && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				angle = ball.getAngle();
				gameState = 'p';
			}

			//this block will work till gameState remains 'p'
			if (gameState == 'p') {

				//move ball using the 'angle'
				ball.velocity(angle);

			//check keyboard inputs for paddle movements
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					//if the key is 'UpArrow' key then move player2 paddle up and check for top border collision
					key = sf::Keyboard::Up;
					p2.borderCollision();
					p2.paddleMove(key);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					//if the key is 'DownArrow' key then move player2 paddle down and check for bottom border collision
					key = sf::Keyboard::Down;
					p2.borderCollision();
					p2.paddleMove(key);

				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					//if the key is 'W' key then move player1 paddle up and check for top border collision
					key = sf::Keyboard::W;
					p1.borderCollision();
					p1.paddleMove(key);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					//if the key is 'S' key then move player1 paddle down and check for bottom border collision
					key = sf::Keyboard::S;
					p1.borderCollision();
					p1.paddleMove(key);
				}

				//if ball collides with top or bottom border change the gameState and deflect the ball by assigning a new angle and changine gameState back
				if (ball.borderCollision()) {
					gameState = 's';
					if (gameState == 's') {
						angle = ball.deflectBorder();
						gameState = 'p';
					}
				}

				//if ball collides with player1 paddle samething happens change the gameState and deflect the ball by assigning a new angle and 
				//changine gameState back
				else if (p1.ballCollision(ball)) {
					gameState = 's';
					if (gameState == 's') {
						angle = ball.deflect(1);
						gameState = 'p';
					}
				}
				//if ball collides with player1 paddle samething happens change the gameState and deflect the ball by assigning a new angle and 
				//changine gameState back
				else if (p2.ballCollision(ball)) {
					gameState = 's';
					if (gameState == 's') {
						angle = ball.deflect(2);
						gameState = 'p';
					}
				}

				//then move ball by using the assigned 'angle'
				ball.velocity(angle);

				//check ball position to add in scores of player 1 or 2 and calling the function again using the new scores so as to update scores on window
				//if ball moves to the extreme right add in scores of player1 
				if (ball.getPosition().x > 690) {
					gameState = 's';
					if (gameState == 's') {
						p1Score += 1;
						update(p1Score, p2Score, window);
					}
				}

				//if ball moves to the extreme left add in scores of player2
				if (ball.getPosition().x < 0) {					 
					gameState = 's';
					if (gameState == 's') {
						p2Score += 1;
						update(p1Score, p2Score, window);
					}					
				}
					
				//keep checking scores if increase to a certain number here is '2' tell who wins by passing player number 1 or 2 to playAgain() with gameState
				if (p1Score > 2) {

					gameState = 's';
					playAgain(1, gameState, window,font);
				}

				if (p2Score > 2) {

					gameState = 's';
					playAgain(2, gameState, window,font);
				}
			}
		}
	};

	//this tells which player wins 
	void playAgain(int player, char gS,sf::RenderWindow &window, sf::Font font) {
		sf::Text win;
		
		Score winner(font);

		//keep whowing the string till 'Space' is pressed
		while (true) {

			//clears the window with black color show the respective string 
			window.clear();
			winner.setString(player, window);
			win.setFont(font);
			win.setString("Would you like to play again? Press Space to play...");
			win.setCharacterSize(20);
			win.setPosition(1, 600 / 2 + 100);
			window.draw(win);
			//if 'Space' pressed break the loop
			if (gS == 's' && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				gS = 'p';
				break;
			}

			window.display();
		}

		//again call 'update' function with 0 scores for player 1 and 2
		if (gS == 'p') {
			update(0, 0, window);
		}
	};

	