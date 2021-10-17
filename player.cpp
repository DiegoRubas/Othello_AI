#include "player.h"
#include <algorithm>

player::~player() = default ;

int player::getNumber(){return number;}
int player::getNumDisks(){return score;} ;
void player::updateNumDisks(int change){
    score += change ;
}

void player::skipMove(int playerNumber){
    
    if (playerNumber == 1){
        playerNumber = 2;
        //rediriger le pointeur ?
    }
    else {
        playerNumber = 1;
    } 
    //cout << "player " << playerNumber << endl;
}

int player::discMovesLeft(char discColor, board &gameBoard, int playerNumber) {
    int size = gameBoard.getSize() ;
    int tally = 0;

    gameMove checkedMove(gameBoard);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            string input = "";
            input += char(j + 1 + 48);
            input += char(i + 65);
            if (checkedMove.isValid(number, input, gameBoard) == 0) {
                tally++;
            }
        }
    }
    if (tally == 0)
    {
        //cout << "No more moves left" << endl;
        skipMove(playerNumber);
    }

    return tally;

}

int player::movesLeft(int playerNumber, board &gameBoard) {

    char discColor = (playerNumber == 1) ? 'X' : 'O';
    return discMovesLeft(discColor, gameBoard, playerNumber);

}

int player::enemyMovesLeft(int playerNumber, board &gameBoard) {

    char enemyDiscColor = (playerNumber == 1) ? 'O' : 'X';
    return discMovesLeft(enemyDiscColor, gameBoard, playerNumber);

}

void player::showPossibleMoves(int playerNumber, board &inputBoard) {
    int size = inputBoard.getSize() ;

    board currentBoard = inputBoard;
    gameMove checkedMove(currentBoard);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            string input = "";
            input += char(j + 1 + 48);
            input += char(i + 65);
            if (checkedMove.isValid(number, input, inputBoard) == 0) {
                currentBoard.setTile(j, i, '*');
            }
        }
    }

    cout << "All possible moves for player " << number << " are marked by a '*' on hypothetical board on the left." << endl;

    currentBoard.compareBoards(inputBoard);

}

char player::getColor(){return color ;}

// AI
int player::eval_fun(int calling_player, board & inputBoard) const{
    int evaluation, c1, c2, c3, c4 ;
    c1 = 1 ;
    c2 = 20 ;
    c3 = 5 ;
    c4 = 5 ;
    evaluation = 0 ;

    int eval_number = inputBoard.getP1score() ;
    evaluation += c1*eval_number ;

    if(calling_player != 0){
        int eval_borders = inputBoard.border_lines() ;
        int eval_corners = inputBoard.corner_tiles() ;
        int eval_powers = inputBoard.power_spots(); //regarde la position des power spots (sauf les corners car deja fait)
        
        evaluation += c2*eval_borders ;
        evaluation += c3*pow(eval_corners,2) ;
        evaluation += c4*eval_powers;
    }
    else{
    }

    return evaluation ;
}

int player::bestCorner(board & inputBoard, string move){
    int winProba = 0 ;
    //get the list of the tiles on the corners 
    set<string> cornerTiles = inputBoard.getCornerTiles();
    //set<string>::iterator corner_itr = cornerTiles.begin() ;
    //if the tiles on the board is in the list -> winning proba rises
    //while(corner_itr != cornerTiles.end()){
        //for (int i = 0; i < movesList.size(); i++){
    if (cornerTiles.count(move) == 1){
        winProba += 1; 
       // cout << "its a me mario" << endl;
    } 
    else {
        winProba = 0;
       // cout << "its a me luigi" << endl;
    }
        //corner_itr = next(corner_itr, 1);
       // }
    //}
    return winProba;
}

int player::worstTiles(board & inputBoard, string move){
    int scoreLoss = 0;
    set<string> secondLastTiles = inputBoard.getSecondLastTiles();
    if (secondLastTiles.count(move) == 1){
        scoreLoss -= 1;
    }
    else {
        scoreLoss = 0;
    }
    return scoreLoss;
}


