#include<iostream>
#include"SFML/Graphics.hpp"
#include"MainMenu.h"
#include <ctime>
#include<cstdlib>

using namespace std;
using namespace sf;

void playername(RenderWindow& window, string& name);
void game_play(RenderWindow& window);
void instruction(RenderWindow& window);

int pagenum = 1000;

int main() {
	RenderWindow window(sf::VideoMode(600, 800), "flappy bird");
	MainMenu menu(600, 800);
	string name;
	
	Texture background;
	background.loadFromFile("background-day.png");
	Sprite bg;
	bg.setTexture(background);
	bg.setScale(Vector2f(2.1f, 1.6f));


	while (true) {

		if (pagenum == 1000) {

			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{

					if (event.type == Event::Closed)
					{
						window.close();
					}
					if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Up)
							menu.moveup();
						if (event.key.code == Keyboard::Down)
							menu.movedown();
						if (event.key.code == Keyboard::Enter)
						{
							if (menu.pressed() == 0) // play
								pagenum = 0;
							if (menu.pressed() == 1) // instraction
								pagenum = 1;
							if (menu.pressed() == 2) // exit
								pagenum = -1;
						}
					}
				}

				window.clear();
				if (pagenum != 1000)
					break;
				window.draw(bg);
				menu.draw(window);
				window.display();
			}
			if (pagenum == -1) //exit
			{
				window.close();
				break;
			}
			if (pagenum == 0) // play
			{
				playername(window, name);
			}
			if (pagenum == 3)
				game_play(window);
			if (pagenum == 1)
				instruction(window);
		}
	}


}


