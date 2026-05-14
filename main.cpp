#include "game_logic/game.h"
#include "character/player.h"
#include "data/constants.h"
#include "ui/input.h"
#include <ctime>
#include <iostream>
#include <windows.h>

int main() {
		SetConsoleOutputCP(CP_UTF8); //Allows UTF8 decoding for printing symbols.
		uint32_t seed = std::time(nullptr);
		
		int choice = characterSelect();
		std::deque<Player> players = {Player::createPlayer(choice)};

		Game run(players, seed, EVENT_LOG_SIZE);
        run.run(); // This is funny.

		return 0;
}