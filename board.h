#ifndef __board_h
#define __board_h
#include <iostream>
#include <cmath>
#include <set>
#include <map>

using namespace std ;

// taille par défaut : 8x8
class board{
    private:
        int size ;
        char grid[100][100] ;        // statique car doit être vu de partout
        int scorePlayer1 = 0 ;
        int scorePlayer2 = 0 ;
        set<string> stickyTiles ;
        map<string, int> moves_p1 ; // se réinitialise à chaque mvt
        map<string, int> moves_p2 ;

        set<string> cornerTiles ; 
        set<string> secondLastTiles ;
        set<string> powerTiles1;
        set<string> powerTiles2;
        set<string> powerTiles3;
        
        
    public :
        board(int size) ;   // constructeur
        board() ;   // constructeur
        ~board() ;  // destructeur

        void initBoard();
        int getSize() const ;
        set<string> getStickyTiles() ;
        set<string> getCornerTiles();
        set<string> getSecondLastTiles();

        void print();
        void printBoard(ostream & out = cout)const;    // imprime le tableau dans le ostream : console, ou fichier
        void compareBoards(board board2);
        void printScore(ostream & out = cout)const;

        /*  Met a jour le plateau, et compte combien le joueur a pris de pions supplémentaires. 
        *   Retourne ce nombre à la fonction appelante (player.play(...))
        */
        int update(char discColor, int yPos, int xPos, string directions);

        // methodes pour effectuer le coup (à commenter chacune)

        void placeDisc(char discColor, int yPos, int xPos);
        
        int flip(char discColor, int yPos, int xPos, string directions); // capture tous les pions possibles

        int flipUp(char discColor, int yPos, int xPos); // capture des pions dans chaque direction
        int flipUpRight(char discColor, int yPos, int xPos);
        int flipRight(char discColor, int yPos, int xPos);
        int flipDownRight(char discColor, int yPos, int xPos);
        int flipDown(char discColor, int yPos, int xPos);
        int flipDownLeft(char discColor, int yPos, int xPos);
        int flipLeft(char discColor, int yPos, int xPos);
        int flipUpLeft(char discColor, int yPos, int xPos);

        void update_movesList() ;
        void update_stickyList(int YPos, int xPos) ;
        void finishGame();

        char getTile(int yPos, int xPos)const;
        void setTile(int yPOs, int xPos, char color);
        int getP1score() ;
        int getP2score() ;

        int addBonus(string input);

        // function that evaluate proability of winning for player 1
        
        // returns contribution of having corner tiles to the probabilty of winning
        int corner_tiles() ;

        // returns contribution of having border tiles to the probabilty of winning
        int border_tiles() ;
        
        /* returns contribution of having lines at border to the probabilty of winning
         * take into account the length of the lines (squared) 
        **/
        int border_lines() ;

        // returns contribution of having stacked tiles to the probabilty of winning
        // int stack_tiles() ;  not good

        // returns contribution of having stacked tiles at borders to the probabilty of winning
        int border_stack_tiles() ;

        int power_spots() ;

        // function that count the length of a border line that X has captured by putting a disc at position Y, X
        int catchLine(int y, int x) ;    
} ;

#endif 