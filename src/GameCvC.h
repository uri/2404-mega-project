

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef GAME_CVC_H
#define GAME_CVC_H

#include "GameSuper.h"

// Forward declares
class Ship;
class Board;
class Player;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GameCvC : public GameSuper
{
public:
    
    GameCvC();
	void play();
    
private:
    
	void setup (void);
    void beginGame(void);
    
};

#endif
