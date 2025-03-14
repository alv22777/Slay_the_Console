#include "game.h"
#include "constants.h"
#include <ctime>

std::mt19937 seed(std::time(nullptr));// Better random number generator

int main() {

		Character player("NOPLAYER", 0, 0, 0, 0, 0, empty_deck, blank_card);
        Game run(player,seed);

		int choice = 0;
		while (choice < 1 || choice > 4) {
			std::cout << "Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n";
			std::cin >> choice;
		}
		player.setupPlayer(choice);
        run.start();
}