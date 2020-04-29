#include "Score.h"

//initializing Font for each text object
Score::Score(sf::Font &font) {

	text.setFont(font);
	score.setFont(font);
}

Score::~Score() {

}

//'text' object contains unchanging message such as the below one
void Score::mainText() {
	text.setString("Welcome To Pong! Press 'Enter' to play");
	text.setCharacterSize(20);
	text.setPosition(700 / 2 - 160, 0);
}

//render both text objects to window
void Score::drawOn(sf::RenderWindow &window) {

	window.draw(text);
	window.draw(score);
}

//set 'score' object to player 1 and 2 scores
void Score::setScore(char s,float x,float y) {

		score.setString(s);
		score.setCharacterSize(60);
		score.setPosition(x,y);		
}

//set 'text' to whatever player wins and shows that particular message
void Score::setString(int player,sf::RenderWindow &window) {
	if (player == 1) {
		text.setString("Player 1 WINS!!");
		text.setCharacterSize(60); 
		text.setPosition(20, 600 / 2);

	}
	if (player == 2) {
		text.setString("Player 2 WINS!!");
		text.setCharacterSize(60);
		text.setPosition(20, 600 / 2);

	}
	window.draw(text);
}

//set 'score' object initially to '0' and show it on screen
void Score::setScore(int player) {

	if (player == 1) {
		
		score.setString("0");
		score.setCharacterSize(60);
		score.setPosition(340 - 30, 600 / 2 - 20);
		
	}
	if (player == 2) {

		score.setString("0");
		score.setCharacterSize(60);
		score.setPosition(350 + 40, 600 / 2 - 20);
	
	}
}
