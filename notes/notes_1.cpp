int main(){
	static board* plateau_de_jeu = new board() ;

	player* player1 = new player('O') ;
	player* player2 = new player('X') ;

	while(...){
		int coup1 = player1.play(*plateau_de_jeu, row, column) ;
		int coup2 = player2.play(*plateau_de_jeu, row, column) ;
	}
}

class player{
	private :
		char color ; // noir ou blanc
	public :
		...
		int play(board* plateau, int row, int column){
			int num_pions_gagne = plateau.update(color, row, column) // va retourner le nombre de pions remplacés

			return num_pions_gagne ;
		}
}