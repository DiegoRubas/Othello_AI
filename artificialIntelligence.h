#ifndef __AI_h
#define __AI_h
#include "player.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std ;
using namespace chrono ;

class artificialIntelligence : public player{
    private :
        int thinkAhead ;
    public :
        artificialIntelligence(int number) ;
        artificialIntelligence(int number, int t_A) ;
        ~artificialIntelligence() ;
        int make_move(board &gameBoard, string &last_move, ostream &data = cout, player* enemy = NULL) override;
        string bestMoveOneTurn(board &gameBoard) ;
        string bestMoveTwoTurns(board &gameBoard);
        string bestMoveThreeTurns(board &gameBoard);

        // AI 
        void showAIThoughtProcess();
} ;
#endif