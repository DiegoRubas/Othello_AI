#ifndef __human_player_h
#define __human_player_h
#include "player.h"
#include "gameMove.h"
class humanPlayer : public player {
    private :
        string name ;
    public :
        humanPlayer(int number) ;
        ~humanPlayer() ;

        void update_score(int move_cost) ;
        int make_move(board &gameboard, string &last_move, ostream &data_file=cout, player* enemy = NULL ) override ;

};

#endif