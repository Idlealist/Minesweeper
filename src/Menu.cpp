#include "Menu.hpp"
#include <iostream>

void Menu::init_menu(sf::RenderWindow& window)
{
	menu_shape.setFillColor(sf::Color(117, 113, 94));

	try {
		if (!this->texture.loadFromFile("Resources/Diffculty_button_96x32.png"))
		{
			throw 12;
		}
	}
	catch (...) {
		std::cout << "Could not load a texture from \"Resources/Difficulty_button_96x32.png\" \n";
		exit(5);
	}
	Menu_Button button;
	button.get_rectangle().setTexture(&texture);
	button.get_rectangle().setTextureRect(sf::IntRect(0, 32, 96, 32));
	buttons.push_back(button);
	buttons.push_back(Menu_Button(button));
	buttons.push_back(Menu_Button(button));
}

void Menu::draw_menu(sf::RenderWindow& window)
{
	sf::Vector2f menu_size(window.getSize());
	sf::Vector2f menu_position;
	menu_size.x *= 0.25f;
	float padding_x = menu_size.x * padding_scale;
	float padding_y = menu_size.y * padding_scale;
	menu_size.x -= padding_x;
	menu_size.y -= 2*padding_y;
	menu_position = sf::Vector2f(padding_x, padding_y);
	menu_shape.setSize(menu_size);
	menu_shape.setPosition(menu_position);
	window.draw(this->menu_shape);
	for (size_t i = 0; i < buttons.size(); i++) {
		buttons[i].get_rectangle().setSize(sf::Vector2f(menu_size.x, menu_size.y / 9.0f));
		buttons[i].get_rectangle().setPosition (sf::Vector2f(menu_position.x, 
												1.40f*i* buttons[i].get_rectangle().getSize().y+menu_position.y));

		buttons[i].get_rectangle().setTextureRect(sf::IntRect(0 ,i*32, 96, 32));
		window.draw(buttons[i].get_rectangle());
	}

	for (size_t i = 0; i < flag_counter.shape.size(); i++) {
		flag_counter.shape[i].setSize(sf::Vector2f(menu_size.x / 3.0f, buttons[0].get_rectangle().getSize().y));
		flag_counter.shape[i].setPosition(sf::Vector2f(menu_position.x + i * flag_counter.shape[i].getSize().x,
														7.0f * flag_counter.shape[i].getSize().y + menu_position.y));
		switch (i)
		{
		case 0:
			flag_counter.shape[i].setTextureRect(sf::IntRect(0, 0, 16, 16));
			break;
		case 1:
			flag_counter.shape[i].setTextureRect(
					sf::IntRect((flag_counter.flags_remainig() / 10) * 16,0 , 16, 16));
			break;
		case 2:
			flag_counter.shape[i].setTextureRect(
				   sf::IntRect((flag_counter.flags_remainig() % 10) * 16, 0, 16, 16));
			break;
		default:
			break;
		}
		window.draw(flag_counter.shape[i]);
		
	}
	
}

void Menu::update_menu()
{
	for (size_t i = 0; i < buttons.size(); i++ ) {
		if (buttons[i].clicked) {
			buttons[i].clicked = false;
			switch (i)
			{
			case 0:
				current_board = Current_board::new_Beginner;
				flag_counter.total_flags = 10;
				break;
			case 1:
				current_board = Current_board::new_Intermediate;
				flag_counter.total_flags = 40;
				break;
			case 2:
				current_board = Current_board::new_Advanced;
				flag_counter.total_flags = 99;
				break;
			default:
				break;
			}
		}
	}

}


void Flag_Counter::set_flags_left(int flags_placed)
{
	this->flags_placed = flags_placed;
}

Flag_Counter::Flag_Counter()
{
	

	try {
		if (!texture_1.loadFromFile("Resources/Tiles_textures_16_test.png"))
		{
			throw 12;
		}
	}
	catch (...) {
		std::cout << "Could not load a texture from \"Tiles_textures_16_test.png\" \n";
		exit(6);
	}

	try {
		if (!texture_2.loadFromFile("Resources/numbers_16.png"))
		{
			throw 12;
		}
	}
	catch (...) {
		std::cout << "Could not load a texture from \"Resources/numbers_16.png\" \n";
		exit(6);
	}

	sf::RectangleShape a;
	a.setTexture(&texture_1);
	shape.push_back(a);
	a.setTexture(&texture_2);
	shape.push_back(a);
	shape.push_back(a);
}

int Flag_Counter::flags_remainig() const
{
	return this->total_flags-flags_placed;
}

