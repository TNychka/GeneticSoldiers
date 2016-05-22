class turnResolver{
	public:
		turnResolver();
		virtual ~turnResolver();
		void resolveTurns(moves playerMove1, moves playerMove2, player* player1, player* player2);	
	    int getPlayerDisplacement(player* player1, player* player2);
		int getAbsolutePlayerDisplacement(player* player1, player* player2);
	protected:
		
	private:
		void resolveMove(moves playerMove, player* player1, player* opponent, bool defend);
};