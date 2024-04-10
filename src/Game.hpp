#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "Board.hpp"
#include "Menu.hpp"


class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode video_mode;

	sf::Vector2i mouse_position_window;
	sf::Vector2f mouse_position_view;
	
	Board *board;
	Game_Object *object;
	Menu menu;

	bool mouse_held;
	bool game_over=0;
	bool win;
	bool first_turn = 1;

	void update_game_state();
	void end_game(bool win);

	void init_variables();
	void init_window();
	void get_mouse_position();
	void update_objects();
	void update_object(Game_Object& object);
	void reset_game();
	void switch_board_stat();


public:
	Game();
	~Game();


	const bool is_window_open();
	void update_Event();
	void update();
	void render();

};

#endif

