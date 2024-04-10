#ifndef MENU_BUTTON
#define MENU_BUTTON

#include "Game_Object.hpp"

class Menu_Button :
    public Game_Object
{	
	friend class Menu;
public:
	Menu_Button();
	Menu_Button(sf::Vector2f postion, sf::Vector2f size);
	Menu_Button(const Menu_Button &other);
	void on_click_left() override;
	void on_click_right() override;
	void set_position(sf::Vector2f) override;
	void set_size(sf::Vector2f) override;
	void set_color(sf::Color) override;
	void draw_object(sf::RenderWindow& window, sf::Texture&) override;
	bool is_clicked()const;

private:
	sf::RectangleShape& get_rectangle() override;
	bool clicked=0;
};

#endif