void game_play(RenderWindow& window) {
	
	

	int health = 10, score = 0;
	float gravity = 0.03;
	float curent_pose = 0, enimy_pose = 0, fire_pose = 0 , portal_pose = 0 , atack_pose = 0;
	bool enimytoutch = false, gameover = false, enimy_pass = false , repound = false;
	bool cantpresskey = false, drawthunder = false, touch_thunder = false, enimy_atack = false;

	View view(FloatRect(0, 0, 600, 800));

	Clock clock;

	Text pointtx;
	Font point;
	point.loadFromFile("Roboto-Bold.ttf");
	pointtx.setFont(point);
	pointtx.setFillColor(Color::Black);
	pointtx.setString(to_string(score));
	pointtx.setCharacterSize(70);
	pointtx.setPosition(Vector2f(280.f, 50.f));

	Texture background;
	background.loadFromFile("background-day.png");
	Sprite bg;
	bg.setTexture(background);
	bg.setScale(Vector2f(2.1f, 1.6f));

	Texture groundtx;
	groundtx.loadFromFile("ground.png");
	Sprite ground;
	ground.setTexture(groundtx);
	ground.setScale(Vector2f(2.f, 1.f));
	ground.setPosition(Vector2f(0.f, 700.f));

	Texture playerTex;
	playerTex.loadFromFile("player.png");
	Sprite player;
	player.setTexture(playerTex);
	player.setScale(Vector2f(1.5f, 1.5f));
	player.setPosition(150, 400);
	player.setTextureRect(IntRect(0, 0, 24, 24));

	Texture teleportTex;
	teleportTex.loadFromFile("Thunder projectile1 w blur.png");
	Sprite teleport;
	teleport.setTexture(teleportTex);
	teleport.setScale(Vector2f(3.f, 3.f));
	teleport.setPosition(220, 0);
	teleport.setTextureRect(IntRect(0, 0, 31, 32));
	teleport.setRotation(90);

	Texture enimytex[6];
	Sprite enimy[6];
	Texture enimyattex[6];
	Sprite enimyatack[6];
	for (int i = 0; i < 6; i++)
	{
		int n = rand() % 600 + 150;
		if (n >= n + 10)
		{
			n = rand() % 600 + 150;
		}
		enimytex[i].loadFromFile("enimy.png");
		enimy[i].setTexture(enimytex[i]);
		enimy[i].setScale(Vector2f(2.f, 2.f));
		enimy[i].setPosition(700, n);
		enimy[i].setTextureRect(IntRect(0, 0, 40, 30));
		enimyattex[i].loadFromFile("enimyfight.png");
		enimyatack[i].setTexture(enimyattex[i]);
		enimyatack[i].setScale(Vector2f(2.f, 2.f));
		enimyatack[i].setPosition(700, n);
		enimyatack[i].setTextureRect(IntRect(0, 0, 40, 30));
	}

	/*Texture enimyattex[6];
	Sprite enimyatack[6];
	for (int i = 0; i < 6; i++)
	{
		enimyattex[i].loadFromFile("enimyfight.png");
		enimyatack[i].setTexture(enimyattex[i]);
		enimyatack[i].setScale(Vector2f(2.f, 2.f));
		enimyatack[i].setPosition(700, enimy_position_y);
		enimyatack[i].setTextureRect(IntRect(0, 0, 42, 33));
	}*/

	Font font;
	font.loadFromFile("Roboto-Bold.ttf");
	Text lose_ms;
	lose_ms.setFont(font);
	lose_ms.setString("GAME OVER");
	lose_ms.setCharacterSize(70);
	lose_ms.setFillColor(Color::Black);
	lose_ms.setPosition(100, 350);

	while (window.isOpen()) {
		
		srand(time(0));
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 650;

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (time > 20)
		{
			time = 20;
		}

		if (gameover == false) {

			////////////////// ground motion.
			ground.move(-0.07 * time, 0);
			if (ground.getPosition().x + 600 <= 0 && ground.getPosition().x + 600 >= -100)
			{
				ground.setPosition(Vector2f(0.f, 700.f));
			}

			///////////////// enimy motion.
			for (int i = 0; i < 6; i++)
			{
				int w = rand() % 5 + 1;
				if (w >= w + i)
				{
					w = rand() %  + 1;
				}
				enimy[i].move(-w * time * 0.02, 0);
				enimyatack[i].move(-w * time * 0.02, 0);
			}

			//////////////////// player movment.
			if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) && cantpresskey == false)
			{
				curent_pose += 0.005 * time;
				gravity = -0.04;
				player.move(0, gravity * time);
				player.setRotation(-15.f);
			}
			else if (cantpresskey == false)
			{
				gravity = 0.03;
				curent_pose = 0;
				player.move(0, gravity * time);
				player.setRotation(15.f);
			}

			///////////////// enimy attak.
			for (int i = 0; i < 6; i++)
			{
				if (enimy[i].getPosition().x >= 240 && enimy[i].getPosition().x <= 245)
				{
					enimy_atack = true;
				}
				else if ((player.getGlobalBounds().intersects(enimyatack[i].getGlobalBounds()) || player.getGlobalBounds().intersects(enimy[i].getGlobalBounds())) && enimytoutch == false)
				{
						enimytoutch = true;
						health = 0;
						//cout << health << endl;
				}
				else if (enimy[i].getPosition().x < 50) {
					enimy_atack = false;
					enimytoutch = false;
				}

				////////////////////// points gain.
				if (player.getPosition().x >= enimy[i].getPosition().x && enimy_pass == false)
				{
					if (player.getGlobalBounds().intersects(enimyatack[i].getGlobalBounds()))
					{
						score = score;
					}
					else {
						score++;
						enimy_pass = true;
						//cout << score << endl;
					}
				}
				/////////////////////// enimy reset to begining.
				for (int i = 0; i < 6; i++) {
					if (enimy[i].getPosition().x <= -90 && enimy[i].getPosition().x >= -150)
					{
						int n = rand() % 500 + 150;
						enimy[i].setPosition(700, n);
						enimyatack[i].setPosition(700, n);
						enimy_pass = false;
					}
				}
			}

			///////////////// point lose.
			if (player.getGlobalBounds().intersects(teleport.getGlobalBounds()))
			{
				if (player.getPosition().y >= 106 && player.getPosition().y <= 108 && repound == false)
				{
					health -= 1;
					repound = true;
					cout << health << endl;
				}

				else if (player.getPosition().y >= 109 && player.getPosition().y <= 700)
				{
					repound = false;
				}

				player.setPosition(Vector2f(150, teleport.getPosition().y + 80));
				drawthunder = true;
				cantpresskey = true;
				float speed = 0.1;
				teleport.move(0, speed);
				player.move(0, speed);
				player.setRotation(15);
				curent_pose = 0;

				if (teleport.getPosition().y > 400) {
					drawthunder = false;
					teleport.setPosition(Vector2f(220.f, 0.f));
					cantpresskey = false;
				}
			}


			
			////////////////// motion.
			///////////// player.
			if (curent_pose > 3)
			{
				curent_pose -= 3;
			}
			player.setTextureRect(IntRect(34 * int(curent_pose), 0, 34, 24));

			///////////// enimy.
			if (enimy_pose > 8)
			{
				enimy_pose -= 8;
			}
			enimy_pose += 0.005 * time;

			if (atack_pose > 8)
			{
				atack_pose -= 8;
			}
			atack_pose += 0.005 * time;

			for (int i = 0; i < 6; i++)
			{
				enimy[i].setTextureRect(IntRect(42 * int(enimy_pose), 0, 42, 33));
				enimyatack[i].setTextureRect(IntRect(42 * int(atack_pose), 0, 42, 33));
			}
			

			
			

			///////////// teleport.
			if (portal_pose > 5)
			{
				portal_pose -= 5;
			}
			portal_pose += 0.01 * time;
			teleport.setTextureRect(IntRect(32 * int(portal_pose), 0, 31, 32));

			/////////////////// score string.
			pointtx.setString(to_string(score));

			///////////// lose.
			if (health <= 0 || player.getGlobalBounds().intersects(ground.getGlobalBounds()))
				gameover = true;

			/////////////////// draw.
			window.clear();
			window.draw(bg);
			window.draw(player);
			if (enimy_atack == true)
			{
				for (int i = 0; i < 6; i++)
				{
					window.draw(enimyatack[i]);
				}
			}
			else
			{
				for (int i = 0; i < 6; i++)
				{
					window.draw(enimy[i]);
				}
			}
			window.draw(ground);
			if (drawthunder == true) {
				window.draw(teleport);
			}
			window.draw(pointtx);
			window.display();


		}
		else
		{
			gravity = 0;
			curent_pose = 0;
			player.move(0.f, gravity * time);
			player.setRotation(15.f);

			player.setTextureRect(IntRect(34 * int(curent_pose), 0, 34, 24));

			window.clear();
			window.draw(bg);
			window.draw(player);
			for(int i = 0; i < 6; i++)
			{
				window.draw(enimy[i]);
			}
			window.draw(lose_ms);
			window.draw(ground);
			window.draw(pointtx);
			window.display();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pagenum = 1000;
			main();
		}
		
	}
}


