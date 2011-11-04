//
//  GamePvC.cpp
//  Mega Project
//
//  Created by ugorelik on 11-03-31.
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "GamePvC.h"
#include "Board.h"
#include "Player.h"
#include "Random.h"
#include "Renderer.h"
#include "ShipTypes.h"
#include "Statistics.h"
#include <string>

#include <limits>
#include <iostream>
using std::endl;
using std::cerr;
using std::cout;
using std::cin;



//-----------------------------------------------------------------------//
// Game                                                                  //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Runs the game and handles restarting it. </summary>

//Game Constructor for Player VS Computer Game
GamePvC::GamePvC()
{
	playerWin = 43;
    enemyWin = 40;
    
	
	mPlayer = new Player(); //these might need to be moved into switch statement
	mEnemy  = new Player();
    
}

void GamePvC::setup()
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
            
            //	createShipPosition (mEnemy->getBoard(), new Basestar());
            createShipPosition (mEnemy->getBoard(), new HeavyRaider());
            //	createShipPosition (mEnemy->getBoard(), new HeavyRaider());
            //	createShipPosition (mEnemy->getBoard(), new Raider());
            //	createShipPosition (mEnemy->getBoard(), new Raider());
            //	createShipPosition (mEnemy->getBoard(), new Raider());
            //	createShipPosition (mEnemy->getBoard(), new Raider());
            //	createShipPosition (mEnemy->getBoard(), new Raider());
            playerWin = 4;
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
            
            createShipPosition (mEnemy->getBoard(), new Basestar());
            createShipPosition (mEnemy->getBoard(), new HeavyRaider());
            createShipPosition (mEnemy->getBoard(), new HeavyRaider());
            createShipPosition (mEnemy->getBoard(), new Raider());
            createShipPosition (mEnemy->getBoard(), new Raider());
            createShipPosition (mEnemy->getBoard(), new Raider());
            createShipPosition (mEnemy->getBoard(), new Raider());
            createShipPosition (mEnemy->getBoard(), new Raider());
        }
}

//Run the Game
void GamePvC::play()
{
	
        
	setup();
    
	Renderer::draw(mPlayer, mEnemy);
    
	beginGame();
    
	delete mPlayer;
	delete mEnemy;
    
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets up the player and enemy ships. </summary>
void GamePvC::beginGame()
{
	// Main game loop, player goes first
	bool playerGoes = true;   // Player or computer
    
    
	while (mPlayer->getStats()->getHitCount() != playerWin && mEnemy->getStats()->getHitCount() != enemyWin)
	{
		if (playerGoes) {
            
			playerGoes = mPlayer->shoot(mEnemy);
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
			if (playerGoes)
				cout<<"Direct hit! Take another shot!\n";
			else
				cout<<"You missed. Turn over.\n";
            
		} 
		else	//COMPUTER GOES 
		{	
		
			int x = random(23);
			int y = random(13);
			playerGoes = !mEnemy->shoot(mPlayer,Position(x,y),mEnemy->selectMissile());
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			if (!playerGoes)
				cout<<"Enemy scored a direct hit! It gets another shot!\n";
			else
				cout<<"Computer missed. Your turn\n";
		}
        
	}
    
    
    
    // Game Over
    Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
    if (mPlayer->getStats()->getHitCount() == playerWin) {
        cout << "You Win!" << endl;
    } else {
        cout << "The Computer Wins!!" << endl;
    }
    
    mPlayer->printStats();
    mEnemy->printStats();
    cout<< "GAME OVER"<< endl;
    
}