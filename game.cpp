#include "game.h"
#include "playerFactory.h"
#include <string.h>
#include <vector>

game::game(int boardSize, int cheatCode) {
    size = boardSize ;
    gameBoard = board(size) ;
    t_A1 = 0 ;
    t_A2 = 0 ;
    last_move = "" ;
    std::time_t result = std::time(nullptr);
    std::asctime(std::localtime(&result)) ;
    string filename = "data/time_data" + to_string(size) + "_" + to_string(result) + ".csv" ;
    data_file.open(filename, ios_base::app) ;
    Z = 0 ;
    cheat = cheatCode ;
    if(cheat == 1) {
        type1 = 'a' ;
        type2 = 'a' ;
    }
}
game::game(int boardSize, int cheatCode, int t1, int t2) {
    size = boardSize ;
    gameBoard = board(size) ;
    t_A1 = t1 ;
    t_A2 = t2 ;
    last_move = "" ;
    std::time_t result = std::time(nullptr);
    std::asctime(std::localtime(&result)) ;
    string filename = "data/"+to_string(t_A1) + "vs" + to_string(t_A2) + "time_data" + to_string(size) + "_" + to_string(result) + ".csv" ;
    data_file.open(filename, ios_base::app) ;
    Z = 0 ;
    cheat = cheatCode ;
    if(cheat == 1) {
        type1 = 'a' ;
        type2 = 'a' ;
    }
}
game::~game() = default ;
board game::getBoard(){
    return gameBoard;
}

 bool game::isFinished(){
    return finished == 1 ;
}

void game::enter_player_input(int i){
    cout << "Please enter the type of player " << i << " ." << endl << "'H' stands for 'Human'" << endl << "'F' stands for 'File'" << endl << "'A' stands for 'Artificial Intelligence'" << endl ;
}

bool game::valid_player_input(char type){
    return (isalpha(type)) && ((type == 'H') || (type == 'h') || (type == 'F') || (type == 'f') || (type == 'A') || (type == 'a'))  ;
}

void game::set_last_turn(string position){
    last_move = position ;
}

void game::start(){
    cout << "Welcome to Othello !" << endl ;
    // Si le code de triche est actif, les types ne sont même pas demandés
    if(cheat != 1){
        // Player 1 input 
        enter_player_input(1) ;
        cin >> type1 ;

        while(!valid_player_input(type1)){
            cout << "Input not valid. A or H or F stp. " << endl ;
            cin >> type1 ;
        }

        // Player 2 input 
        enter_player_input(2) ;
        cin >> type2 ;

        while(!valid_player_input(type2)){
            cout << "Input not valid. A or H or F stp. " << endl ;
            cin >> type2 ;
        }
    }
    
    type1 = tolower(type1) ;
    type2 = tolower(type2) ;
    // identifications des joueurs dans le fichier d'analyse des données de jeu
    // encodage [T][N] où T est le type du joueur (a, h, ou f)
    // et [N] est le numéro du joueur, soit 1 soit 2
    data_file << type1<<1 << "," << type2<<2 <<endl ;
    if(t_A1 != 0 && t_A2 != 0){
        player* player1 = new artificialIntelligence(1, t_A1) ;
        player* player2 = new artificialIntelligence(2, t_A2) ;
        players[0] = player1 ;
        players[1] = player2 ; 
    }
    else{
        player* player1 = playerFactory::makeInstance(type1, 1) ;
        player* player2 = playerFactory::makeInstance(type2, 2) ;
        players[0] = player1 ;
        players[1] = player2 ; 
    }


}

void game::play(){
    for(int i = 1; i<=2; i++){
        int playerNumber = i  ;
        cout << "Player " << playerNumber << "'s turn." << endl ;
        int move_score =0 ;
        /* if(artificialIntelligence* AI = dynamic_cast<artificialIntelligence*>(players[playerNumber-1])){
            move_score = AI->make_move(gameBoard, last_move, data_file, players[playerNumber%2]) ;
        }
        else{
            move_score = players[playerNumber-1]->make_move(gameBoard, last_move, data_file, NULL) ;
        } */
        move_score = players[playerNumber-1]->make_move(gameBoard, last_move, data_file, players[playerNumber%2]) ;
        if(move_score == 0){
            if(++Z == 2){
                cout << "Since the two players have no moves left, the party is ending." << endl ;
                end() ;
                break ;
            }
        }
        else 
            Z = 0 ;

    }

}


void game::end(){
    cout << "##############################" << endl << "Final board : " << endl ;
    gameBoard.print() ;
    finished = 1 ;
}
