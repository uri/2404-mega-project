///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik, Eric Rhodes, Michael Anderson                //
//   Filename: Game.h                                                    //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef GAME_SUPER_H
#define GAME_SUPER_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//

class Ship;
class Board;
class Player;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GameSuper
{
public:
	// Game
	virtual void play (void) = 0;
    
protected:
	virtual void setup (void) = 0;
    virtual void beginGame(void) = 0;
    void queryShipPosition  (Board *target, Ship *ship);
    void createShipPosition (Board *target, Ship *ship);
	    
    
protected:
	// Variables
    Player * mPlayer;
    Player * mEnemy;
    int playerWin;
    int enemyWin;
};

#endif // GAME_H
