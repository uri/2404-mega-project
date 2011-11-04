//
//  GameSingle.cpp
//  Mega Project
//
//  Created by ugorelik on 11-03-31.
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "GameHost.h"
#include "Board.h"
#include "Player.h"
#include "Random.h"
#include "Renderer.h"
#include "ShipTypes.h"
#include "Statistics.h"
#include "NetworkUtility.h"
#include "Server.h"
#include <string>

#include <limits>
#include <iostream>



using namespace std;


//-----------------------------------------------------------------------//
// Game                                                                  //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Runs the game and handles restarting it. </summary>

//Game Constructor
GameHost::GameHost()
{
	playerWin = 43;
    enemyWin = 40;
    
    server = new Server();
	
	mPlayer = new Player(); //these might need to be moved into switch statement
	mEnemy  = new Player();
    
}

void GameHost::setup()
{
    
    cout << "Would you like to quickstart (y/n)? ";
    char quickstart; cin >> quickstart;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    
    // Create enemy ships
    
    
    // Create player ships
    if ((quickstart | 32) == 'y')
    {
        createShipPosition (mPlayer->getBoard(), new Battlestar());
        createShipPosition (mPlayer->getBoard(), new Raptor());
        createShipPosition (mPlayer->getBoard(), new Raptor());
        createShipPosition (mPlayer->getBoard(), new Raptor());
        createShipPosition (mPlayer->getBoard(), new Viper());
        createShipPosition (mPlayer->getBoard(), new Viper());
        createShipPosition (mPlayer->getBoard(), new Viper());
        createShipPosition (mPlayer->getBoard(), new Viper());
    }
    else
    {
        queryShipPosition (mPlayer->getBoard(), new Battlestar());
        queryShipPosition (mPlayer->getBoard(), new Raptor());
        queryShipPosition (mPlayer->getBoard(), new Raptor());
        queryShipPosition (mPlayer->getBoard(), new Raptor());
        queryShipPosition (mPlayer->getBoard(), new Viper());
        queryShipPosition (mPlayer->getBoard(), new Viper());
        queryShipPosition (mPlayer->getBoard(), new Viper());
        queryShipPosition (mPlayer->getBoard(), new Viper());
        
    }
    
    // TODO: Rewrite to make more OOPish
    
    // Send message to client    
    // --------------------------------------------
    
    cout << "Ready to send all info... " << endl;
    
    // Ship list sending
    // --------------------------------------------
    // Send Message
    
    bzero(buf, 1024);
    strcpy(buf,NetworkUtility::shipListToCString(mPlayer)); 
    
    server->SendMessage(buf);
    
	cout << "Host sent the ship list: " << buf << endl;
    
    bzero(buf, 1024);		//clear the buffer to receive in 
    // --------------------------------------------
    // Read Message
    
    strcpy(buf, server->ReadMessage());
    
    cout << "Host : Received Ship List" << endl;
    
    // Decode
    printf("\n\n%s\n", buf);
    NetworkUtility::networkSetup(mEnemy,buf);
    
    
    //DEBUG Print the enemies list
    bzero(buf, 1024);
    strcpy(buf,NetworkUtility::shipListToCString(mEnemy)); 
    printf("This is the enemy's list: \n%s\n\n",buf);
}


void GameHost::play()
{ 
	setup();
    
	Renderer::draw(mPlayer, mEnemy);// Render the blank board
    
	beginGame();
    server->Stop();
	server->EndTransmission();
	delete server;
	delete mPlayer;
	delete mEnemy;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets up the player and enemy ships. </summary>
void GameHost::beginGame()
{
    
    
    
	// ------------------------------------------------
    //      Main Shoot loop
    // ------------------------------------------------
    bool hostGoes = true;
	while (mPlayer->getStats()->getHitCount() != playerWin && mEnemy->getStats()->getHitCount() != enemyWin)
	{
		server->AddObserver(mPlayer,mEnemy);
		server->UpdateObservers(mPlayer,mEnemy);
        if (hostGoes) {
			hostGoes = mPlayer->shoot(mEnemy);
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
			if (hostGoes)
				cout<<"Direct hit! Take another shot!";
			else{
				cout<<"You missed. Turn over.";
				//send info on hits/misses to the enemy
				server->SendMessage(NetworkUtility::convertToString(mPlayer->getRecentHits(), mPlayer->getRecentMisses()));

				mPlayer->getRecentHits()->clear();
				mPlayer->getRecentMisses()->clear();
			}
            
		} 
		else	//CLIENT GOES 
		{
            bzero(buf, 1024);
			strcpy(buf,server->ReadMessage());
			NetworkUtility::networkShoot(mEnemy,buf); // Might need to change  back to mEnemy
			Renderer::draw(mPlayer, mEnemy);
			cout << buf << endl;			//DEBUG CODE
			cout <<"Your turn! \n";
			hostGoes = true;
		}
        
        
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