#include "pokerImg.h"

pokerImg::pokerImg()
{
	setString();
	setTexture();
	setSprite();
}

pokerImg::~pokerImg()
{
}

void pokerImg::setString() {
	str_pocker.push_back(imgAdress + "A-1.jpg");
	str_pocker.push_back(imgAdress + "2-1.jpg");
	str_pocker.push_back(imgAdress + "3-1.jpg");
	str_pocker.push_back(imgAdress + "4-1.jpg");
	str_pocker.push_back(imgAdress + "5-1.jpg");
	str_pocker.push_back(imgAdress + "6-1.jpg");
	str_pocker.push_back(imgAdress + "7-1.jpg");
	str_pocker.push_back(imgAdress + "8-1.jpg");
	str_pocker.push_back(imgAdress + "9-1.jpg");
	str_pocker.push_back(imgAdress + "10-1.jpg");
	str_pocker.push_back(imgAdress + "A-2.jpg");
	str_pocker.push_back(imgAdress + "2-2.jpg");
	str_pocker.push_back(imgAdress + "3-2.jpg");
	str_pocker.push_back(imgAdress + "4-2.jpg");
	str_pocker.push_back(imgAdress + "5-2.jpg");
	str_pocker.push_back(imgAdress + "6-2.jpg");
	str_pocker.push_back(imgAdress + "7-2.jpg");
	str_pocker.push_back(imgAdress + "8-2.jpg");
	str_pocker.push_back(imgAdress + "9-2.jpg");
	str_pocker.push_back(imgAdress + "10-2.jpg");
	str_pocker.push_back(imgAdress + "A-3.jpg");
	str_pocker.push_back(imgAdress + "2-3.jpg");
	str_pocker.push_back(imgAdress + "3-3.jpg");
	str_pocker.push_back(imgAdress + "4-3.jpg");
	str_pocker.push_back(imgAdress + "5-3.jpg");
	str_pocker.push_back(imgAdress + "6-3.jpg");
	str_pocker.push_back(imgAdress + "7-3.jpg");
	str_pocker.push_back(imgAdress + "8-3.jpg");
	str_pocker.push_back(imgAdress + "9-3.jpg");
	str_pocker.push_back(imgAdress + "10-3.jpg");
	str_pocker.push_back(imgAdress + "A-4.jpg");
	str_pocker.push_back(imgAdress + "2-4.jpg");
	str_pocker.push_back(imgAdress + "3-4.jpg");
	str_pocker.push_back(imgAdress + "4-4.jpg");
	str_pocker.push_back(imgAdress + "5-4.jpg");
	str_pocker.push_back(imgAdress + "6-4.jpg");
	str_pocker.push_back(imgAdress + "7-4.jpg");
	str_pocker.push_back(imgAdress + "8-4.jpg");
	str_pocker.push_back(imgAdress + "9-4.jpg");
	str_pocker.push_back(imgAdress + "10-4.jpg");
	str_pocker.push_back(imgAdress + "back.jpg");
}

void pokerImg::setTexture() {
	for (int i = 0; i < str_pocker.size(); i++) {
		texture.loadFromFile(str_pocker[i]);
		tex_pocker.push_back(texture);
	}
}

void pokerImg::setSprite() {
	for (int i = 0; i < tex_pocker.size(); i++) {
		sprite.setTexture(tex_pocker[i]);
		spr_pocker.push_back(sprite);
	}
}

Sprite pokerImg::getSprite(int num) {
	return spr_pocker[num];
}