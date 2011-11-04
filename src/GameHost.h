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

#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "GameSuper.h"


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <iostream>

using namespace std;

// Forward declares
class Ship;
class Board;
class Player;
class Server;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class GameHost : public GameSuper
{
public:
    
    GameHost();
	void play();
    
    Server * server;
    
private:
    char buf[1024];
	void setup (void);
    void beginGame(void);
	string portName;
    
};

#endif // GAME_H
