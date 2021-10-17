#include "humanPlayer.h"
humanPlayer::humanPlayer(int n){
    number = n ;
    cout<< "What would be player " << number << "'s name ?" << endl ;
    std::cin >> name ;
    if (number == 1)
        color = 'X' ;
    else if (number == 2) 
        color = 'O' ;
    score = 0 ;
    cout << "player number " <<number << " is called " << name << endl ;
};

humanPlayer::~humanPlayer() = default ;

int humanPlayer::make_move(board &gameBoard, string &last_move, ostream &data_file, player* enemy) {
    int res ;
    
    string position ;
    gameBoard.printBoard();
    cout << "Where would player " << number << " like to place their disc?" << ' ';
    std::cin >> position;

    gameMove currentMove(gameBoard);
    int movesLeftNumber = movesLeft(number, gameBoard);

    while ((position == "00" && movesLeftNumber != 0) || currentMove.isValid(number, position, gameBoard) != 0) {
        if(position == "00" && movesLeftNumber != 0) {
            cout << "Player number " << number << " has still a move left." << endl ;
            showPossibleMoves(number, gameBoard);
            cout  << "Where would player " << number << " like to place their disc?" << endl;
            std::cin >> position;
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
            std::cin >> position;
        }
    }

    if (position == "00" && movesLeftNumber == 0) {
        cout << "Player number " << number << " has no moves left." << endl;
        res = 0 ;
    } else if (position != "00") {
        res = gameBoard.update(currentMove.getColor(), currentMove.getYPos(), currentMove.getXPos(), currentMove.getDirections());
    }
    last_move = position ;
    return res ;
}