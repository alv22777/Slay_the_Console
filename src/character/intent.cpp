#include "character/intent.h"
#include "game_logic/game.h"
#include "game_logic/effect.h"
#include "ui/colors.h"

std::vector<std::shared_ptr<Effect>> Intent::getActions(){return actions;}

Intent::Intent(std::vector<std::shared_ptr<Effect>> a): actions(a){}

