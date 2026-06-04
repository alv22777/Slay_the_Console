#ifndef CHARACTER_H
#define CHARACTER_H


#include<iostream>
#include "stdint.h"
#include "game_logic/power.h"
#include <memory>
#include <vector>

enum class Color;
enum class Attribute{hp, max_hp, block, energy, max_energy};


//This is a Slay The Spire Character, it has several core attributes like HP, energy and block.
class Character{
	protected:
	std::string name;
	Color col;

	int max_HP; 
	int HP; 
	int block;
	
	std::vector<std::unique_ptr<Power>> powers;
	
	public:
	Character(std::string N, int MHP, Color c);

	std::string getName();
	int getAttribute(Attribute a);
	
	void setName(std::string n);
	void setAttribute(Attribute att, int value);
	
	int32_t changeAttribute(Attribute att, int Delta);
    Color getColor();
	
	const std::vector<std::unique_ptr<Power>>& getPowers();

	bool isAlive();	
	int32_t takeDamage(int magnitude);
	int32_t gainBlock(int magnitude);
	void hpChange(int magnitude);

	void addPower(PID p, int m);
	void removePower(int pos);
	void removeAllPowers();
	void removeInvalidPowers();

	
	void displayStatus();
	void displayPowers();

	void onHit(Character* source);
	int32_t modOutDamage(int32_t base);
	int32_t modIncDamage(int32_t base);
	int32_t modBlockGain(int32_t base);

	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	Character(Character&&) noexcept = default;
	Character& operator=(Character&&) noexcept = default;

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

