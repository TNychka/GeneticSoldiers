#include "player.hpp"
#include "AIGen.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
#include <random>
#include <vector>

using namespace std;

MLAI::MLAI(int health, 
		   int position, 
	       int meleeAttackDamage, 
	       int rangedAttackDamage,
	       int defenceBlockedDamage,
		   vector <vector <int> > genome		   
	       ):genome(genome), 		  
		   player(health, 
		   position, 
		   meleeAttackDamage, 
		   rangedAttackDamage, 
		   defenceBlockedDamage){
			cout<<"new"<<endl;
}

MLAI::~MLAI(){
	
}

int MLAI::getAbsDisplacement(player* opponent){
	return abs(opponent->getPosition() - getPosition());
}

moves MLAI::getMove(player* opponent){
	int roll = rand()%100+1; //generate roll 0 - 100
	int distance = getAbsDisplacement(opponent);
	int probability=0;
	if(roll<=genome.at(distance).at(0)){
		return DEFEND;
	} else if(roll<=genome.at(distance).at(1)+genome.at(distance).at(0)){
		return MELEE_ATTACK;
	} else if(roll<=genome.at(distance).at(2)+genome.at(distance).at(1)+genome.at(distance).at(0)){
		return RANGED_ATTACK;
	} else if(roll<=genome.at(distance).at(3)+genome.at(distance).at(2)+genome.at(distance).at(1)+genome.at(distance).at(0)){
		return MOVE_FORWARDS;
	} else{
		return DEFEND;
	}
}

void MLAI::setScore(int score){
	score = score;
}

int MLAI::getScore() const{
	return score;
}

vector <vector <int> > MLAI::getGenome() const{
	return genome;
}


AIGenerator::AIGenerator(int health, 
						 int position, 
						 int meleeAttackDamage, 
						 int rangedAttackDamage, 
						 int defenceBlockedDamage,
						 vector <vector <int> > seed1,
						 vector <vector <int> > seed2,
						 int generationSize,
						 int sizeOfMap
						 ):baseHealth(health),
						 basePosition(position),
						 baseMeleeAttackDamage(meleeAttackDamage),
						 baseRangedAttackDamage(rangedAttackDamage),
						 baseDefenceBlockedDamage(defenceBlockedDamage),
						 seed1(seed1),
						 seed2(seed2),
						 generationSize(generationSize),
						 mapSize(sizeOfMap),
						 AIGeneration(generationSize, NULL),
						 currentPlayer(generationSize)
{		
	breed();					 
}

AIGenerator::~AIGenerator(){
	for(int i = AIGeneration.size(); i>=0; i--){
		delete AIGeneration.at(i);
		AIGeneration.pop_back();
	}
}

player* AIGenerator::getPlayer(){
	currentPlayer--;
	if(currentPlayer<0){
		cout<<"Spawning new generation"<<endl;
		spawnNewGeneration();	
		currentPlayer=generationSize-1;		
	}
	return AIGeneration.at(currentPlayer);
}

int average(int a, int b){
	return (a+b)/2;
}

vector <vector<int> > AIGenerator::createGenome(){
	/***distance     0 1 2 3 4 5 6 7 8 9 10 11
	   move 0 defend 
			1 melee
			2 range
			3 move			
	*/
	vector <vector <int> > genome(mapSize, vector<int>(4,25));
	/*Average the genomes of the two successful candidates*/			
	for(int i = genome.size()-1; i >= 0; i--){
		for(int z = genome.at(0).size()-1; z>=0; z--){			
			genome.at(i).at(z)=( average( seed1.at(i).at(z), seed2.at(i).at(z) ) );
		}
	}
	return genome;
}

/***********************PLAY WITH THESE***************/
int AIGenerator::scorePlayer(int turns, int health, int enemyHealth, bool won){
	int score = 0;	
	score = 2*max(0,health) - 3*max(0,enemyHealth);
	if(won){
		score+=150;
		score += 30 - turns;
	}else{
		score += min(30,turns);
	}
	AIGeneration.at(currentPlayer)->setScore(score);
	return score;
}

vector <vector<int> > AIGenerator::mutateGenome(vector <vector<int> > genome){	
	/*Introduce mutations*/
	for(int i = genome.size()-1; i >= 0; i--){
		for(int z = genome.at(0).size()-1; z>=0; z--){
			int roll = rand()%100;			
			if(roll>95){//major mutation 2
				int newProbability = min(100, max(0,(4-rand()%9)+genome.at(i).at(z)));
				genome.at(i).at(z)= newProbability;
			}else if(roll>70){//minor mutation 1
				int newProbability = min(100, max(0,(1-rand()%3)+genome.at(i).at(z)));
				genome.at(i).at(z)= newProbability;
			}else{
			}
		}
	}
	return genome;
}
/***********************PLAY WITH THESE***************/

vector <vector<int> > AIGenerator::checkGenome(vector <vector<int> > genome){	
	/*Assert sum of probabilities is not out side of 0-100*/
	for(int i = genome.size()-1; i >= 0; i--){
		int sum = 0;
		for(int z = genome.at(0).size()-1; z>=0; z--){
			sum+=genome.at(i).at(z);
		}
		if(sum<=96){
			for(int z = genome.at(0).size()-1; z>=0; z--){
				genome.at(i).at(z)++;
			}
		}else if(sum>=104){
			for(int z = genome.at(0).size()-1; z>=0; z--){
				genome.at(i).at(z)--;
			}
		}
	}
	return genome;
}

void AIGenerator::breed(){
	vector <vector <int> > baseGenome = createGenome();	
	for (int i =0; i< generationSize;i++){
		if(AIGeneration[i]!=NULL){
			delete (AIGeneration[i]);
			AIGeneration[i]=NULL;
		}
    } 
	AIGeneration.clear();
	for(int i = 0; i<generationSize; i++){			
		AIGeneration.push_back(new MLAI(baseHealth,
								   basePosition,
								   baseMeleeAttackDamage,
								   baseRangedAttackDamage,
								   baseDefenceBlockedDamage,
								   checkGenome(mutateGenome(baseGenome))));	
	}
}

vector <vector <int> > AIGenerator::getGenome() const{
	return AIGeneration[currentPlayer]->getGenome();
}

void AIGenerator::getHighestScoringPair(){
	
	assert(AIGeneration.size()>=1);
	
	if(AIGeneration.size()==1){

		seed2=seed1=AIGeneration.at(0)->getGenome();		
	}else{	

		for(int i = AIGeneration.size()-1; i>=0; i--){
			if(seed1.empty()){
				seed1 = AIGeneration.at(i)->getGenome();
			}else if(seed2.empty()){
				seed2 = AIGeneration.at(i)->getGenome();
			}else{
				if(AIGeneration.at(i)->getScore() > seed1Score){
					seed1 = AIGeneration.at(i)->getGenome();
				}else if(AIGeneration.at(i)->getScore() > seed2Score){
					seed2 = AIGeneration.at(i)->getGenome();
				}
			}
		}
	}
}

void AIGenerator::spawnNewGeneration(){
	seed1.clear();
	seed2.clear();
	getHighestScoringPair();	
	cout<<endl;
	breed();
}