#include "filePlayer.h"

filePlayer::filePlayer(int n){
    number = n ;
    score = 0 ;
    if (number == 1){
        color = 'X' ;
        filename = "./noir.txt" ;
        opponent ="./blanc.txt" ;
        my_file.open(filename) ;
        opponent_file.open(opponent) ;
    }
    else if (number == 2){ 
        color = 'O' ;
        filename = "./blanc.txt" ;
        opponent ="./noir.txt" ;
        my_file.open(filename) ;
    }
} ;

int filePlayer::make_move(board &gameBoard, string &last_move, ostream & data_file, player* enemy){
    opponent_file.open(opponent, ios_base::app) ;
    opponent_file << last_move << endl ;;
    opponent_file.close() ;
    cout << last_move << endl ;
    gameBoard.print() ;
    // le fichier est déjà ouvert
    string position ;
    while(!getline(my_file, position)){
        cout << "Waiting for player " << number<< "'s file to be completed." << endl ;
        this_thread::sleep_for(chrono::milliseconds(2000));
        my_file.clear() ;
        my_file.sync() ;
    }
    cout << position << endl ;
    gameMove currentMove(gameBoard);
    int movesLeftNumber = movesLeft(number, gameBoard);

    while ((position == "00" && movesLeftNumber != 0) || currentMove.isValid(number, position, gameBoard) != 0) {
        if(position == "00" && movesLeftNumber != 0) {
            cout << "Player number " << number << " has still a move left." << endl ;
            showPossibleMoves(number, gameBoard);
            cout  << "Where would player " << number << " like to place their disc?" << endl;

            while(!getline(my_file, position)){
                cout << "Waiting for player " << number<< "'s file to be completed." << endl ;
                this_thread::sleep_for(chrono::milliseconds(2000));
                my_file.clear() ;
                my_file.sync() ;
            }
        } else {
            switch (currentMove.isValid(number, position, gameBoard)) {
                case 1:
                    cout << "Please input a valid position (e.g. 2E or 5f): ";
                    break;
                case 2:
                    cout << "There is already a disc at this position (" << position << ").";
                    break;
                case 3:
                    cout << "The position (" << position << ") you have entered is not connected to any other discs.";
                    break;
                case 4:
                    cout << "A disc at this position (" << position << ") cannot capture enemy discs.";
                    break;
                default:
                    break;
            }
            if (currentMove.isValid(number, position, gameBoard) > 1) {
                showPossibleMoves(number, gameBoard);
                cout << "Please enter another position: ";
            }
            while(!getline(my_file, position)){
                cout << "Waiting for player " << number<< "'s file to be completed." << endl ;
                this_thread::sleep_for(chrono::milliseconds(2000));
                my_file.clear() ;
                my_file.sync() ;
            }
        }
    }

    if (position == "00" && movesLeftNumber == 0) {
        cout << "Player number " << number << " has no moves left." << endl;
    } else if (position != "00") {
        gameBoard.update(currentMove.getColor(), currentMove.getYPos(), currentMove.getXPos(), currentMove.getDirections());
    }
    last_move = position ;
    return 0 ;
}