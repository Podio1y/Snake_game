#pragma once

#include <iostream>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Game engine

class Game{
	public:
		Game();

		Game(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool);

		~Game();

		int update();

		void render();

		void poll_ev();

		bool win_open();

		void set_prev_time(sf::Time);

		void set_curr_time(sf::Time);

		sf::Time get_curr_time();

		float get_time_diff();

		sf::Clock get_clock();

		void init_board(bool);
		void destroy_board();

		void init_snake();
		void destroy_snake();

		int move_snake(int, int);

		bool out_of_bounds();
		bool self_collision();

		void spawn_apple();

		// Draw Functions
		void draw_board(bool force_square);
		void draw_line(int x1, int y1, int x2, int y2);
		void draw_snake();
		void draw_rect(int, int, int, int, sf::Color, sf::Color);

	private:

		unsigned int frame_count = 0;

		void init_window();

		sf::RenderWindow* window;
		sf::Event ev;

		sf::Clock clk;
		sf::Time prev_time;
		sf::Time curr_time;

		std::default_random_engine rand_engine;

		unsigned int x_resolution;
		unsigned int y_resolution;
		unsigned int max_framerate;

		int x_cord = 10;
		int y_cord = 10;
		int x_movement = 0;
		int y_movement = 0;

		unsigned int rows;
		unsigned int cols;

		unsigned int snake_length = 4;

		char** board;
		int** snake_cords;
		std::vector<int> empty_cords;

		unsigned int y_bounds[2];
		unsigned int x_bounds[2];

		unsigned int row_size;
		unsigned int col_size;

		unsigned int y_max_rounded;
		unsigned int x_max_rounded;

		unsigned int counter = 0;

		bool apple_present = false;
		unsigned int apple_x;
		unsigned int apple_y;
};

