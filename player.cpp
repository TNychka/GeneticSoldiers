#include "player.hpp"

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/*PLAYER*/
player::player(int health, 
			   int position, 
			   int meleeAttackDamage, 
			   int rangedAttackDamage,
			   int defenceBlockedDamage)
			   :health(health),
			   position(position),
			   meleeAttackDamage(meleeAttackDamage),
			   rangedAttackDamage(rangedAttackDamage),
			   defenceBlockedDamage(defenceBlockedDamage){
}

player::~player(){
	
}

int player::getPosition() const{
	return position; 
}
int player::getHealth() const{
	return health; 
}
int player::getMeleeAttackDamage() const{
	return meleeAttackDamage; 
}
int player::getRangedAttackDamage() const{
	return rangedAttackDamage; 
}
int player::getDefenceBlockedDamage() const{
	return defenceBlockedDamage; 
}
void player::updateHealth(int healthChange){
	health += healthChange;
}
void player::updatePosition(int positionChange){
	position += positionChange;
}

/*BASIC AI*/
basicAI::basicAI(int health, 
			     int position, 
			     int meleeAttackDamage, 
			     int rangedAttackDamage,
			     int defenceBlockedDamage)
			     :player(health, position, meleeAttackDamage, rangedAttackDamage, defenceBlockedDamage){
					 
}

basicAI::~basicAI(){
	
}

//Really, really basic ai. Improve if I see fit later
moves basicAI::getMove(player* opponent){
	if(abs(opponent->getPosition() - getPosition()) <= 1){
		return MELEE_ATTACK;
	}else{
		return MOVE_FORWARDS;
	}
}

/*BASIC USER INPUT*/
basicPlayerInput::basicPlayerInput(int health, 
			     int position, 
			     int meleeAttackDamage, 
			     int rangedAttackDamage,
			     int defenceBlockedDamage)
			     :player(health, position, meleeAttackDamage, rangedAttackDamage, defenceBlockedDamage){
					 
}

basicPlayerInput::~basicPlayerInput(){
	
}

moves basicPlayerInput::getMove(player* opponent){
	string input;
	while(1){
		cin>>input;
		if("melee"==input){
			return MELEE_ATTACK;
		}else if("ranged"==input){
			return RANGED_ATTACK;
		}else if("move"==input){
			return MOVE_FORWARDS;
		}else if("defend"==input){
			return DEFEND;
		}
	}
}