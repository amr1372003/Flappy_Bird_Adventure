#include "MainMenu.h"
#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;


MainMenu::MainMenu(float width, float hight)
{
	font.loadFromFile("Roboto-Bold.ttf");

	mainmenu[0].setFont(font);
	mainmenu[0].setFillColor(Color::Yellow);
	mainmenu[0].setString("PLAY");
	mainmenu[0].setCharacterSize(48);
	mainmenu[0].setPosition(Vector2f(width/ 3, hight / 4));

	mainmenu[1].setFont(font);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("instracture");
	mainmenu[1].setCharacterSize(48);
	mainmenu[1].setPosition(Vector2f(width / 3, (hight / 4) +100));
	
	mainmenu[2].setFont(font);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("EXIT");
	mainmenu[2].setCharacterSize(48);
	mainmenu[2].setPosition(Vector2f(width / 3, (hight / 4) + 200));

	selected = 0;

}

void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainmenu[i]);
	}
}

void MainMenu::moveup()
{
	if (selected - 1 >= -1) {
		mainmenu[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1) {
			selected = 2;
		}
		mainmenu[selected].setFillColor(Color::Yellow);
	}
}

void MainMenu::movedown()
{
	if (selected + 1 <= 3) {
		mainmenu[selected].setFillColor(Color::White);
		selected++;
		if (selected == 3) {
			selected = 0;
		}
		mainmenu[selected].setFillColor(Color::Yellow);
	}
}

void MainMenu::setselected(int n)
{
	selected = n;
}

MainMenu::~MainMenu()
{
}
