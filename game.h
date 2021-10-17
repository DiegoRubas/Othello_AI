#ifndef __game_h
#define __game_h
#include <iostream>
using namespace std;
#include <string.h>
#include <fstream>
#include "board.h"
#include "player.h"

class game{
    private:
        board gameBoard;
        bool finished ;
        int size, cheat, t_A1, t_A2 ; // mode triche : utilise direct l'IA
        string last_move ;
        char type1, type2 ;
        ofstream data_file ;
        player* players[2];
        int Z ; // nombre de tours passés consécutifs
        // player player1 = player('X');
        // player player2 = player('O');
        // player players[2] = {player1, player2};
    public:
    
        game(int size, int cheat);
        game(int size, int cheat, int t_A1, int t_A2);
        ~game();
        board getBoard();

        bool isFinished() ;

        void setSize(int size) ;

        void start() ;
        void play() ;
        void passed_turn() ;
        void set_last_turn(string position) ;
        void played_turn() ;
        void end() ;
        
        void enter_player_input(int n) ;
        bool valid_player_input(char type) ;

};

#endif 