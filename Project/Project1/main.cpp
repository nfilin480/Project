#include <iostream>
#include "header.h"

/*Главное меню*/
void main_menu(RenderWindow& window);

/*Меню после смерти*/
void lose_menu(RenderWindow& window);

/*Меню паузы*/
int pause_menu(RenderWindow& window);

/*Меню победы*/
void win_menu(RenderWindow& window);

/*Статус меню*/
int flag = 0;

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Test!");

	while (window.isOpen()) {

		if (flag == 0) main_menu(window);

		if (flag == 1) lose_menu(window);

		if (flag == 2) startgame(window);

		if (flag == 3) win_menu(window);


	}
		
	return 0;
}

void main_menu(RenderWindow& window) {
	/*Загрузка готового меню, шрифта и создание текста с заданием позиций на экране*/
	Sprite menu;
	Texture m;
	m.loadFromFile("sprites/main_menu.png");
	menu.setTexture(m);

	Font font;
	font.loadFromFile("sprites/font.ttf");
	Text newgame("New game", font, 32);
	newgame.setPosition(576, 215);

	Text exit("Exit", font, 32);
	exit.setPosition(618, 395);

	/*Отрисовка меню*/
	while (window.isOpen()) {
		if (IntRect(576, 215, 100, 50).contains(Mouse::getPosition(window))) { newgame.setFillColor(Color::Blue); }
		else
			newgame.setFillColor(Color::White);
		if (IntRect(576, 215, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			flag = startgame(window);
			break;
		}
		if (IntRect(576, 395, 100, 50).contains(Mouse::getPosition(window))) { exit.setFillColor(Color::Blue); }
		else
			exit.setFillColor(Color::White);
		if (IntRect(618, 395, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
		}

		window.draw(menu);
		window.draw(newgame);
		window.draw(exit);
		window.display();

	}
}


void lose_menu(RenderWindow& window) {

	/*Загрузка готового меню, шрифта и создание текста с заданием позиций на экране*/
	Sprite game_menu;
	Texture g;
	g.loadFromFile("sprites/game_menu.png");
	game_menu.setTexture(g);
	game_menu.setPosition(500, 250);

	Font font;
	font.loadFromFile("sprites/font.ttf");

	Text restart("Restart game", font, 32);
	restart.setPosition(576, 283);

	Text quit("Quit", font, 32);
	quit.setPosition(620, 355);

	Text dead("You are dead :(", font, 40);
	dead.setPosition(520, 225);
	dead.setFillColor(Color::Red);

	bool gameMenu = true;

	/*Отрисовка меню*/
	while (gameMenu == true && window.isOpen()) {
		if (IntRect(576, 283, 210, 50).contains(Mouse::getPosition(window))) { restart.setFillColor(Color::Blue); }
		else
			restart.setFillColor(Color::White);
		if (IntRect(576, 283, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			flag = startgame(window);
			break;
		}
		if (IntRect(576, 365, 100, 50).contains(Mouse::getPosition(window))) { quit.setFillColor(Color::Blue); }
		else
			quit.setFillColor(Color::White);
		if (IntRect(576, 365, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			window.close();
		}

		window.draw(game_menu);
		window.draw(dead);
		window.draw(restart);
		window.draw(quit);
		window.display();
	}
}

int pause_menu(RenderWindow& window) {

	/*Загрузка готового меню, шрифта и создание текста с заданием позиций на экране*/
	Sprite pause_menu;
	Texture g;
	g.loadFromFile("sprites/pause_menu.png");
	pause_menu.setTexture(g);
	pause_menu.setPosition(500, 230);

	Font font;
	font.loadFromFile("sprites/font.ttf");

	Text resume("Resume", font, 32);
	resume.setPosition(610, 272);

	Text restart("Restart game", font, 32);
	restart.setPosition(576, 337);

	Text quit("Quit", font, 32);
	quit.setPosition(630, 405);

	Text pause("PAUSE", font, 64);
	pause.setPosition(580, 190);
	pause.setFillColor(Color::Red);

	bool gameMenu = true;

	/*Отрисовка меню*/
	while (gameMenu == true && window.isOpen()) {
		if (IntRect(610, 272, 100, 50).contains(Mouse::getPosition(window))) { resume.setFillColor(Color::Blue); }
		else
			resume.setFillColor(Color::White);
		if (IntRect(610, 272, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left) || (Keyboard::isKeyPressed(Keyboard::Escape))) {
			gameMenu = false;
			return 0;
		}
		if (IntRect(576, 337, 132, 50).contains(Mouse::getPosition(window))) { restart.setFillColor(Color::Blue); }
		else
			restart.setFillColor(Color::White);
		if (IntRect(576, 337, 132, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			flag = 2;
			return 1;
		}
		if (IntRect(630, 405, 90, 50).contains(Mouse::getPosition(window))) { quit.setFillColor(Color::Blue); }
		else
			quit.setFillColor(Color::White);
		if (IntRect(630, 405, 90, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			window.close();
		}

		window.draw(pause_menu);
		window.draw(pause);
		window.draw(resume);
		window.draw(restart);
		window.draw(quit);
		window.display();
	}
}

void win_menu(RenderWindow& window) {

	/*Загрузка готового меню, шрифта и создание текста с заданием позиций на экране*/
	Sprite game_menu;
	Texture g;
	g.loadFromFile("sprites/game_menu.png");
	game_menu.setTexture(g);
	game_menu.setPosition(500, 250);

	Font font;
	font.loadFromFile("sprites/font.ttf");

	Text restart("Restart game", font, 32);
	restart.setPosition(576, 283);

	Text quit("Quit", font, 32);
	quit.setPosition(620, 355);

	Text win("You are win!!!! :)", font, 40);
	win.setPosition(520, 225);
	win.setFillColor(Color::Red);

	Text cong("CONGRATULATIONS!!!", font, 70);
	cong.setPosition(390, 150);
	cong.setFillColor(Color::Yellow);

	bool gameMenu = true;

	/*Отрисовка меню*/
	while (gameMenu == true && window.isOpen()) {
		if (IntRect(576, 283, 210, 50).contains(Mouse::getPosition(window))) { restart.setFillColor(Color::Blue); }
		else
			restart.setFillColor(Color::White);
		if (IntRect(576, 283, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			flag = startgame(window);
			break;
		}
		if (IntRect(576, 365, 100, 50).contains(Mouse::getPosition(window))) { quit.setFillColor(Color::Blue); }
		else
			quit.setFillColor(Color::White);
		if (IntRect(576, 365, 100, 50).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) {
			gameMenu = false;
			window.close();
		}

		window.draw(game_menu);
		window.draw(cong);
		window.draw(win);
		window.draw(restart);
		window.draw(quit);
		window.display();
	}
}