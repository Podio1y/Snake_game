#include "Game.h"

Game::Game() {

	x_resolution = 1280;
	y_resolution = 720;
	max_framerate = 60;

	rows = 15;
	cols = 15;

	init_window();
	init_board(true);

	clk = sf::Clock::Clock();
}

Game::Game(unsigned int x, unsigned int y, unsigned int f_rate, unsigned int r, unsigned int c, bool force_square) {

	x_resolution = x;
	y_resolution = y;
	max_framerate = f_rate;

	rows = r;
	cols = c;

	init_window();
	init_board(force_square);
	init_snake();

	clk = sf::Clock::Clock();
}

Game::~Game() {

	delete window;
	window = nullptr;

	empty_cords.clear();

	destroy_board();
	destroy_snake();
}

void Game::init_window() {
	window = new sf::RenderWindow(sf::VideoMode(x_resolution, y_resolution), "Testing_Window_Name", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(max_framerate);
}

void Game::poll_ev() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {

		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:

			switch (ev.key.code) {

			case sf::Keyboard::A:
				std::cout << "A\n";
				// x_cord--;
				x_movement = -1;
				y_movement = 0;
				break;

			case sf::Keyboard::S:
				std::cout << "S\n";
				// y_cord++;
				y_movement = 1;
				x_movement = 0;
				break;

			case sf::Keyboard::D:
				std::cout << "D\n";
				// x_cord++;
				x_movement = 1;
				y_movement = 0;
				break;

			case sf::Keyboard::W:
				std::cout << "W\n";
				// y_cord--;
				y_movement = -1;
				x_movement = 0;
				break;
			}
			break;
		}
	}
}

void Game::init_board(bool force_square) {
	board = new char* [cols];
	for (int i = 0; i < cols; i++) {
		board[i] = new char[rows];
	}

	// Soon to offload all this max to an init function, as this gets called quite often..
	y_bounds[0] = (int)y_resolution / 10.0;
	y_bounds[1] = (int)y_resolution * 9.0 / 10.0;
	x_bounds[0] = (int)x_resolution / 10.0;
	x_bounds[1] = (int)x_resolution * 9.0 / 10.0;

	row_size = floor((y_bounds[1] - y_bounds[0]) / double(rows));
	col_size = floor((x_bounds[1] - x_bounds[0]) / double(cols));

	// These are too prevent rounding error causing slight line misalingments
	y_max_rounded = y_bounds[0] + rows * row_size;
	x_max_rounded = x_bounds[0] + cols * col_size;

	// Gives the option to force a square board or keep a rectangular one
	if (force_square) {
		y_bounds[1] = (int)y_resolution * 9.0 / 10.0;
		x_bounds[1] = (int)x_resolution * 9.0 / 10.0;

		if (x_bounds[1] > y_bounds[1]) {
			x_bounds[1] = y_bounds[1];
		}
		else {
			y_bounds[1] = x_bounds[1];
		}

		row_size = floor((y_bounds[1] - y_bounds[0]) / double(rows));
		col_size = floor((x_bounds[1] - x_bounds[0]) / double(cols));

		// These are too prevent rounding error causing slight line misalingments
		y_max_rounded = y_bounds[0] + rows * row_size;
		x_max_rounded = x_bounds[0] + cols * col_size;
	}
}

void Game::destroy_board() {
	for (int i = 0; i < cols; i++) {
		delete[] board[i];
	}
	delete[] board;
}

void Game::init_snake() {
	//std::cout << rows * cols << "\n";
	snake_cords = new int* [rows*cols];
	for (int i = 0; i < rows*cols; i++) {
		snake_cords[i] = new int[2];
		snake_cords[i][0] = -1;
		snake_cords[i][1] = -1;
		std::cout << ".\n";
	}

	int start_x = ((int)(cols / 2.0));
	int start_y = ((int)(rows / 2.0));

	for (int i = 0; i < 4; i++) {
		snake_cords[i][0] = start_x;
		snake_cords[i][1] = start_y + i;
		board[snake_cords[i][0]][snake_cords[i][1]] = 's';
		std::cout << snake_cords[i][0] << " " << snake_cords[i][1] << "\n";
	}
	y_movement = -1;
	x_movement = 0;

	//empty_cords.resize(rows*cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[j][i] != 's') {
				board[j][i] = '.';
			}
		}
	}

}

void Game::destroy_snake() {
	for (int i = 0; i < rows * cols; i++) {
		delete[] snake_cords[i];
	}
	delete[] snake_cords;
}

void Game::draw_board(bool force_square) {

	// Board Lines
	for (int i = 0; i <= cols; i++) {

		draw_line(x_bounds[0] + col_size * i, y_bounds[0], x_bounds[0] + col_size * i, y_max_rounded);
	}

	for (int i = 0; i <= rows; i++) {

		draw_line(x_bounds[0], y_bounds[0] + row_size * i, x_max_rounded, y_bounds[0] + row_size * i);
	}

}

