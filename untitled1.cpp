#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
using namespace sf;

float screen_x = 1280;
float screen_y = 720;
int framerate = 60;

int stupid_variable = 1; // ensures that evaluation at input handling will equal true the first time spacebar is pressed
						// (should probably be changed asap)
class Player
{
public:
	float spd_mod = 8;
	Vector2f pos;
	Vector2f spd;
	
	void UpdatePos()
	{
		if (spd.x != 0.f && spd.y != 0.f)
		{
			spd.x /= sqrt(2.f);
			spd.y /= sqrt(2.f);
		}

		pos.x += spd.x;
		pos.y += spd.y;
	}
};

class Bullet
{
public:
	Vector2f pos = { 0,0 };
	Vector2f spd;
	bool isActive = false;

	vector<Bullet> bullets;

	void SetSpeed(Vector2f p_pos, Vector2i m_pos, float spd_const)
	{
		spd.x = (spd_const * (m_pos.x - p_pos.x)) / sqrtf(((pow((m_pos.x - p_pos.x), 2)) + (pow((m_pos.y - p_pos.y), 2))));
		spd.y = (spd_const * (m_pos.y - p_pos.y)) / sqrtf(((pow((m_pos.x - p_pos.x), 2)) + (pow((m_pos.y - p_pos.y), 2))));
	}

	void UpdatePos()
	{
		pos.x += spd.x;
		pos.y += spd.y;
	}

	void DeleteBullet()
	{

	}
};

class Enemy
{
public:

};

int main()
{
	
	Player player;
	player.pos.x = screen_x/2;
	player.pos.y = screen_y/2;
	player.spd.x = 0;
	player.spd.y = 0;

	vector<Bullet> bullets;
	bullets.push_back(Bullet()); // for safety
	
	vector<RectangleShape> bullet_sprites;
	bullet_sprites.push_back(RectangleShape());

	Time time;

	RenderWindow window(VideoMode(screen_x, screen_y), "UNTITLED");
	window.setFramerateLimit(framerate);
	window.setMouseCursorVisible(false);
	Clock clock;
	RectangleShape crosshair(Vector2f(10, 10));
	crosshair.setFillColor(Color::Red);

	RectangleShape player_sprite(Vector2f(20, 8));
	player_sprite.setFillColor(Color::Green);

	RectangleShape bullet_sprite(Vector2f(5, 5));
    bullet_sprite.setFillColor(Color::Yellow);

	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		
		Vector2i mouse_pos = Mouse::getPosition(window);
		crosshair.setPosition(mouse_pos.x,mouse_pos.y);

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.spd.y = -player.spd_mod;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.spd.y = player.spd_mod;
		
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.spd.x = -player.spd_mod;
			
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.spd.x = player.spd_mod;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space) && ((clock.getElapsedTime().asSeconds() > 0.25) || stupid_variable > 0))
		{
			bullets.push_back(Bullet());
			bullets[bullets.size()-1].isActive = true;
			bullets[bullets.size() - 1].pos = player.pos;
			bullets[bullets.size()-1].SetSpeed(player.pos, mouse_pos, 20);
			bullet_sprites.push_back(RectangleShape(Vector2f(5, 5)));
			bullet_sprites[bullet_sprites.size()-1].setFillColor(Color::Yellow);
			clock.restart();
			stupid_variable -= 1;
		}

	
		player.UpdatePos();
		player_sprite.setPosition(player.pos.x, player.pos.y);
		player.spd.x = 0;
		player.spd.y = 0;
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].UpdatePos();
		}

		window.clear();
		window.draw(player_sprite);
		window.draw(crosshair);
		for (int i = 0; i < bullets.size(); i++)
		{
			bullet_sprites[i].setPosition(bullets[i].pos.x, bullets[i].pos.y);
			window.draw(bullet_sprites[i]);
		}
		window.display();

	}
	return 0;
}