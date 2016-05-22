#include "player.hpp"
#include "turnResolver.hpp"
#include <cmath>
#include <random>
#include <iostream>

using namespace std;


int turnResolver::getAbsolutePlayerDisplacement(player* player1, player* player2){
	return abs( player1->getPosition() - player2->getPosition());
}

int turnResolver::getPlayerDisplacement(player* player1, player* player2){
	return player1->getPosition() - player2->getPosition();
}

void turnResolver::resolveMove(moves playerMove, player* player1, player* opponent, bool defend){
	if(playerMove==MELEE_ATTACK){		
		if(getAbsolutePlayerDisplacement(player1, opponent)<=1){
			if(defend==true){
				cout<<"melee blocked";
			}else{
				opponent->updateHealth(-(player1->getMeleeAttackDamage()));
				cout<<"melee hit";
			}
		}else{
			cout<<"melee missed";
		}
	}else if(playerMove==RANGED_ATTACK){
		int distance = getAbsolutePlayerDisplacement(player1, opponent);
		int chanceToHit = 11-distance;
		
		if(chanceToHit>rand()%10){
			if(defend==true){
				cout<<"ranged blocked";
			}else{
				opponent->updateHealth(-(player1->getRangedAttackDamage()));
				cout<<"ranged hit";
			}			
		}else{
			cout<<"ranged miss";
		}		
	}else if(playerMove==MOVE_FORWARDS){
		if(getPlayerDisplacement(player1, opponent)>1){
			player1 -> updatePosition(-1);
			cout<<"moving left";
		}else if(getAbsolutePlayerDisplacement(player1, opponent)<=1){
			cout<<"could not move";
		}else{
			player1 -> updatePosition(1);
			cout<<"moving right";
		}		
	}else if(playerMove==DEFEND){
		cout<<"blocking";
	}
	cout<<endl;
}


turnResolver::turnResolver(){
	
}

turnResolver::~turnResolver(){
	
}

void turnResolver::resolveTurns(moves playerMove1, moves playerMove2, player* player1, player* player2){
	
	bool defending1;
	bool defending2;
	
	if(playerMove1==DEFEND){
		defending1 = true;
	}else{
		defending1 = false;
	}
	
	if(playerMove2==DEFEND){
		defending2 = true;
	}else{
		defending2 = false;
	}
	
	cout<<"player 1: ";
	resolveMove(playerMove1, player1, player2, defending2);
	cout<<"player 2: ";
	resolveMove(playerMove2, player2, player1, defending1);
}

