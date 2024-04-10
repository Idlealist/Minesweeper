#include "Menu_Button.hpp"

Menu_Button::Menu_Button()
{
}

Menu_Button::Menu_Button(sf::Vector2f postion, sf::Vector2f size) {
	this->set_position(postion);
	this->set_size(size);
}

Menu_Button::Menu_Button(const Menu_Button &other){
	this->rectangle=other.rectangle;
}

void Menu_Button::on_click_left()
{
	clicked = true;
}

void Menu_Button::on_click_right()
{
}

void Menu_Button::set_position(sf::Vector2f position)
{
	this->rectangle.setPosition(position);
}

void Menu_Button::set_size(sf::Vector2f size)
{
	this->rectangle.setSize(size);
}

void Menu_Button::draw_object(sf::RenderWindow& window, sf::Texture&)
{
}

bool Menu_Button::is_clicked()const
{
	return this->clicked;
}

sf::RectangleShape& Menu_Button::get_rectangle()
{
	return this->rectangle;
}

void Menu_Button::set_color(sf::Color color)
{
	this->rectangle.setFillColor(color);
}