#include "Cell.hpp"


Cell::Cell(const unsigned int row, const unsigned int col) : row(row), col(col) {
}


void Cell::set_position(sf::Vector2f position)
{
    this->rectangle.setPosition(position);
}

Cell Cell::operator++()
{
    set_mine();
    return *this;
}

Cell Cell::operator++(int)
{
    set_mine();
    return *this;
}


void Cell::set_size(sf::Vector2f size)
{
    try {
        if (size.x < 0.0f)
            throw("Cell size_x");
        else if (size.y < 0.0f)
            throw("Cell size_y");
    }
    catch (std::string a) {
        std::cout << a << "has to be greater or equal to 0\n";
        exit(3);
    }
    this->rectangle.setSize(size);
}



void Cell::set_color(sf::Color color)
{
    this->rectangle.setFillColor(color);
}

void Cell::on_click_left()
{
    switch (this->state)
    {
    case State::Unrevealed:
        this->state = State::Revealed;
    default:
        break;
    }
}


void Cell::set_mines_in_neighborhood(int mine_count)
{
    this->mines_in_neighborhood = mine_count;
}
int Cell::get_mines_in_neighborhood() const{
    return this->mines_in_neighborhood;
}

void Cell::on_click_right() {
    switch (this->state)
    {
    case State::Unrevealed:
        this->state = State::Flagged;
        break;
    case State::Flagged:
        this->state = State::Unrevealed;
    default:
        break;
    }
}
void Cell::set_mine() {
    try{
        if (!mine)
            mine = true;
        else
            throw 21;
    }
    catch (...) {
        std::cout << "This cell already has a mine!!!\n";
        exit(4);
    }
}

void Cell::draw_object(sf::RenderWindow& window, sf::Texture& texture)
{
    switch (this->get_state()) {
    case State::Unrevealed:
        rectangle.setFillColor(sf::Color(66, 65, 51));
        break;
    case Cell::State::Revealed:
        if (this->has_mine()) {
            
            rectangle.setTexture(&texture);
            rectangle.setTextureRect(sf::IntRect(16 * 9, 0, 16, 16));
        }
        else
            if (mines_in_neighborhood) {
                rectangle.setTexture(&texture);
                rectangle.setTextureRect(sf::IntRect(16 * mines_in_neighborhood, 0, 16, 16));
            }else
                rectangle.setFillColor(sf::Color(92,90,71));
        break;
    case Cell::State::Flagged:
        rectangle.setTexture(&texture);
        rectangle.setTextureRect(sf::IntRect( 0, 0, 16, 16));
        break;
    }
    window.draw(this->rectangle);
}

sf::RectangleShape& Cell::get_rectangle()
{
    return rectangle;
}



const bool Cell::has_mine() const
{
    return mine;
}

const unsigned int Cell::get_row()
{
    return row;
}

const unsigned int Cell::get_col()
{
    return col;
}


Cell::State Cell::get_state() {
    return this->state;
}



