#include "Game.h"

Game::Game() {
	init_window();

	clk = sf::Clock::Clock();
}

Game::~Game() {
	delete window;
}

void Game::poll_ev() {
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::B) {
				std::cout << "B\n";
			}
		}
	}
}

void Game::init_window() {
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Testing_WIndow_Name", sf::Style::Titlebar | sf::Style::Close);

	window->setFramerateLimit(144);
}

void Game::update() {
	poll_ev();
}

void Game::render() {
	//Render	
	window->clear(); // Clear old frame

	// draw stuff

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