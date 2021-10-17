#include <ctime>
#include <iostream>
#include "game.h"


bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main(int argc, char*  argv[]) {
    int size;
    if(argc == 1){
        size = 8 ;
    }
    else if(!is_number(argv[1])) {
        cout << "Input for grid size is invalid." << endl ;
        return 1 ;
    }
    else size = atoi(argv[1]) ;
    
    int cheat = 0 ;
    if(argc>=3){
        cheat = 1 ;
    }
    if(argc == 3){
        game game(size, cheat) ;    
        game.start() ; 
        while( !game.isFinished() ){
            game.play() ; 
        }
    }
    else {
        game game(size, cheat, atoi(argv[3]), atoi(argv[4])) ;    
        game.start() ; 
        while( !game.isFinished() ){
            game.play() ; 
        }
    }

    return 0;
}