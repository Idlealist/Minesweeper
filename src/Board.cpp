#include "Board.hpp"
#include <algorithm>
#include <random> 
#include <ctime> 

Board::Board(unsigned int width, unsigned int height, unsigned int mines_number)
{
	try{
		if (width && height && mines_number) {
			this->width = width;
			this->height = height;
			this->mines_number = mines_number;
		}
		else
			throw(12);
	}
	catch (...) {
		std::cout << "Width, height and mine number cannot be 0\n";
	}

	for (unsigned int i = 0; i < width; i++) {
		std::vector<Cell> a;
		for (unsigned int j = 0; j < height; j++) {
			a.push_back(Cell(i, j)); 
		}
		cells.push_back(a);
	}
}


void Board::random_mine_placement(const unsigned int row, const unsigned int col)
{
	for (auto& i : cells)
		for (auto& j : i)
			j.mine = 0;
	unsigned int max_rand = width*height;
	std::vector<int> random_vector(max_rand);

	for (unsigned int i = 0; i < max_rand; i++)
		random_vector[i] = i;
	
	//clearing first click zone
	const int row_min = std::max(0, (int) row - 1);
	const int col_min = std::max(0, (int) col - 1);
	const int row_max = std::min(width - 1, (int) row + 1);
	const int col_max = std::min(width - 1, (int) col + 1);
	for (int i = row_max; i >= row_min; --i) {
		for (int j = col_max; j >= col_min; --j) {
			random_vector.erase(random_vector.begin() + (i * width) + j);
		}
	}

	std::mt19937 rng(static_cast<unsigned int>(std::time(0)));
	std::shuffle(random_vector.begin(), random_vector.end(), rng);
	
	std::vector<int> mine_locations = { random_vector.begin(), 
										random_vector.begin() + mines_number};

	std::sort(mine_locations.begin(), mine_locations.end());

	int r =0, c=0;
	for (auto &i : mine_locations){
		while ( (i - (r*height)) > height-1 && r < (width-1)) {
			r++;
		}
		cells[r][i - (r * height)]++; 
	}
}


void Board::draw_board(sf::RenderWindow &window)
{
	sf::Vector2f board_size(window.getSize());
	sf::Vector2f board_postion = board_size;
	sf::RectangleShape board_shape;
	float padding_x = 0.05f*board_size.x;
	float padding_y = 0.05f * board_size.y;
	int space_for_menu = (int) (0.25f * board_size.x);
	
	board_size.x -=space_for_menu+padding_x;
	board_size.y -= padding_y;

	board_postion.x -=board_size.x+ 0.5f*padding_x;
	board_postion.y = 0.5f*padding_y;

	board_shape.setPosition(board_postion);
	board_shape.setSize(board_size);
	board_shape.setFillColor(sf::Color(117, 113, 94));	

	window.draw(board_shape);
	draw_cells(window, board_shape);
	if(board_cleared||board_exploded)
		draw_end_pop_up(board_cleared, window, board_shape);
}

void Board::draw_cells(sf::RenderWindow &window, sf::RectangleShape board_shape)
{
	//adjusts size of board and cells apriopiate to window size
	const unsigned int cells_in_row= cells.size();
	const unsigned int cells_in_col= cells[0].size();
	const float board_width = board_shape.getSize().x;
	const float board_height = board_shape.getSize().y;
	float cell_size;
	const float cell_margin_factor=0.1f;
	float cell_margin;
	float total_cell_size;
	sf::Vector2f offset(board_shape.getPosition().x, board_shape.getPosition().y);
	const float space_per_cell_in_row = board_width / cells_in_row;
	const float space_per_cell_in_col = board_height / cells_in_col;

	if (space_per_cell_in_row > space_per_cell_in_col)
		cell_size = board_height / (cells_in_col + (cells_in_col + 1) * cell_margin_factor);
	else
		cell_size = board_width / (cells_in_row + (cells_in_row + 1) * cell_margin_factor);

	cell_margin = cell_margin_factor * cell_size;
	total_cell_size = cell_size + cell_margin;
	offset.x += cell_margin;
	offset.y += cell_margin;

	if (space_per_cell_in_row > space_per_cell_in_col)
		offset.x += (board_width - (cells_in_row * total_cell_size + cell_margin)) / 2;
	else
		offset.y +=  (board_height - (cells_in_col * total_cell_size +cell_margin)) / 2;
	
	


	sf::RectangleShape rectangle;
	sf::Vector2f cell_size_vec(cell_size, cell_size);
	rectangle.setSize(cell_size_vec);

	for (unsigned int i = 0; i < cells.size();i++) {
		for (unsigned int j = 0; j < cells[i].size(); j++) {
			sf::Vector2f cell_pos(offset.x  + (i)*(cell_size+cell_margin),
									 offset.y + (j)*(cell_size + cell_margin));
			
			rectangle.setPosition(cell_pos);

			sf::Texture cell_texture;
			try {
				if (!cell_texture.loadFromFile("Resources/Tiles_textures_16.png"))
				{
					throw 12;
				}
			}
			catch(...){
				std::cout << "Could not load a texture from \"Resources/Tiles_textures_16.png\" \n";
				exit(3);
			}
			cells[i][j].get_rectangle() = rectangle;
			cells[i][j].draw_object(window, cell_texture);
		}
	}
}

