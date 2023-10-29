#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

// Game engine

class Game{
	public:
		Game();

		~Game();

		void update();

		void render();

		void poll_ev();

		bool win_open();

		void set_prev_time(sf::Time);

		void set_curr_time(sf::Time);

		sf::Time get_curr_time();

		float get_time_diff();

		sf::Clock get_clock();

	private:

		unsigned int frame_count = 0;

		void init_window();

		sf::RenderWindow* window;
		sf::Event ev;

		sf::Clock clk;
		sf::Time prev_time;
		sf::Time curr_time;
};

