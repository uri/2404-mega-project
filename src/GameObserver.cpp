//////////////////////////////////////////////////////////////////////////////////////////////
//						GameObserver.cpp														//
//						Last edited by: Michael Anderson									//
//////////////////////////////////////////////////////////////////////////////////////////////

#include "GameObserver.h"

#include "Observer.h"
#include "Player.h"
#include "Board.h"
#include "Ship.h"
#include "ShipTypes.h"
#include "Statistics.h"
#include "NetworkUtility.h"
#include "Renderer.h"
#include "Client.h"
#include <iostream>
#include <limits>

using namespace std;

//Game Constructor
GameObserver::GameObserver()
{
	playerWin = 43;
    enemyWin = 40;
    
    observer = new Observer();
	
	mPlayer = new Player();
	mEnemy  = new Player();
    

}

void GameObserver::setup()
{
	
    bzero(buf, 1024);
	strcpy(buf,observer->ReadMessage());
	printf("This is the player: \n%s\n\n",buf);
	NetworkUtility::networkShoot(mPlayer,buf);
	bzero(buf, 1024);
	strcpy(buf,observer->ReadMessage());
	printf("This is the Enemy: \n%s\n\n",buf);
	NetworkUtility::networkShoot(mEnemy,buf);


   

}


void GameObserver::play()
{       
    
    setup();
    Renderer::draw(mPlayer, mEnemy);
    
    beginGame();
    
    delete mPlayer;
    delete mEnemy;
    cout << "The game has concluded...\n";
    exit(0);
    
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets up the player and enemy ships. </summary>
void GameObserver::beginGame()
{ 
    
	while (mPlayer->getStats()->getHitCount() != playerWin && mEnemy->getStats()->getHitCount() != enemyWin)
	{
		bzero(buf, 1024);
		strcpy(buf,observer->ReadMessage());
		NetworkUtility::networkShoot(mPlayer,buf);
		bzero(buf, 1024);
		strcpy(buf,observer->ReadMessage());
		NetworkUtility::networkShoot(mEnemy,buf);
    
		Renderer::draw(mPlayer, mEnemy);

	}


    // Game Over
    Renderer::draw(mPlayer, mEnemy);    // Draw the final state of the game board
    if (mPlayer->getStats()->getHitCount() == playerWin) {
        cout << "Player 1 Wins!" << endl;
    } else {
        cout << "Player 2 Wins!" << endl;
    }
    
    mPlayer->printStats();  
    mEnemy->printStats();
    cout<< "GAME OVER"<< endl;
    
}