int Board::count_mines_in_neighborhood(const sf::Vector2i pos)
{
	if (cells[pos.x][pos.y].has_mine())
		return 0;

	// sets limits for x and y indexes  
	const int x_low_lim = std::max(0, pos.x - 1);
	const int y_low_lim = std::max(0, pos.y - 1);
	const int x_up_lim = std::min(width - 1, pos.x + 1);
	const int y_up_lim = std::min(width - 1, pos.y + 1);

	int mine_count = 0;
	for (int i = x_low_lim; i <= x_up_lim; i++) {
		for (int j = y_low_lim; j <= y_up_lim; j++) {
			if (cells[i][j].has_mine())
				mine_count++;
		}
	}

	return mine_count;
}

void Board::reveal_neighbors(sf::Vector2i pos)
{
	const int x_low_lim = std::max(0, pos.x - 1);
	const int y_low_lim = std::max(0, pos.y - 1);
	const int x_up_lim = std::min(width - 1, pos.x + 1);
	const int y_up_lim = std::min(width - 1, pos.y + 1);

	for (int i = x_low_lim; i <= x_up_lim; i++) {
		for (int j = y_low_lim; j <= y_up_lim; j++) {
			if (cells[i][j].get_state() == Cell::State::Unrevealed){
				cells[i][j].on_click_left();
				if (cells[i][j].get_mines_in_neighborhood() == 0)
					reveal_neighbors(sf::Vector2i(i, j));
			}
		}
	}
}

void Board::draw_end_pop_up(bool win, sf::RenderWindow& window, sf::RectangleShape board_shape)
{
	sf::Texture texture;
	try {
		if (!texture.loadFromFile("Resources/Lose_win_32.png"))
		{
			throw 12;
		}
	}
	catch (...) {
		std::cout << "Could not load a texture from \"Resources/Lose_win_32.png\" \n";
		exit(4);
	}
	sf::RectangleShape pop_up;
	float pop_up_scale = 0.45f;
	pop_up.setSize(sf::Vector2f(board_shape.getSize().x * pop_up_scale, 
								board_shape.getSize().y * pop_up_scale));

	sf::Vector2f center_pos(board_shape.getPosition().x + 0.5f * (board_shape.getSize().x - pop_up.getSize().x),
						board_shape.getPosition().y + 0.5f * (board_shape.getSize().y - pop_up.getSize().y));
	pop_up.setPosition(center_pos);
	pop_up.setTexture(&texture);
	pop_up.setTextureRect(sf::IntRect(32*(win), 0, 32, 32));

	window.draw(pop_up);
}

void Board::init_bombs(const unsigned int row, const unsigned int col)
{
	try {
		if (width * height > mines_number) {
			random_mine_placement(row, col);
			for (auto& v : cells) {
				for (auto iterator = v.begin(); iterator != v.end(); iterator++) {
					auto i = &v - &cells[0];
					auto j = std::distance(v.begin(), iterator);
					iterator->set_mines_in_neighborhood(count_mines_in_neighborhood(sf::Vector2i(i, j)));
				}
			}
		}
		else
			throw mines_number - (width * height);
	}
	catch (unsigned int a) {
		std::cout << "Wrong number of mines to spawn (mine number - cell number is " << a << ")\n";
	}
}

void Board::update_board()
{
	this->flags_placed = 0;
	this->tiles_revealed = 0;
	for (auto& i : cells) {
		for (auto& j : i) {
			if (j.get_state() == Cell::State::Revealed && j.get_mines_in_neighborhood() == 0 && !j.has_mine() ){
				auto a = &i - &cells[0];
				auto b = &j - &i[0];
				reveal_neighbors(sf::Vector2i(a, b));
			}
		}

	}
	//check win/lose condition and flags used
	for (auto& i : cells) {
		for (auto& j : i) {
			switch (j.get_state())
			{
			case Cell::State::Revealed:
				if (j.has_mine())
					this->board_exploded = true;
				else
					tiles_revealed++;
				break;
			case Cell::State::Flagged:
				flags_placed++;
				break;
			default:
				break;
			}
		}
	}

	if (tiles_revealed == (width * height - mines_number))
		this->board_cleared = true;

	//if bomb was clicked reveal all remaining mines
	else if (board_exploded) {
		for (auto& i : cells)
			for (auto& j : i)
				if (j.has_mine()) {
					if (j.get_state() == Cell::State::Flagged)
						j.on_click_right();
					j.on_click_left();
				}
	}		
}
