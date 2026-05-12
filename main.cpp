#include "game_logic/game.h"
#include "game_logic/rng.h"
#include "character/enemy.h"
#include "character/player.h"
#include "data/constants.h"
#include "ui/colors.h"
#include "ui/eventlog.h"
#include <ctime>
#include <iostream>
#include <stdint.h>
#include <windows.h>

int main() {

		SetConsoleOutputCP(CP_UTF8); //Allows UTF8 decoding for printing symbols.
		uint32_t seed;

		// std::cout<<"Do you want to choose a custom seed? 0: random seed.\n";std::cin>>seed;
		// if(seed==0){seed = std::time(nullptr);}

		seed = std::time(nullptr);	
		RNG rng(seed);

		std::deque<Player> players;
		std::deque<Enemy> enemies;
		
		
		int choice = 0;
		
		while (choice < 1 || choice > 4) {
			std::cout << "Please select your character:\n";
			std::cout<<color(Color::red, "1. The Ironclad\n")<<color(Color::green, "2. The Silent\n")<<
			color(Color::blue, "3. The Defect\n")<<color(Color::purple, "4. The Watcher\n");
			std::cin >> choice;
		}
		
		Player player("NOPLAYER", 0,0, Color::colorless);

		player.setupPlayer(choice);
		players.emplace_back(player);
	

		Game run(players, enemies, seed, EventLog(5));


		
        run.run(); // This is funny.
		
	}