int player::Bestmove(int calling_palyer, int counter, int think_ahead, player* enemy, board & inputBoard, int enemyMinMax){
    
    board copyBoard = inputBoard ;
    int bestScore = inputBoard.getP1score() ; // to min/max : player 1's score
    bestScore = ((number==1)? -100000:100000) ; // new version
    bestScore = 0 ;
    if(think_ahead == 0) {
        //cout << "doing eval for player " << number << " at counter = " << counter << endl ;   
        int evalReturn = eval_fun(calling_palyer, copyBoard) ;
        //cout << "Return from eval function : " << evalReturn  << ". Now returning to counter = " << counter -1<< endl ;
        return evalReturn ;
    }

    string bestMove;

    int movesNum = movesLeft(number, copyBoard) ;
    string movesList[movesNum] ;

    
    
    gameMove checkedMove(copyBoard) ;
    string input ;
    set<string> stickyTiles = inputBoard.getStickyTiles() ;
    set<string>::iterator sticky_itr = stickyTiles.begin() ;

    map <string, int> validMoves ;

    int max = 0;
    int min = 0;

    while(sticky_itr!=stickyTiles.end()){
        input = *sticky_itr ;
        sticky_itr = next(sticky_itr, 1) ;
        if(checkedMove.isValid(number, input, copyBoard) == 0){ //puisque la move est deja validinput, sticky et vide, on pourrait simplement verifier s'il capture
            int value = checkedMove.getFlipNumber(); // met comme valeur le nombre de pions captures
            value += copyBoard.addBonus(input); // y ajoute la valeur associee a sa position dans le plateau
            validMoves.insert(pair<string, int> (input, value)) ; //moves sticky ainsi que valides pour le player
            if (value > max) {
                max = value;
            }
            if (value < min) {
                min = value;
            }

            // gen exhaustive sur les stickytiles
            //movesList[n++] = input ;
        }
    }

    // tri du map
    int l = 0;
    for (int i = max; i >= min; i--) {
        for (map <string, int>::iterator valid_itr = validMoves.begin(); valid_itr != validMoves.end(); valid_itr++) {
            string position = valid_itr->first;
            int value = valid_itr->second;
            if (i == value) {
                movesList[l] = position;
                l++;
            }
        }
    }

    
    
    /* // GEN EXHAUSTIVE
    int size = inputBoard.getSize() ;
    int i, j ;
    string input ;
    int n =0;
    gameMove checkedMove(copyBoard) ;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            input = "";
            input += char(j + 1 + 48);
            input += char(i + 65);
            if(checkedMove.isValid(number, input, copyBoard) == 0) {
                score += checkedMove.getFlipNumber() ;
                movesList[n] = input ;
                n ++ ;
            }
        }
    } */
    int res = 1 ; 
    int k = 0 ;
    while(res==1 && k < movesNum){
        gameMove move(inputBoard);
        string input = movesList[k] ;
        //cout << endl <<"Trying new move : "<< input  << " on the following board " << endl ;
        //inputBoard.printBoard() ;
        //cout << input << endl ;
        move.isValid(number, input, inputBoard) ;
        int move_score ;      

        // update function : modifies board and updates player 1 and 2 scores (board attributes)
        copyBoard.update(move.getColor(), move.getYPos(), move.getXPos(), move.getDirections()) ;
        //cout << "calling bestmove for player number " << enemy->getNumber() << " at counter "<< counter+1   << endl ;
        move_score = enemy->Bestmove(calling_palyer, counter+1, think_ahead-1, this, copyBoard, bestScore) ;
        if(bestScore == 0) bestScore = move_score ;
        //move_score += bonus;
        if(enemyMinMax != 0 && ((number == 2 && move_score < enemyMinMax) || (number == 1 && move_score > enemyMinMax))){
            bestScore = move_score ;
            res = 0 ;
        }
        

        //cout << "move_score (return from eval of enemy)" << move_score << " that should be compared to " << bestScore <<endl ;
        
        if((number == 1 && move_score >= bestScore) || (number == 2 && move_score <= bestScore)){
            //cout << " New maximum reached for player " << number << " at counter = " << counter << "for input " << input  << endl ;
            bestScore = move_score ;
            bestMove = input ;
            if(counter == 0){
                bestMoveIA =bestMove ;
            }
        }

        // UNDO
        copyBoard = inputBoard ;
        k++ ;
    }
    //cout << " With best move for player " << number << " at counter = " << counter << " ( " <<bestMove <<" " <<bestScore<< "), now returning to player" << enemy->getNumber() << " at " << "counter = " << counter -1 << endl ;
    return bestScore ;    
}