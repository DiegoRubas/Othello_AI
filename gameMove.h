#ifndef __gamemove_h
#define __gamemove_h

#include "board.h"
class gameMove{
    private:
        int yPos;
        int xPos;
        char color;
        char enemyColor;
        int directions[8];
        int flipNumber;
        int size ;
        board currentBoard;
    public:
        gameMove();
        gameMove(board &board);
        gameMove(int yPos, int xPos);
        ~gameMove();

        int isValid(int playerNumber, string input, board &inputBoard);

        bool isValidInput(string input); // vérifie si l'entrée est valide (2e ou 2E et non 9I ou 0Z) DEVRAIT ETRE STATIQUE

        int isValidPosition(int playerNumber); // vérifie si la position du pion à placer est valide, à savoir les suivants: DEVRAIT ETRE STATIQUE
        bool isSticky(); // vérifie si le pion à placer est contigu à un pion (ennemi)
        bool canFlip(); // vérifie si un pion à cet endroit peut capturer des pions ennemis

        void checkUp(); // vérifie dans toutes les directions
        void checkUpRight();
        void checkRight();
        void checkDownRight();
        void checkDown();
        void checkDownLeft();
        void checkLeft();
        void checkUpLeft();


        void setPos(string input) ;
        int getYPos();
        int getXPos();
        char getColor();
        char getEnemyColor();
        int getDirection(int i);
        int getFlipNumber();
        string getDirections();
};

#endif