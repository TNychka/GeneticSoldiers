class map{
	public:
		map(int MapSize);
		virtual ~map();
		void drawMap(player* player1, player* player2);
	private:
		int mapSize;
};