void Game::draw_snake() {
	for (int i = snake_length - 1; i >= 0; i--) {
		draw_rect(snake_cords[i][0]*col_size + x_bounds[0], snake_cords[i][1]*row_size + y_bounds[0], col_size - 1, row_size - 1, sf::Color(0, 180, 0), sf::Color(0, 110, 0));
		//std::cout << (x_bounds[0] + snake_cords[i][0] * col_size) << " " << (y_bounds[0] + snake_cords[i][1] * row_size) << "\n";
	}
	// Do something for snake_length = 0 (head)
}

void Game::draw_line(int x1, int y1, int x2, int y2) {
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};

	window->draw(line, 2, sf::Lines);
}

void Game::draw_rect(int x, int y, int width, int height, sf::Color outline, sf::Color fill) {
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(fill);
	rect.setOutlineColor(outline);
	rect.setOutlineThickness(1);
	rect.setPosition(x, y);

	window->draw(rect);
}

int Game::move_snake(int x_movement, int y_movement) {

	board[snake_cords[snake_length - 1][0]][snake_cords[snake_length - 1][1]] = '.';
	for (int i = snake_length - 1; i > 0; i--) {
		
		snake_cords[i][0] = snake_cords[i - 1][0];
		snake_cords[i][1] = snake_cords[i - 1][1];

		board[snake_cords[i][0]][snake_cords[i][1]] = 's';
	}

	snake_cords[0][0] += x_movement;
	snake_cords[0][1] += y_movement;
	if (out_of_bounds()) {
		return -1;
	}
	if (self_collision()) {
		return -1;
	}
	board[snake_cords[0][0]][snake_cords[0][1]] = 's';

	if (snake_cords[0][0] == apple_x && snake_cords[0][1] == apple_y) {
		apple_present = false;
		snake_length++;
		snake_cords[snake_length - 1][0] = snake_cords[snake_length - 2][0];
		snake_cords[snake_length - 1][1] = snake_cords[snake_length - 2][1];

		board[snake_cords[snake_length - 1][0]][snake_cords[snake_length - 1][1]] = 's';

		empty_cords.clear();
		//std::cout << "\n";
		for (int i = 0; i < rows ; i++) {
			for (int j = 0; j < cols; j++) {
				if (board[j][i] != 's') {
					empty_cords.push_back(j + i*cols);
				}
			}
		}

		if (snake_length >= rows * cols) {
			// win the game i guess
		}
	}
}

bool Game::self_collision() {
	return board[snake_cords[0][0]][snake_cords[0][1]] == 's';
}

bool Game::out_of_bounds() {
	return (snake_cords[0][0] < 0 || snake_cords[0][0] >= cols || snake_cords[0][1] < 0 || snake_cords[0][1] >= rows);
}

void Game::spawn_apple() {
	if (empty_cords.size() > 0) {
		std::uniform_int_distribution<int> distribution(0, empty_cords.size() - 1);
		int rand_num = distribution(rand_engine);
		apple_x = empty_cords.at(rand_num) % cols;
		apple_y = empty_cords.at(rand_num) / cols;
		apple_present = true;
	}
}

int Game::update() {

	if (!apple_present) {
		spawn_apple();
	}

	counter++;

	poll_ev();
	//x_cord += x_movement;
	//y_cord += y_movement;
	if ((counter % (int)(max_framerate/5.0)) == 0 && counter > 0) {
		if (move_snake(x_movement, y_movement) < 0) {
			return -1; // out of bounds
		}

		// print board for debug
		//for (int i = 0; i < rows; i++) {
		//	for (int j = 0; j < cols; j++) {
		//		std::cout << board[j][i] << " ";
		//	}
		//	std::cout << "\n";
		//}
		counter = 0;
	}
}

void Game::render() {
	//Render	
	window->clear(); // Clear old frame

	// draw stuff
	draw_board(true);
	draw_rect(apple_x*col_size + x_bounds[0], apple_y*row_size + y_bounds[0], row_size - 1, col_size - 1, sf::Color::Red, sf::Color::Red);
	draw_snake();

	window->display(); // Draw complete
}

bool Game::win_open() {
	return window->isOpen();
}

void Game::set_prev_time(sf::Time t) {
	prev_time = t;
}

float Game::get_time_diff() {
	return curr_time.asSeconds() - prev_time.asSeconds();
}

void Game::set_curr_time(sf::Time t) {
	curr_time = t;
}

sf::Clock Game::get_clock() {
	return clk;
}

sf::Time Game::get_curr_time() {
	return curr_time;
}