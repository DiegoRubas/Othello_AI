
d = actualState + thinkAhead
s = actualState

Bestmove(s, d, &inputBoard){
	/*if( s==60 ){ //movesLeft(board) == 0
		return score1 ;
	}*/
	if( s==d ){ //movesLeft(board) == 0
		return evalFun(inputBoard) ; // state = Board
	}

	board imBoard ;

	else{
		bestScore
		bestMove
		for(move in movesList){
			make_move(move, imBoard) // changer sur la board
			score = bestmove(s+1, d, imBoard)
			if(score > bestScore){
				bestScore = score ;
				bestMove = move
			}
			imBoard = inputBoard


		}
		return Bestmove(s+1, d) ;
	}
}

string bestPos = Bestmove(board, s, 10) ;