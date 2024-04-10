#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>



class Game_Object
{
protected:
	sf::RectangleShape rectangle;
public:
	virtual void on_click_left()=0;
	virtual void on_click_right()=0;
	virtual void set_position(sf::Vector2f)=0;
	virtual void set_size(sf::Vector2f)=0;
	virtual void set_color(sf::Color) = 0;
	virtual void draw_object(sf::RenderWindow& window, sf::Texture&) = 0;
	virtual sf::RectangleShape& get_rectangle() = 0;
};

#endif
