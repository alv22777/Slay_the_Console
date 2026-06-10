#include "game_logic/game.h"
#include "character/player.h"
#include "data/constants.h"
#include "ui/input.h"
#include <ctime>
#include <iostream>
#include <windows.h>
#include <memory>

int main() {
		SetConsoleOutputCP(CP_UTF8);
		uint64_t time = std::time(nullptr);
		RNG pregame(time);
		uint64_t seed = pregame.nextInt(SEED_MIN,SEED_MAX); //This can be removed, but it's here for seed presentation consistency.

		std::deque<std::unique_ptr<Enemy>> enemies;
		int choice = characterSelect();
		std::unique_ptr<Player> player = Player::createPlayer(choice);
	
		Game run(player, enemies, seed, EVENT_LOG_SIZE);
		
		bool replay = 1;
		while(replay){
			run.run(); // This is funny.
			replay = run.gameOver();
		}
		Sleep(1000);
		return 0;
}
