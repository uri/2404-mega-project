///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, Uri Gorelik                                //
//   Filename: Game.h                                                    //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef GAME_PVC_H
#define GAME_PVC_H

#include "GameSuper.h"

// Forward declares
class Ship;
class Board;
class Player;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GamePvC : public GameSuper
{
public:

    GamePvC();
	void play();
    
private:

	void setup (void);
    void beginGame(void);
    
};

#endif // GAME_H
