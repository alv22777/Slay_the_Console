#include "game.h"
#include "constants.h"
#include <ctime>


int main() {

		uint32_t seed = std::time(nullptr);

		std::deque<Character> players;
		std::deque<Character> enemies;
		
		Character player("NOPLAYER", 0, 0, 0, 0, 0, empty_deck, blank_card);
			


		RNG rng(seed);

		int choice = 0;
		while (choice < 1 || choice > 4) {
			std::cout << "Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n";
			std::cin >> choice;
		}
		player.setupPlayer(choice);
		players.emplace_back(player);
	

		Game run(players, enemies, seed);


		
        run.run(); // This is funny.
		
	}