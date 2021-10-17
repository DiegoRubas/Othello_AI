#include "player.h"
#include "playerFactory.h"

player* playerFactory::makeInstance(char type, int number){
        switch (type)
        {
        case 'h':
            return new humanPlayer(number) ;
            break;
        case 'f' :
            return new filePlayer(number) ;
            break ;
        case 'a' :
            return new artificialIntelligence(number) ;
            break ;
        default:
            cout << "An issue has occurred while creating player. Human player should take the role of player "<< number << ". " << endl ;
            return new humanPlayer(number) ;
            break;
        }
    } ;