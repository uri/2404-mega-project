//
//  GameSingle.cpp
//  Mega Project
//
//  Created by ugorelik on 11-03-31.
//  Copyright 2011 Carleton University. All rights reserved.
//

#include "GameCvC.h"
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

//Game Constructor for Computer Vs Computer Game
GameCvC::GameCvC()
{
	playerWin = 0;//43;
    enemyWin = 0;//40;
    
	
	mPlayer = new Player(); //these might need to be moved into switch statement
	mEnemy  = new Player();
    
}

//sets up all game ships for both computers
void GameCvC::setup()
{
    //create player 1 ships
    createShipPosition (mPlayer->getBoard(), new Battlestar());
    createShipPosition (mPlayer->getBoard(), new Raptor());
    createShipPosition (mPlayer->getBoard(), new Raptor());
    createShipPosition (mPlayer->getBoard(), new Raptor());
    createShipPosition (mPlayer->getBoard(), new Viper());
    createShipPosition (mPlayer->getBoard(), new Viper());
    createShipPosition (mPlayer->getBoard(), new Viper());
    createShipPosition (mPlayer->getBoard(), new Viper());
    //create player 2 ships
    createShipPosition (mEnemy->getBoard(), new Basestar());
    createShipPosition (mEnemy->getBoard(), new HeavyRaider());
	createShipPosition (mEnemy->getBoard(), new HeavyRaider());
	createShipPosition (mEnemy->getBoard(), new Raider());
    createShipPosition (mEnemy->getBoard(), new Raider());
    createShipPosition (mEnemy->getBoard(), new Raider());
    createShipPosition (mEnemy->getBoard(), new Raider());
    createShipPosition (mEnemy->getBoard(), new Raider());
	//tally the required hits on player 1 for player 2 to win
	const List<Ship *>::ListNode<Ship *> * curr = mPlayer->getBoard()->getShipList()->head();
	while (curr != 0)
	{
		for(int x = 0; x < curr->data->width(); x++)
			for(int y = 0; y < curr->data->height(); y++)
				if(curr->data->getDesign()[x][y])
					enemyWin++;

		curr = curr->next();  
	}
	curr = mEnemy->getBoard()->getShipList()->head(); 
	while (curr != 0)
	{
		for(int x = 0; x < curr->data->width(); x++)
			for(int y = 0; y < curr->data->height(); y++)
				if(curr->data->getDesign()[x][y])
					playerWin++;

		curr = curr->next();  
	}

        

}


//Runs the games
void GameCvC::play()
{
	setup();
    
	Renderer::draw(mPlayer, mEnemy);
    
	beginGame();
    
	delete mPlayer;
	delete mEnemy;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Sets up the player and enemy ships. </summary>
void GameCvC::beginGame()
{
	// Main game loop, player goes first
	bool playerGoes = true;   // Player or computer
    
    
	while (mPlayer->getStats()->getHitCount() != playerWin && mEnemy->getStats()->getHitCount() != enemyWin)
	{
		if (playerGoes) {
			cout<<"Computer 1 is firing.\n";
			int x = random(23);
			int y = random(13);
			playerGoes = mPlayer->shoot(mEnemy,Position(x,y),mEnemy->selectMissile());
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			//cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
			if (playerGoes)
				cout<<"Direct hit! Computer 1 gets another shot!\n";
			else
				cout<<"Computer 1 missed. Turn over.\n";
            
		} 
		else	//COMPUTER GOES 
		{	
            cout<<"Computer 2 is firing.\n";
			int x = random(23);
			int y = random(13);
			playerGoes = !mEnemy->shoot(mPlayer,Position(x,y),mEnemy->selectMissile());
			Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
			if (!playerGoes)
				cout<<"Computer 2 scored a direct hit! It gets another shot!\n";
			else
				cout<<"Computer 2 missed. Turn over\n";
		}
        
	}
    
    
    
    // Game Over
    Renderer::draw(mPlayer, mEnemy);    // Draw after every turn
    if (mPlayer->getStats()->getHitCount() == playerWin) {
        cout << "Player 1 Wins!" << endl;
    } else {
        cout << "Player 2 Wins!" << endl;
    }
    
    mPlayer->printStats();
    mEnemy->printStats();
    cout<< "GAME OVER"<< endl;
    
}