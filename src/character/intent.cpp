#include "character/intent.h"
#include "game_logic/game.h"
#include "game_logic/effect.h"
#include "ui/colors.h"

std::vector<Effect>& Intent::getActions(){return actions;}


Intent::Intent(std::vector<Effect> a): actions(a){}

