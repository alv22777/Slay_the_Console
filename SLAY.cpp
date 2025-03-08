#include "game.h"
#include "constants.h"
#include <ctime>

/*
	Glossary:
	ICL: The Ironclad
	SLT: The Silent
	DEF: The Defect
	WAT: The Watcher
	CLS: Colorless cards
	HP: Hit Points. If it becomes 0, you instantly die and lose the game.
	NRG: Energy. It's used to play cards.
	BLK: Block. If an enemy attacking would reduce your HP, lose that amount of block instead.
	ATK: An Attack. Deals damage to an/ALL enemies. Sometimes has other effects.
	SKL: Skill. Usually gives you block and/or other useful efects like card draw.
	POW: Power. Gives you a continuous (useful) effect throughout combat.
	CUR: Curse. Has negative effects. Obtained through events and certain relics.
	EXH: Exhaust. When this card is played, remove it from your deck until end of combat. 
*/

std::mt19937 seed(std::time(nullptr));// Better random number generator

int main() {

    	initializeDecks();
		Character player = Character("NOPLAYER", 0, 0, 0, 0, 0, empty_deck, blank_card);
        Game run = Game(player,seed);
		int choice = 0;
		while (choice < 1 || choice > 4) {
			std::cout << "Please select your character: \n1. The Ironclad\n2. The Silent\n3. The Defect\n4. The Watcher\n";
			std::cin >> choice;
		}
        run.setupPlayer(choice);
        run.start();
}