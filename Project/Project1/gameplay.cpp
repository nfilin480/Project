#include <iostream>
#include <cmath>

#include "player.h"
#include "header.h"

int startgame(RenderWindow &window)
{
	setlocale(LC_ALL, "RUSSIAN");
	/*Карта*/
	Sprite ground;
	Texture g;
	g.loadFromFile("sprites/ground_2.png");
	ground.setTexture(g);

	/*Фон*/
	Sprite background;
	Texture b;
	b.loadFromFile("sprites/BG.png");
	background.setTexture(b);

	/*Стрелы лучника*/
	Sprite arrow;
	Texture arrows;
	arrows.loadFromFile("sprites/arrow.png");
	arrow.setTexture(arrows);

	/*Мечник*/
	Texture w;
	w.loadFromFile("sprites/warrior.png");

	/*Лучник*/
	Texture a;
	a.loadFromFile("sprites/archer.png");

	/*Герой*/
	Texture t;
	t.loadFromFile("sprites/ninja.png");

	PLAYER p(t, a, w);
	p.onGround = false;

	Clock clock;

	while (window.isOpen())
	{
		/*Задание времени*/
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;

		if (time > 20) time = 20;

		/*Проверка на то, жив ли персонаж*/
		if (p.alive == false) {
			if (p.currentFrame > 9) {
				return 1;
			}
		}

		Event event;

		/*Закрытие окна*/
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		/*Движение влево*/
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.15;

		}

		/*Движение вправо*/
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.15;
		}

		/*Прыжок*/
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -0.3; p.onGround = false; }
		}

		/*Атака*/
		if (Mouse::isButtonPressed(Mouse::Left) && p.attack == 0) {
			p.attack = 1;
			p.currentFrame = 0;

		}

		/*Обновление координат героя*/
		p.update(time);

		/*Победа, герой дошел до финиша*/
		if (p.rect.left > 5600) return 3;

		/*Пауза*/
		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			
			while (Keyboard::isKeyPressed(Keyboard::Escape)) {

			}

			int helper = pause_menu(window);

			while (Keyboard::isKeyPressed(Keyboard::Escape)) {

			}

			if (helper == 1) {
				return 2;
			}
		}

		

		/*Сдвиг камеры*/
		if (p.rect.left > 640) p.offsetX = p.rect.left - 640; 

		/*Отрисовка фона, карты*/
		window.clear(Color::White);
		ground.setPosition(-p.offsetX, 0);
		window.draw(background);
		window.draw(ground);

		/*Отрисовка лучников*/
        for (int j = 0; j < (int)place_archers.size();j++) {
			p.enemy_archer(time, j);
			window.draw(p.archer);

			/*Отрисовка стрел лучника*/
			if (p.index_arrows.size() > 0) {
                for (int i = 0;i < (int)p.index_arrows.size();i++) {
					/*Задание значений*/
					arrow.setPosition((p.index_arrows[i].left += p.dx_arrows[i]) - p.offsetX, (p.index_arrows[i].top += p.dy_arrows[i]));
					arrow.setRotation(atan(p.angle[i]) * 180.0 / 3.14 + 270);
					/*Попадание стрелы в героя*/
					if (int((p.index_arrows[i].left + 16) / 32) == int((p.rect.left + 16) / 32) && int((p.index_arrows[i].top + 8) / 32) == int((p.rect.top + 16) / 32)) p.alive = false;
					if (int((p.index_arrows[i].left + 16) / 32) == int((p.rect.left + 16) / 32) && int((p.index_arrows[i].top + 8) / 32) == int((p.rect.top + 48) / 32)) p.alive = false;

					/*Удаление стрел из вектора, которые вышли за карту*/
					if (p.index_arrows[i].top > 720) {
						auto it = p.index_arrows.begin();
						for(int g = 0; g < i;g++)
							*it++;
						p.index_arrows.erase(it);
						auto it_1 = p.dx_arrows.begin();
						for (int g = 0; g < i;g++)
							*it_1++;
						p.dx_arrows.erase(it_1);
						auto it_2 = p.dy_arrows.begin();
						for (int g = 0; g < i;g++)
							*it_2++;
						p.dy_arrows.erase(it_2);
						auto it_3 = p.angle.begin();
						for (int g = 0; g < i;g++)
							* it_3++;
						p.angle.erase(it_3);
					}
					/*Отрисовка стрелы*/
					window.draw(arrow);
				}
			}
		}

		/*Отрисовка мечников*/
		for (int j = 0; j < (int)place_warriors.size();j++) {
			if ((p.rect.left - place_warriors[j].left) < 640 && (p.warrior_alive[j] != 2)) {
				/*Задание анимации и положения на экране*/
				p.enemy_warrior(time, j);
				p.warrior.setPosition(place_warriors[j].left - p.offsetX + p.offset_warrior[j], place_warriors[j].top);

				/*Отрисовка*/
				window.draw(p.warrior);

			}
		}

		/*Отрисовка героя и обновление экрана*/
		window.draw(p.hero);
		window.display();
	}
	return -1;

}