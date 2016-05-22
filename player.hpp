enum moves {DEFEND, MELEE_ATTACK, RANGED_ATTACK, MOVE_FORWARDS};

class player{
	public:
	
		virtual ~player();
		
		int getHealth() const;
		int getPosition() const;
		
		void updateHealth(int healthChange);
		void updatePosition(int positionChange);
		
		int getMeleeAttackDamage() const;
		int getRangedAttackDamage() const;
		int getDefenceBlockedDamage() const;	
		
		virtual moves getMove(player* opponent)=0;
	
	protected:
		player(int health, int position, int meleeAttackDamage, int rangedAttackDamage, int defenceBlockedDamage);
		
	private:
		int health;
		int position;
		const int meleeAttackDamage;
		const int rangedAttackDamage;
		const int defenceBlockedDamage;
};

class basicAI: public player{
	public:
		basicAI(int health, int position, int meleeAttackDamage, int rangedAttackDamage, int defenceBlockedDamage);
		~basicAI();
		moves getMove(player* opponent);
	protected:
	
	private:
};

class basicPlayerInput: public player{
	public:
		basicPlayerInput(int health, int position, int meleeAttackDamage, int rangedAttackDamage, int defenceBlockedDamage);
		~basicPlayerInput();
		moves getMove(player* opponent);
	protected:
	
	private:
		int getAbsDisplacement(player* opponent);
};