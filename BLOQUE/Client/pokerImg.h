#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class pokerImg
{
public:
	pokerImg();
	~pokerImg();
	void setString();
	void setTexture();
	void setSprite();
	Sprite getSprite(int);


private:
	string imgAdress="img/";
	vector<string> str_pocker;

	Texture texture;
	vector<Texture> tex_pocker;

	Sprite sprite;
	vector<Sprite> spr_pocker;
};

