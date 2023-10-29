#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {

	Game* g = new Game();
	float fps = 0;
	g->set_prev_time(g->get_clock().getElapsedTime());

	while (g->win_open()) {

		g->update();

		g->render();

		//////////////////////////////////////
		// Printing fps
		g->set_curr_time(g->get_clock().getElapsedTime());
		fps = 1.0 / (g->get_time_diff());
		std::cout << "fps = " << fps << "\n";
		g->set_prev_time(g->get_curr_time());
		//////////////////////////////////////
	}

	return 0;
}