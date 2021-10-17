

int eval_fun(board & inputBoard, player* playerA, player* playerB) const{
	// provisoirement
	char cA, cB ;
	cA = playerA->getColor() ;
	cB = playerB->getColor() ;
	if(playerB->getScore() == playerA->getScore()) return 1/2 ;
	if(cA == 'X') return playerA->getScore() > playerB->getScore() ;
	else return playerA->getScore() > playerB->getScore() ;
}

/* Bestmove -> de la classe AI
Arguments : turn, inputBoard, et un pointeur vers le joueur ADVERSE

*/
// NB : "number" est un attribut de l'objet qui appelle "Bestmove" !
Bestmove(int turn, int think_ahead, player *shittyPlayer, const board & nputBoard) { 
	board copyBoard = inputBoard ;

	if(think_ahead == 0){
		return eval_fun(inputBoard, this, shittyPlayer) ;
	}

	if(turn == 60){
		return score>shittyPlayer->getScore() ;
	}

	int bestScore ; // if player 1, must maximize
					// if player 2, must minimize

	string bestMove ;
	else{
		
		int movesNum = movesLeft(number, copyBoard) ;
		string movesList[movesNum] ;

		for(move in movesList){

			// pour la generation exhaustive, 	
			// backtracking : recherche exhaustive
			imaginaryBoard.update(color, move) ;
			int move_score = shittyPlayer->Bestmove(turn+1, think_ahead-1, this, copyBoard) ;

			// recherche de la meilleure solution par min et max
			if(number ==  1 && move_score > bestScore){
				bestScore = move_score ;
				bestMove = move ;
			}
			else if(numer == 2 && move_score < bestScore){	
				bestScore = move_score ;
				bestMove = move ;
			}

			// UNDO (backtracking)	
			copyBoard = inputBoard ;
		}
	}
}