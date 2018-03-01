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
	vector <position> pockerPos;
	
	vector <Sprite> playerPocker;
};

