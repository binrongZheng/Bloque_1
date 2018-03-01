#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include "pokerImg.h"


struct position
{
	int x, y;
};
class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void start();

private:
	pokerImg pocker;
	vector <position> playerPockerPos;
	vector <Sprite> playerPocker;

	vector <position> otherPlayerPockerPos;
	vector <Sprite> otherPlayerPocker;

	Sprite centerCard;
};

