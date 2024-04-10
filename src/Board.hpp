#ifndef BOARD_HPP
#define BOARD_HPP
#include "Cell.hpp"

#include <vector>
#include <iostream>
#include <algorithm> 

class Board
{
	friend class Game;
public:
	Board(unsigned int width, unsigned int height, unsigned int mines_number);
	//~Board();

	void random_mine_placement(const unsigned int row, const unsigned int col);
	void draw_board(sf::RenderWindow &window);
	void draw_cells(sf::RenderWindow &window, sf::RectangleShape board_shape);
	int count_mines_in_neighborhood(const sf::Vector2i pos);
	void update_board();
	void reveal_neighbors(sf::Vector2i pos);
	void draw_end_pop_up(bool win, sf::RenderWindow& window, sf::RectangleShape board_shape);
	void init_bombs(const unsigned int row, const unsigned int col);
private:

	std::vector <std::vector <Cell> > cells;
	int width;
	int height;
	int mines_number;

	int tiles_revealed = 0;
	int flags_placed;

	bool board_cleared = false;
	bool board_exploded = false;
};

#endif

