#ifndef PLAYER_CLASS
#define PLAYER_CLASS
#include "board.h"
#include "gameMove.h"
#include <fstream>
#include <iostream>
class player{
    protected :
        int score, number, enemyNumber;
        char color, enemyColor;
        string bestMoveIA ;
    public :
        ~player();
        int getNumDisks() ;
        char getColor() ;
        int getNumber() ;
        void updateNumDisks(int change) ;

        void skipMove(int playerNumber);
        int discMovesLeft(char discColor, board &gameBoard, int playerNumber);
        int movesLeft(int playerNumber, board &gameBoard);
        int enemyMovesLeft(int playerNumber, board &gameBoard);
        void showPossibleMoves(int playerNumber, board &inputBoard);

        /*  player.play(...) va informer le plateau que des choses vont changer. 
        *   Le plateau va compter combien de pions sont gagnés et les retourner dans cette méthode.
        *   main() se chargera de soustraire le nombre de pions à l'adversaire
        *   
        *   Hint : réfléchir en termes de "nombre de pions gagnés/perdus à l'adversaire" est un bon critère pour l'IA
        * 
        */
        // int play(board grid, int row, int col) ;  // utilisera le board qui est statique
        virtual int make_move(board &gameBoard, string &last_move, ostream &data_file=cout, player* enemy = NULL) =0;


        int eval_fun(int calling_palyer, board & inputBoard) const ;
        int Bestmove(int calling_palyer, int turn, int think_ahead, player* enemy, board & inputBoard, int enemyMinMax=0) ;
        int bestCorner(board & inputBoard, string move);
        int worstTiles(board & inputBoard, string move);
};
#include "humanPlayer.h"
#include "filePlayer.h"
#include "artificialIntelligence.h"
#endif
