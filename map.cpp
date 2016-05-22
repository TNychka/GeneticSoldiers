#include "player.hpp"
#include "map.hpp"

#include <iostream>

using namespace std;

map::map(int mapSize):mapSize(mapSize){
	
}

map::~map(){
	
}

void map::drawMap(player* player1, player* player2){
	
	int player1Position = player1->getPosition();
	int player2Position = player2->getPosition();
	
	for(int i = 0; i<mapSize; i++){
		if(player1Position==i){
			cout<<"1 ";
		}else if(player2Position==i){
			cout<<"2 ";
		}else{
			cout<<"_ ";
		}
	}	
	cout<<endl;
}