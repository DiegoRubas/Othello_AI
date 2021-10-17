#include "gameMove.h"

gameMove::gameMove(){
    xPos = 0 ;
    yPos = 0 ;
    
    for (int i = 0; i < 8; i++) {
        directions[i] = 0;
    }
}
gameMove::gameMove(board &b) {
    currentBoard = b;
    size = currentBoard.getSize() ;
    for (int i = 0; i < 8; i++) {
        directions[i] = 0;
    }
    //cout << endl;
}
gameMove::gameMove(int y, int x) {
    yPos = y ;
    xPos = x ;
}

gameMove::~gameMove() = default;

int gameMove::isValid(int playerNumber, string input, board &inputBoard) {
    int errorType = 0;
    flipNumber = 0;
    currentBoard = inputBoard;
    
    if(input == "00") return 0 ;

    if (!isValidInput(input)) {
        errorType = 1;
    } else if (isValidPosition(playerNumber) != 0) {
        errorType = isValidPosition(playerNumber);
    }
    return errorType;
}

bool gameMove::isValidInput(string input) {
    bool valid = false;
    if (input.length() == 2) {
        yPos = int(input.at(0)) - 48 - 1;
        xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
        if (0 <= yPos && yPos < size && 0 <= xPos && xPos < size) {
            valid = true;
        }
    }
    return valid;
}

int gameMove::isValidPosition(int playerNumber) {

    int errorType = 0;

    if (playerNumber == 1) {
        color = 'X';
        enemyColor = 'O';
    } else {
        color = 'O';
        enemyColor = 'X';
    }

    if (currentBoard.getTile(yPos, xPos) != '.') {
        errorType = 2;
    } else if (!isSticky()) {
        errorType = 3;
    } else if (!canFlip()) {
        errorType = 4;
    }
    

    return errorType;
}

bool gameMove::isSticky() {
    bool sticky = false;

    int minX = (xPos == 0) ? 0 : -1;
    int maxX = (xPos == size - 1) ? 0 : 1;
    int minY = (yPos == 0) ? 0 : -1;
    int maxY = (yPos == size - 1) ? 0 : 1;

    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            if (currentBoard.getTile(yPos + j, xPos + i) == enemyColor) {
                sticky = true;
            }
        }
    }

    return sticky;
}

bool gameMove::canFlip() {
    checkUp();
    checkUpRight();
    checkRight();
    checkDownRight();
    checkDown();
    checkDownLeft();
    checkLeft();
    checkUpLeft();
    bool flipper = false;
    for (int i = 0; i < 8; i++) {
        if (directions[i] == 1) {
            flipper = true;
        }
    }
    return flipper;
}

void gameMove::checkUp() {
    directions[0] = 0;
    if (currentBoard.getTile(yPos - 1, xPos) == enemyColor) { // vérifie s'il y a un pion ennemi directement au-dessus
        for (int i = yPos - 2; i >= 0; i--) { // parcourt tous les pions au-dessus sauf celui directement dessus
            if (currentBoard.getTile(i, xPos) == color) {
                int enemyDiscCounter = 0;
                for (int j = i + 1; j < yPos; j++) { // compte le nombre de disques de l'ennemi entre le pion à placer et le pion évalué
                    if (currentBoard.getTile(j, xPos) == enemyColor)
                        enemyDiscCounter++;
                }
                if (enemyDiscCounter == yPos - i - 1) {
                    /*
                    en comparant le nombre de disques ennemies et l'écart entre 2 disques, on sait déterminer s'il n'y a que des pions ennemis entre
                    les 2 disques évalués (donc pas de vide) et par conséquent si le disque à placer peut captuer des pions adverses
                    */
                    i = -1; // condition de sortie
                    directions[0] = 1;
                    flipNumber += enemyDiscCounter;
                }
            }
        }
    }
}

void gameMove::checkUpRight() {
    directions[1] = 0;
    for (int i = 2; i <= min(size - 1 - xPos, yPos); i++) {
        if (currentBoard.getTile(yPos - i, xPos + i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > 0; j--) {
                if (currentBoard.getTile(yPos - j, xPos + j) == enemyColor) {
                    enemyDiscCounter++;
                }
            }
            if (enemyDiscCounter == i - 1) {
                i = size;
                directions[1] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkRight() {
    directions[2] = 0;
    for (int i = xPos + 2; i < size; i++) {
        if (currentBoard.getTile(yPos, i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > xPos; j--) {
                if (currentBoard.getTile(yPos, j) == enemyColor)
                    enemyDiscCounter++;
            }
            if (enemyDiscCounter == i - xPos - 1) {
                i = size;
                directions[2] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkDownRight() {
    directions[3] = 0;
    for (int i = 2; i <= min(size - 1 - xPos, size - 1 - yPos); i++) {
        if (currentBoard.getTile(yPos + i, xPos + i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > 0; j--) {
                if (currentBoard.getTile(yPos + j, xPos + j) == enemyColor) {
                    enemyDiscCounter++;
                }
            }
            if (enemyDiscCounter == i - 1) {
                i = size;
                directions[3] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkDown() {
    directions[4] = 0;
    for (int i = yPos + 2; i < size; i++) {
        if (currentBoard.getTile(i, xPos) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > yPos; j--) {
                if (currentBoard.getTile(j, xPos) == enemyColor)
                    enemyDiscCounter++;
            }
            if (enemyDiscCounter == i - yPos - 1) {
                i = size;
                directions[4] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkDownLeft() {
    directions[5] = 0;
    for (int i = 2; i <= min(xPos, size - 1 - yPos); i++) {
        if (currentBoard.getTile(yPos + i, xPos - i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > 0; j--) {
                if (currentBoard.getTile(yPos + j, xPos - j) == enemyColor) {
                    enemyDiscCounter++;
                }
            }
            if (enemyDiscCounter == i - 1) {
                i = size;
                directions[5] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkLeft() {
    directions[6] = 0;
    for (int i = xPos - 2; i >= 0; i--) {
        if (currentBoard.getTile(yPos, i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i + 1; j < xPos; j++) {
                if (currentBoard.getTile(yPos, j) == enemyColor)
                    enemyDiscCounter++;
            }
            if (enemyDiscCounter == xPos - i - 1) {
                i = -1;
                directions[6] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

void gameMove::checkUpLeft() {
    directions[7] = 0;
    for (int i = 2; i <= min(xPos, yPos); i++) {
        if (currentBoard.getTile(yPos - i, xPos - i) == color) {
            int enemyDiscCounter = 0;
            for (int j = i - 1; j > 0; j--) {
                if (currentBoard.getTile(yPos - j, xPos - j) == enemyColor) {
                    enemyDiscCounter++;
                }
            }
            if (enemyDiscCounter == i - 1) {
                i = size;
                directions[7] = 1;
                flipNumber += enemyDiscCounter;
            }
        }
    }
}

int gameMove::getYPos() {
    return yPos;
}

int gameMove::getXPos() {
    return xPos;
}

char gameMove::getColor() {
    return color;
}

char gameMove::getEnemyColor() {
    return enemyColor;
}

int gameMove::getDirection(int i) {
    return directions[i];
}

string gameMove::getDirections() {
    string dirString = "00000000";
    for (int i = 0; i < 8; i++) {
        if (directions[i] == 1) {
            dirString[i] = '1';
        }
    }
    return dirString;
}

int gameMove::getFlipNumber() {
    return flipNumber;
}

void gameMove::setPos(string input){
    yPos = int(input.at(0)) - 48 - 1;
    xPos = (int(input.at(1) < 97)) ? int(input.at(1)) - 65 : int(input.at(1)) - 97;
}
