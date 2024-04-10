#include "Game.hpp"
#include <typeinfo>

void Game::update_game_state()
{
    menu.update_menu();
    switch (menu.current_board)
    {
    case Menu::Current_board::new_Beginner:
        reset_game();
        board = new Board(8, 8, 10);
        menu.current_board = Menu::Current_board::cur_Begginer;
        break;
    case Menu::Current_board::new_Intermediate:
        reset_game();
        board = new Board(13, 13, 40);
        menu.current_board = Menu::Current_board::cur_Intermediate;
        break;
    case Menu::Current_board::new_Advanced:
        reset_game();
        board = new Board(22, 22, 99);
        menu.current_board = Menu::Current_board::cur_Advanced;
        break;
    default:
        break;
    }
    
    if (board) {
        board->update_board();
        if (board->board_exploded || board->board_cleared) {
            this->end_game(board->board_cleared);
        }
        menu.flag_counter.set_flags_left(board->flags_placed);
    }
}

void Game::init_variables()
{
	this->window = nullptr;
}

void Game::init_window()
{	
	this->video_mode.height = 600;
    this->video_mode.width = 800;
    this->window = new sf::RenderWindow(this->video_mode, "Minesweeper");
    this->mouse_held = false;
}

void Game::get_mouse_position()
{
    this->mouse_position_window = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(mouse_position_window);
}

void Game::update_objects()
{
    if (!game_over && board){
        for (auto& i : board->cells) {
            for (auto& j : i) {
                update_object(j);
            }
        }
    }

    for (auto& i : menu.buttons) {
        update_object(i);
    }
}

void Game::update_object(Game_Object &object)
{
        if (object.get_rectangle().getGlobalBounds().contains(this->mouse_position_view)) {
            switch (this->event.key.code) {
            case sf::Mouse::Button::Left:
                if (first_turn) {
                    if (typeid(object) == typeid(Cell)) {
                        Cell& cell_object = dynamic_cast<Cell&>(object);
                        board->init_bombs(cell_object.get_row(), cell_object.get_col());
                        first_turn = false;
                    }
                }
                object.on_click_left();
                update_game_state();  
                break;
            case sf::Mouse::Button::Right:
                object.on_click_right();
                update_game_state();

                if (board->flags_placed > board->mines_number) { //if flags limit was exceeded retrive previous state
                    object.on_click_right();
                    update_game_state();
                }
                break;
            }
        }
}

void Game::switch_board_stat()
{
    switch (menu.current_board)
    {
    case Menu::Current_board::cur_Begginer:
        menu.current_board = Menu::Current_board::new_Beginner;
        break;
    case Menu::Current_board::cur_Intermediate:
        menu.current_board = Menu::Current_board::new_Intermediate;
        break;
    case Menu::Current_board::cur_Advanced:
        menu.current_board = Menu::Current_board::new_Advanced;
        break;
    default:
        break;
    }
}

void Game::reset_game()
{
    game_over = 0;
    win = 0;
    first_turn = 1;
    if(board)
        delete board;
}


Game::Game()
{
    this->init_variables();
	this->init_window();
    this->menu.init_menu(*this->window);
}

Game::~Game()
{
	delete this->window;
    delete this->board;
    delete this->object;
}

const bool Game::is_window_open()
{
	return this->window->isOpen();
}

void Game::update_Event()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
            else if (event.key.code == sf::Keyboard::Space) {
                switch_board_stat();
                update_game_state();
                render();
            }
            break;
        case sf::Event::MouseButtonPressed:
            this->update_objects();
            this->render();
            break;
        case sf::Event::Resized: {
            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
            this->render();
            break;
        }
        default:
            break;
        }
    }
}

void Game::update()
{
    this->get_mouse_position();
    this->update_Event();

}


void Game::render()
{
    this->window->clear(sf::Color(39, 40, 34));
    if(board)
        this->board->draw_board(*this->window);

    this->menu.draw_menu(*this->window);
    this->window->display();
}

void Game::end_game(bool win)
{
    this->game_over = true;
    this->win = win;
}
