#pragma once
#include <SFML/Graphics.hpp>

class Score
{
private:
	sf::Text text,score;

public:
	Score(sf::Font &font);
	~Score();

	void drawOn(sf::RenderWindow &window);
	void setScore(char s,float x,float y);
	void mainText();
	void setScore(int player);
	void setString(int player, sf::RenderWindow &window);
};

