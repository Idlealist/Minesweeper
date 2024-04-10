#ifndef MENU_HPP
#define MENU_HPP

#include "Menu_Button.hpp"

class Flag_Counter {
	friend class Menu;

public:
	void set_flags_left(int flags_placed);
private:
	Flag_Counter();
	int flags_remainig()const;

	std::vector <sf::RectangleShape> shape;
	int total_flags=0;
	int flags_placed = 0;
	sf::Texture texture_1, texture_2;
};

class Menu
{
	friend class Game;
public:
	void init_menu(sf::RenderWindow &window);
	void draw_menu(sf::RenderWindow &window);
	void update_menu();
private:
	enum class Current_board{ new_Beginner, new_Intermediate, new_Advanced, cur_Begginer, cur_Intermediate, cur_Advanced, already_present, none};
	sf::RectangleShape menu_shape;
	std::vector<Menu_Button> buttons;
	float padding_scale = 0.05f;
	sf::Texture texture;
	Flag_Counter flag_counter;
	Current_board current_board = Current_board::none;
};



#endif


