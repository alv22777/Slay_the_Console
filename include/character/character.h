#ifndef CHARACTER_H
#define CHARACTER_H


#include<iostream>

enum class Color;
enum class Attribute{hp, max_hp, block, energy, max_energy};

//This is a Slay The Spire Character, it has several core attributes like HP, energy and block.
class Character{
	protected:
	std::string name; //Your character's name.
	int max_HP; //Maximun number of Hit Points. Persistent through floors.
	int HP; //Current Hitpoints. Persistent through floors.
	int block; //Current amount of BLK. Combat only.
	Color col;
	public:
	Character(std::string N, int MHP, Color c);

	std::string getName();
	int getAttribute(Attribute a);
	
	void setName(std::string n);
	void setAttribute(Attribute att, int value);
	
	void changeAttribute(Attribute att, int Delta);
    Color getColor();
	bool isAlive();	
	void takeDamage(int magnitude);
	void gainBlock(int magnitude);
	void hpChange(int magnitude);
	virtual ~Character() noexcept = default;
};
// int Stance; //WAT, PSM (Prismatic): Current Stance. 0: Neutral NTL, 1: Calm CLM, 2: Wrath WRT, 3: Divinity DIV. Combat only.
// int orbSlots; //How many orb slots you currently have. Defect starts with 3. On any other character, you start with 1 if you are Prismatic. Combat only.
// deque <int> orbs; //Your channeled orbs. Combat only.
// bool prismatic;
// int potionSlots; //How many potion slots you currently have. You start with 3. Persistent through floors.
// deque <Potion> potions; //Your current potions. Persistent through floors, but you can only use them in combat.
//^^^^ Future Potion class will be very simple, since effects that can be applied by potions will be limited to the same effects that can be applied by cards. 

#endif