#include "player.hpp"
#include "turnResolver.hpp"
#include "map.hpp"
#include "AIGen.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generatePlayers(player** player1, player** player2, AIGenerator* gen){

	if(*player2!=NULL){
		delete *player2;
	}
	 *player1 = /*new basicAI(50, 19, 20, 5, 20);*/gen->getPlayer();
	 *player2 = new basicAI(50, 19, 20, 5, 20);
}

void printGameInformation(int player1Wins,int player2Wins){
	cout<<"P1 wins: "<<player1Wins<<" P2 wins: "<<player2Wins<<endl;
}

void printGenome(AIGenerator* gen){
	vector <vector <int> > temp = gen->getGenome();
	cout<<"   def mel ran mov"<<endl;
	for(int i = 0; i < temp.size(); i++){
		if(i<10){
			cout<<i<<"  ";
		}else{
			cout<<i<<" ";
		}
		for(int z = 0; z< temp.at(i).size(); z++){			
			cout<<temp.at(i).at(z)<<"  ";
		}
		cout<<endl;
	}
}

int main(){
	turnResolver* resolutionController = new turnResolver;
	map* field = new map(20);	
	vector <vector <int> > baseGenome{{25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25},
									  {25,25,25,25}};
	
	vector <vector <int> > seed1 = baseGenome;
	vector <vector <int> > seed2 = baseGenome;
	

	AIGenerator* gen = new AIGenerator(50, 0, 20, 5, 20, baseGenome, baseGenome, 100, 20);
	

	player* player1=NULL;
	player* player2=NULL;

	generatePlayers(&player1, &player2, gen);
	
	int player1Wins = 0;
	int player2Wins = 0;
	int turnsTaken = 0;
	int gameNumber = 1;
	
	while(1){
		if(player1->getHealth()<=0){
			cout<<"Game Number: "<<gameNumber<<endl;
			cout<<"Player 2 win"<<endl;
			cout<<"Turns :"<<turnsTaken<<endl;
			cout<<"AI SCORE: "<<gen->scorePlayer(turnsTaken, player1->getHealth(), player2->getHealth(), false)<<endl;
			printGenome(gen);
			player2Wins++;
			printGameInformation(player1Wins, player2Wins);
			generatePlayers(&player1, &player2, gen);	
			turnsTaken = 0;
			gameNumber++;
			if(gameNumber%10000000==0){
				cout<<"Continue?"<<endl;
				string temp="n";	
				cin>>temp;
				if(temp=="y"){
					
				}else{
					return 0;
				}
			}	
		}else if(player2->getHealth()<=0){
			cout<<"Game Number: "<<gameNumber<<endl;
			cout<<"Player 1 win"<<endl;
			cout<<"Turns :"<<turnsTaken<<endl;
			cout<<"AI SCORE: "<<gen->scorePlayer(turnsTaken, player1->getHealth(),player2->getHealth(), true)<<endl;
			printGenome(gen);
			player1Wins++;
			printGameInformation(player1Wins, player2Wins);
			generatePlayers(&player1, &player2, gen);				
			turnsTaken = 0;	
			gameNumber++;	
			if(gameNumber%10000000==0){
				cout<<"Continue?"<<endl;
				string temp="n";	
				cin>>temp;
				if(temp=="y"){
					
				}else{
					return 0;
				}
			}			
		}else{
			resolutionController->resolveTurns(player1->getMove(player2),
											   player2->getMove(player1),
											   player1,
											   player2);
			field->drawMap(player1, player2);
			cout<<"P1 health: "<<player1->getHealth()<<" ";
			cout<<"P2 health: "<<player2->getHealth()<<endl;
			turnsTaken++;
		}
	}
}

