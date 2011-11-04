//
//  GameClient.cpp
//  Mega Project
//
//  Created by ugorelik on 11-03-31.
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "GameClient.h"
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
GameClient::GameClient()
{
	playerWin = 43;
    enemyWin = 40;
    
	
	//set the instance variables port and servername to the portnumber and servername passed in
    
    cout << "Good before launching client server" << endl;
	client = new Client();
	
	mPlayer = new Player(); //these might need to be moved into switch statement
	mEnemy  = new Player();
    
}

void GameClient::setup()
{
    
    cout << "Would you like to quickstart (y/n)? ";
    char quickstart; cin >> quickstart;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
    
    
    // Create enemy ships
    
    
    // Create player ships
    if ((quickstart | 32) == 'y')
    {
        createShipPosition (mPlayer->getBoard(), new Basestar());
        createShipPosition (mPlayer->getBoard(), new HeavyRaider());
        createShipPosition (mPlayer->getBoard(), new HeavyRaider());
        createShipPosition (mPlayer->getBoard(), new Raider());
        createShipPosition (mPlayer->getBoard(), new Raider());
        createShipPosition (mPlayer->getBoard(), new Raider());
        createShipPosition (mPlayer->getBoard(), new Raider());
        createShipPosition (mPlayer->getBoard(), new Raider());
    }
    
    else
    {
        queryShipPosition (mPlayer->getBoard(), new Basestar());
        queryShipPosition (mPlayer->getBoard(), new HeavyRaider());
        queryShipPosition (mPlayer->getBoard(), new HeavyRaider());
        queryShipPosition (mPlayer->getBoard(), new Raider());
        queryShipPosition (mPlayer->getBoard(), new Raider());
        queryShipPosition (mPlayer->getBoard(), new Raider());
        queryShipPosition (mPlayer->getBoard(), new Raider());
        queryShipPosition (mPlayer->getBoard(), new Raider());
        
    }
    
    cout << "Ready to recieve info... " << endl;
    
    // Ship List getting
    // --------------------------------------------
    // Read Message
    bzero(buf, 1024);
    
    strcpy(buf, client->ReadMessage());
    
    cout << "Client : Received Ship List"<< buf << endl;
    
    // Now the client has the host ship
    // Now the host needs the client ships
    // --------------------------------------------
    // Send Client Ship Locations to the Host
    client->SendMessage(NetworkUtility::shipListToCString(mPlayer));
    
    // Decode 
    printf("\n\n%s\n", buf);
	NetworkUtility::networkSetup(mEnemy,buf);
    
    //DEBUG Print the enemies list
    bzero(buf, 1024);
    strcpy(buf,NetworkUtility::shipListToCString(mEnemy)); 
    printf("This is the enemy's list: \n%s\n\n",buf);
}


void GameClient::play()
{  
	setup();
    
	Renderer::draw(mPlayer, mEnemy);// Render the blank board
    
	beginGame();
    
	delete mPlayer;
	delete mEnemy;
    
    
    
    
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets up the player and enemy ships. </summary>
void GameClient::beginGame()
{
    
    
    
	// ------------------------------------------------
    //      Main Shoot loop
    // ------------------------------------------------
	bool clientGoes;
    while (mPlayer->getStats()->getHitCount() != playerWin && mEnemy->getStats()->getHitCount() != enemyWin)
	{
		
		
		bzero(buf, 1024);
		strcpy(buf,client->ReadMessage());
		NetworkUtility::networkShoot(mEnemy,buf); // Might need to change  back to mEnemy
		Renderer::draw(mPlayer, mEnemy);
		cout << buf << endl;

		clientGoes = true;
		while (clientGoes)	//CLIENT GOES 
		{	
			clientGoes = mPlayer->shoot(mEnemy);
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
			if (clientGoes)
				cout<<"Direct hit! Take another shot!";
			else{
				cout<<"You missed. Turn over.";
				//send info on hits/misses to the enemy
				client->SendMessage(NetworkUtility::convertToString(mPlayer->getRecentHits(), mPlayer->getRecentMisses()));

				mPlayer->getRecentHits()->clear();
				mPlayer->getRecentMisses()->clear();
			}
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