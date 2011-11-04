#ifndef GAME_OBSERVER_H
#define GAME_OBSERVER_H

#include "GameSuper.h"


#define BUF_SIZE            1024
#define SERVER_IP           "134.117.27.122"
#define SERVER_PORT         60000


// Forward declares
class Ship;
class Board;
class Player;
class Observer;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GameObserver : public GameSuper
{
public:
    
    GameObserver();
	void play();
    
private:
    
	void setup (void);
    void beginGame(void);
    char buf[1024];
    
    Observer * observer;
    
};

#endif
