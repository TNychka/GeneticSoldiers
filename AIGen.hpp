#include <vector>

using namespace std;

class MLAI: public player{
	public:
	
		MLAI(int health, 
			 int position, 
			 int meleeAttackDamage, 
			 int rangedAttackDamage, 
			 int defenceBlockedDamage,
			 vector <vector <int> > baseGenome);
		~MLAI();
		
		moves getMove(player* opponent);
		
		int getScore() const;
		void setScore(int score);
		
		vector <vector <int> > getGenome() const;
		
	protected:
	
	private:
		int score;
		vector <vector <int> > genome;
		int getAbsDisplacement(player* opponent);
};

class AIGenerator{
	public:
		AIGenerator(int health, 
					int position, 
					int meleeAttackDamage, 
					int rangedAttackDamage, 
					int defenceBlockedDamage,
					vector <vector<int> > seed1,
				    vector <vector<int> > seed2,
					int generationSize,
					int sizeOfMap);
		virtual ~AIGenerator();
		player* getPlayer();	
		int scorePlayer(int turns, int health, int enemyHealth, bool won);
		vector <vector <int> > getGenome() const;
	protected:
		
	private:
		int baseHealth;
		int basePosition;
		int baseMeleeAttackDamage;
		int baseRangedAttackDamage;
		int baseDefenceBlockedDamage;	
	
		int generationSize;
		int mapSize;
		
		vector <vector<int> > seed1;
		int seed1Score;
		vector <vector<int> > seed2;
		int seed2Score;
		vector<MLAI*> AIGeneration;
		
		int currentPlayer;
		
		void spawnNewGeneration();
		vector <vector<int> > createGenome();
		vector <vector<int> > mutateGenome(vector <vector<int> > genome);
		vector <vector<int> > checkGenome(vector <vector<int> > genome);
		void getHighestScoringPair();
		void breed();
};