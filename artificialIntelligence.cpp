#include "artificialIntelligence.h"
artificialIntelligence::artificialIntelligence(int n){
    number = n ;
    enemyNumber = (n % 2) + 1;
    score = 0 ;
    
    thinkAhead = 5 ;

    if (number == 1) {
        color = 'X' ;
        enemyColor = 'O' ;
    } else if (number == 2) {
        color = 'O' ;
        enemyColor = 'X' ;
    }
} ;

artificialIntelligence::artificialIntelligence(int n, int t){
    number = n ;
    enemyNumber = (n % 2) + 1;
    score = 0 ;
    thinkAhead = t ;

    if (number == 1) {
        color = 'X' ;
        enemyColor = 'O' ;
    } else if (number == 2) {
        color = 'O' ;
        enemyColor = 'X' ;
    }
} ;

int artificialIntelligence::make_move(board &gameBoard, string &last_move, ostream &data_file, player* enemy){
    int res;
    
    gameMove currentMove(gameBoard);
    string position ;
    gameBoard.print();

    auto start = high_resolution_clock::now() ;
    if (movesLeft(number, gameBoard) == 0) {
        std::cout << "Player number " << number << " has no moves left." << endl;
        res = 0 ;
    } else {
        cout << "AI " << number << " is carefully thinking of its move." << endl;
        
        //position = bestMoveTwoTurns(gameBoard);

        // New version : IA
        if(number == 1 ){
            Bestmove(1, 0, thinkAhead, enemy, gameBoard) ;
            position = bestMoveIA ; 
        }
        else {
            Bestmove(2, 0, thinkAhead, enemy, gameBoard) ;
            position = bestMoveIA ; 
            //position = bestMoveTwoTurns(gameBoard) ;
        } ;
        currentMove.isValid(number, position, gameBoard) ;
        res = gameBoard.update(color, currentMove.getYPos(), currentMove.getXPos(), currentMove.getDirections());
        cout << "AI " << number << " has chosen move " << position << " resulting in " << currentMove.getFlipNumber() << " tiles flipped." << endl ;
    }

    
    auto stop = high_resolution_clock::now() ;
    auto duration = duration_cast<milliseconds>(stop - start); 
    // affichage dans un fichier de sortie le temps pris par l'IA
    if(number==1) data_file << duration.count() <<"," ;
    else data_file << duration.count() << endl ;
    data_file.clear() ;

    
    last_move = position ;
    ofstream outfile ;
    if(number == 1)outfile.open("./noir.txt", ios_base::app) ;
    else outfile.open("./blanc.txt", ios_base::app) ;
    outfile << position << endl ;
    outfile.close() ;
    return res;

};
