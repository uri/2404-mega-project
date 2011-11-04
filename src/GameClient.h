///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik, Michael Anderson, Eric Rhodes                //
//   Filename: Game.h                                                    //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef GAME_CLIENT_H
#define GAME_CLIENT_H

#include "GameSuper.h"
#include <iostream>
#include <string>


using namespace std;

// Forward declares
class Ship;
class Board;
class Player;
class Client;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GameClient : public GameSuper
{
public:
    
    GameClient();
	void play();
    
private:
	char buf[1024];
    Client *client;
	void setup (void);
    void beginGame(void);
    
};

#endif
