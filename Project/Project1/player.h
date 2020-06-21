#ifndef PLAYER_H
#define PLAYER_H

#include "global_vars.h"

class PLAYER {

public:

	Sprite hero;
	Sprite archer;
	Sprite warrior;

	/*Переменные героя*/
	float dx, dy;				//Скорость по x и y
	FloatRect rect;				//Координаты героя
	bool onGround;				//Его нахождение на карте(на платформе или нет)
	float currentFrame;			//Кадр анимации героя
	int attack;					//Была ли нажата кнопка для атаки
	bool right = true;			//Последнее нажатие клавиши, право или лево
	bool alive = true;			//Статус героя(жив/мертв)
	float offsetX = 0;			//Сдвиг карты


	vector<float> frame_archer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};			//Кадр анимации мечника
	vector<float> dx_arrows;												//Скорость стрелы по х
	vector<float> dy_arrows;												//Скорость стрелы по y
	vector<FloatRect> index_arrows;											//Координаты стрел
	vector<float> angle;													//Угол, под которым летит стрела


	vector<int> warrior_alive = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};								//Статус мечника(нужно ли его отрисовывать)								
	vector<float> dx_warrior = { 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};	//Его скорость
	vector<float> offset_warrior = { 0 , 0, 0, 0, 0, 0, 0, 0 ,0 ,0};							//Нахождение мечника, относительно его позиции
	vector<float> max_offset_warrior = {64, 80, 64, 128 ,80, 96, 112, 112, 112, 112};			//Максимальный его размах ходьбы
	vector<float> frame_warrior = { 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};								//Кадр анимации мечника

	PLAYER(Texture& image, Texture& a, Texture& w)
	{
		/*Задание значений*/
		hero.setTexture(image);
		rect = FloatRect(32, 32, 32, 64);
		archer.setTexture(a);
		warrior.setTexture(w);
		dx = dy = 0.1;
		currentFrame = 0;
		attack = 0;
	}


	void update(float time)
	{
		/*Движение персонажа по x и вызов проверки постановки на платформе по x*/
		rect.left += dx * time;
		Collision(0);

		/*Придание герою скорости по y*/
		if (!onGround) {
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		onGround = false;

		/*Проверка на постановку на платформе по y*/
		Collision(1);

		/*Обновление кадра анимации*/
		currentFrame += 0.01 * time;
		if (currentFrame > 10) {
			currentFrame -= 10;
			if (attack == 1) attack = 0;
		}
		/*Анимация ходьбы вправо*/
		if (dx > 0) {
			hero.setTextureRect(IntRect(32 * int(currentFrame), 64, 32, 64));
			right = true;
		}
		/*Анимация ходьбы влево*/
		if (dx < 0) {
			hero.setTextureRect(IntRect(32 * int(currentFrame) + 32, 64, -32, 64));
			right = false;
		}
		/*Анимация постановки на месте*/
		if (dx == 0) {
			if(right)
				hero.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 64)); 
			else
				hero.setTextureRect(IntRect(32 * int(currentFrame) + 32, 0, -32, 64));
		}
		/*Анимация прыжка вправо*/
		if (dy < 0 && dx > 0) {
			hero.setTextureRect(IntRect(32 * int(currentFrame), 128, 32, 64));
			right = true;
		}
		/*Анимация прыжка влево*/
		if (dy < 0 && dx < 0) {
			hero.setTextureRect(IntRect(32 * int(currentFrame) + 32, 128, -32, 64));
			right = false;
		}

		/*Анимация атаки*/
		if (attack == 1) {
			int frame = 32;
			int helper = 0;
			if (int(currentFrame) > 2 && int(currentFrame) < 8) frame = 48;
			if (int(currentFrame) > 2) helper = (int(currentFrame) - 3) * 16;
			if (right) hero.setTextureRect(IntRect(32 * int(currentFrame) + helper, 256, frame, 64));
			if (!right) hero.setTextureRect(IntRect(32 * int(currentFrame) + helper + frame, 256, -frame, 64));
			if (dy < 0 && right == true) hero.setTextureRect(IntRect(32 * int(currentFrame) + helper, 320, frame, 64));
			if (dy < 0 && right != true) hero.setTextureRect(IntRect(32 * int(currentFrame) + helper + frame, 320, -frame, 64));

			/*Проверка на убийство мечника*/
			Collision_enemy(time, 0);
		}

		/*Анимация смерти*/
		if (alive == false) {
			currentFrame -= 0.008 * time;
			hero.setTextureRect(IntRect(32 * int(currentFrame), 192, 32, 64));
		}

		/*Задание координат*/
		hero.setPosition(rect.left - offsetX, rect.top);

		dx = 0;
	}



	void Collision(int dir)
	{
		/*Для каждой клетки, в которой есть герой*/
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			{
				/*Выход за границы карты*/
				if (j < 0 || i > 22) {
					alive = false;
					return;
				}

				/*Если герой в текстуре, то он выходит из нее*/
				if (m[i][j] == 1)
				{
					if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx < 0) && (dir == 0)) rect.left = j * 32 + rect.width;
					if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				/*Персонаж на нижней границы карты*/
				if (m[i][j] == g) {
					alive = false;
					return;
				}

			}
	}

	void Collision_enemy(float time, int dir) {
		/*Для каждой клетки, в которой стоит герой*/
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
				/*Проверяется каждый мечник*/
				for (int k = 0; k < (int)place_warriors.size();k++)
					if (j == (int)((place_warriors[k].left + offset_warrior[k]) / 32) && (int)((place_warriors[k].top) / 32 == i) && warrior_alive[k] != 2)
						if (dir == 0) {
							warrior_alive[k] = 1;
							frame_warrior[k] = 0;
						}
						else
							alive = false;

	}

	void enemy_archer(float time, int i) {


		int flag = 0;
		frame_archer[i] += 0.003 * time;
		if (frame_archer[i] >= 10) {
			frame_archer[i] -= 10;
			flag = 1;
		}

		/*Анимация стрельбы лучника влево*/
		if (abs(place_archers[i].left - rect.left) < 320 && place_archers[i].left - rect.left > 0) {
			if ((frame_archer[i] + 0.003 * time) > 10) flag = 2;
			archer.setTextureRect(IntRect(32 * int(frame_archer[i]), 64, 32, 64));
		}

		/*Анимация стрельбы вправо*/
		if (abs(place_archers[i].left - rect.left) < 320 && place_archers[i].left - rect.left < 0) {
			if ((frame_archer[i] + 0.003 * time) > 10) flag = 2;
			archer.setTextureRect(IntRect(32 * int(frame_archer[i]) + 32, 64, -32, 64));
		}

		/*Анимация на месте*/
		if (abs(place_archers[i].left - rect.left) > 320) archer.setTextureRect(IntRect(32 * int(frame_archer[i]), 0, 32, 64));
		archer.setPosition(place_archers[i].left - offsetX, place_archers[i].top);

		/*Если кадр анимации дошел до последнего, то спавнится стрела*/
		if (flag == 2) {
			index_arrows.push_back(FloatRect(place_archers[i].left, place_archers[i].top, 32, 16));			/*Задание начальных координат стрелы*/
			dx_arrows.push_back((rect.left / 32 - place_archers[i].left / 32) * 1 * 0.002);					/*Задание скорости по х*/
			dy_arrows.push_back((rect.top / 32 - place_archers[i].top / 32) * 1 * 0.002);					/*Задание скорости по y*/
			angle.push_back((place_archers[i].left - rect.left) / (rect.top - place_archers[i].top));		/*Задание угла, под которым летит стрела*/
		}

	}

	void enemy_warrior(float time, int i) {

		frame_warrior[i] += 0.0065 * time;

		int attack_flag = 0;

		/*Анимация смерти мечника закончилась*/
		if (warrior_alive[i] == 1 && frame_warrior[i] > 9) {
			warrior_alive[i] = 2;
			return;
		}
		if (frame_warrior[i] > 10) {
			frame_warrior[i] -= 10;
		}

		/*Анимация смерти*/
		if (warrior_alive[i] == 1) {
			warrior.setTextureRect(IntRect(32 * int(frame_warrior[i]), 192, 32, 64));
			return;
		}

		/*Анимация атаки влево*/
		if (abs(place_warriors[i].left - rect.left + offset_warrior[i]) < 32 && (place_warriors[i].left - rect.left) > 0) {
			warrior.setTextureRect(IntRect(32 * int(frame_warrior[i]), 64, 32, 64));
			attack_flag = 1;
			Collision_enemy(time, 1);
		}

		/*Анимация атаки вправо*/
		if (abs(place_warriors[i].left - rect.left + offset_warrior[i]) < 32 && (place_warriors[i].left - rect.left) < 0) {
			warrior.setTextureRect(IntRect(32 * int(frame_warrior[i]) + 32, 64, -32, 64));
			attack_flag = 1;
			Collision_enemy(time, 1);
		}

		/*Анимация ходьбы*/
		if (abs(place_warriors[i].left - rect.left) > 30 && attack_flag == 0) {
			if (abs(offset_warrior[i] + dx_warrior[i] * time) > max_offset_warrior[i])
				dx_warrior[i] *= -1;
			offset_warrior[i] += dx_warrior[i] * time;

			if (dx_warrior[i] < 0) warrior.setTextureRect(IntRect(32 * int(frame_warrior[i]), 0, 32, 64));
			else
				warrior.setTextureRect(IntRect(32 * int(frame_warrior[i]) + 32, 0, -32, 64));
		}

	}
};

#endif // PLAYER_H
