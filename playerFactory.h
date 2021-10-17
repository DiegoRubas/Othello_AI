#include "player.h"
class playerFactory {
    public :
        virtual ~playerFactory(){} ;
        static player* makeInstance(char type, int number);
} ;