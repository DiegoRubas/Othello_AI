#include <string>
#include "game.h"

using namespace std;

int main() {

    game game;
    board gameBoard = game.getBoard() ;

    // game.gameplay();

    for (int i = 0; i < 60; i++) {

        gameBoard.print();

        string position;
        int playerNumber = (i % 2) + 1;

        cout << "Where would player " << playerNumber << " like to place their disc?" << endl;
        cin >> position;

        gameMove currentMove;

        while (!currentMove.isValid(playerNumber, position, gameBoard)) {
            cin >> position;
        }

        gameBoard.update(currentMove.getColor(), currentMove.getYPos(), currentMove.getXPos(), currentMove.getDirections());

        if (gameBoard.enemyMovesLeft(playerNumber) == 0) {
            i = 60; //condition de sortie de la boucle
            cout << "Player number " << ((i + 1) % 2) + 1 << " has no moves left." << endl;
            gameBoard.print();
        }

    }
    
    gameBoard.finishGame();

    return 0;
}