void playername(RenderWindow& window, string& name) {
	if (!name.empty())
	{
		name.clear();
	}

	Texture background;
	background.loadFromFile("background-day.png");
	Sprite bg;
	bg.setTexture(background);
	bg.setScale(Vector2f(2.1f, 1.6f));
	
	Font font;
	font.loadFromFile("Roboto-Bold.ttf");
	Text t1, t2;
	t1.setFont(font);
	t2.setFont(font);
	t1.setString("Enter Your Name : ");
	t1.setCharacterSize(40);
	t2.setCharacterSize(40);
	t1.setPosition(10, 10);
	t2.setPosition(10, 100);
	t1.setFillColor(Color::Yellow);
	t2.setFillColor(Color::White);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::TextEntered)
			{
				name += static_cast<char>(event.text.unicode);
			}
			if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0)
			{
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter) && name.size() > 1)
			{
				pagenum = 3; // game window
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				pagenum = 1000; // game window
				return;
			}
		}
		t2.setString(name);
		window.clear();
		window.draw(bg);
		window.draw(t1);
		window.draw(t2);
		window.display();
	}
}

void instruction(RenderWindow& window) {
	pagenum = 100;
	Event event;
	Texture background;
	background.loadFromFile("background-day.png");
	Sprite bg;
	bg.setTexture(background);
	bg.setScale(Vector2f(2.1f, 1.6f));

	Font font;
	Text t1;
	font.loadFromFile("Roboto-Bold.ttf");
	t1.setFont(font);
	t1.setString("# Flappy Bird Adventure - Game Instructions\n\n"

		"## Objective:\n"
	    "Guide your bird through a treacherous sky, dodging flying\nenemies and staying aloft!\n\n"

		"## Controls :\n"
		"-**Space Key * *: Flap wings to move up.\n"
		"- **Up Arrow Key * *: Also flaps wings to move up.\n"
		"- **No Key Press * *: The bird will move down due to gravity.\n\n"

		"## How to Play :\n"
	    "1. Start the game by pressing the * *Space Key * *or\n**Up Arrow Key * *to make the bird take flight.\n"
		"2. Once in the air, navigate by pressing the** Space Key** or\n**Up Arrow Key * *to ascend.\nRelease the keys to let gravity pull the bird downward.\n"
		"3. Avoid the flying enemies that come your way.\nIf you touch an enemy, it's game over!\n"
		"4. The longer you survive without hitting an enemy,\nthe higher your score.\n\n"

		"## Tips:\n"
	    "-Timing is key!Learn the rhythm of your bird's flapping to\ncontrol your ascent and descent.\n"
		"- Keep an eye on the patterns of the enemies to find the best\npath through.\n"
		"- Practice makes perfect.The more you play, the better you'll\nget at anticipating and avoiding\nthe enemies.\n\n"

		"Good luck, and have fun!");
	t1.setCharacterSize(20);
	t1.setPosition(10, 10);
	t1.setFillColor(Color::Black);
	
	window.clear();
	window.draw(bg);
	window.draw(t1);
	window.display();
	while (window.isOpen())
	{
		if(Keyboard::isKeyPressed(Keyboard::Escape)) {
			pagenum = 1000;
			main();
		}
	}
}