#ifndef __fileplayer_h
#define __fileplayer_h

#include "player.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std ;
class filePlayer : public player{
    private :
        string filename ;
        string opponent ;
        ifstream my_file;
        ofstream opponent_file;
        
    public :
        filePlayer(int n) ;
        ~filePlayer() ;
        int make_move(board &gameBoard, string &last_move, ostream & data_file = cout, player* enemy = NULL )override ;
} ;

#endif