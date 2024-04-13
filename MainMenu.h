#pragma once
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class MainMenu
{
private:
	int selected;
	Font font;

public:
	Text mainmenu[3];
	MainMenu(float width, float hight);
	void draw(RenderWindow& window);
	void moveup();
	void movedown();
	void setselected(int n);
	int pressed() {
		return selected;
	}
	~MainMenu();
};

