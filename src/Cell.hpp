#ifndef CELL_HPP
#define CELL_HPP

#include "Game_Object.hpp"
#include <iostream>
#include <string>

class Cell :
    public Game_Object 
{
    friend class Board;
public:
    Cell(const unsigned int row, const unsigned int col);
    Cell operator++();
    Cell operator++(int);

    void set_position(sf::Vector2f position) override;
    void set_size(sf::Vector2f size) override;
    void set_color(sf::Color color) override;
    void on_click_left() override;
    void on_click_right() override;
    void draw_object(sf::RenderWindow &window, sf::Texture& texture) override;
    void set_mines_in_neighborhood (int mine_count);
    int get_mines_in_neighborhood()const;

    void set_mine();
    const bool has_mine() const;
    const unsigned int get_row();
    const unsigned int get_col();
    
    sf::RectangleShape& get_rectangle() override;
    enum class State{
        Unrevealed,
        Revealed,
        Flagged,
    };
    State get_state();
private:
    State state = State::Unrevealed;
    bool mine = false;
    const unsigned int row;
    const unsigned int col;
    int mines_in_neighborhood = 0;
};

#endif

