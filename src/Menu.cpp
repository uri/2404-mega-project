///////////////////////////////////////////////////////////////////////////////////////////////
//						Created March 28th													//
//						Menu.cpp															//
//						Gets game type from user and runs appropriate game					//
//////////////////////////////////////////////////////////////////////////////////////////////

#include "Menu.h"
#include "GameSuper.h"
#include "GameClient.h"
#include "GameObserver.h"
#include "GamePvC.h"
#include "GameCvC.h"
#include "GameHost.h"
#include <string>
#include <limits>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


Menu::Menu()
{
	
	
}


//If they choose host, prompt Port Number
//If they choose client, prompt for server name ex. "lambda04" and Port Number ex. 60001


void Menu::run (void)
{
   
    while (true) {

		int x;
		bool look = false;

		while (!look)
		{
			cout << "================= BATTLESTAR HIDE AND SEEK ===================\n\n"
				 << "Welcome to Mission Control!\n"
				 <<	"Please enter the type of game you would like to play:\n\n"
				 << "<1> Player VS. Computer\n"
				 << "<2> Watch a Simulation (Comp VS Comp)\n"
				 << "<3> Player VS. Player\n"
				 << "<4> Observe\n"
				 << "<5> To Quit\n\n"
				 << "Enter number now (ex: 3): ";
			while (!(cin >> x))
			{	
				cerr << "Invalid input, please enter one of the indicated integers.\n";
				cin.clear();
				cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
					// Avoid weird looping errors
			}

			// Flush the rest of the input stream
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');


			if (x == 5) 
			{
			   cin.clear();
			   cout << "\nYou have Quit your current session!" ;
			   exit(0);
			}
        
			if (x > 4 || x < 1)
				cerr << "Selection out of Bounds, try again.\n\n";
			else look = true;
		}

		cout << "\n";

		string port;
		string servername;
		//Process x!!!!!!
		switch (x)
		{
			case 1:
				{
					cout << "You have selected the Player VS Computer game, it will begin shortly...\n";
					//call necessary P v C code
                    game = new GamePvC();
					break;
				}
			case 2:
				{
					cout << "You have selected the Watch a Simulation option, it will begin shortly...\n";
					//call necessary simulation code
                    game = new GameCvC();
					break;
				}
			case 3:
				{

					bool look = false;
					while (!look)
					{
						cout << "You have selected the Player VS Player option, please select a player type.\n";
						cout << "<1> Host\n<2> Client\n";
						while (!(cin >> x))
						{
							cerr << "Invalid input, please enter one of the indicated integers.\n";
							cin.clear();
							cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
								// Avoid weird looping errors
						}

						// Flush the rest of the input stream
						cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

						look = true;
						if (x == 1) 
						{
						   cout << "You have chosen to Host the game...\n";
						   game = new GameHost();
						   //call code to wait for client
						}
						else if (x == 2)
						{
						   cout << "You have chosen to be a Client, please enter the following...\n";
						   game = new GameClient();
						}
						else
						{
							cerr << "Selection out of Bounds, try again.\n\n";
							look = false;
						}
					}
					//call necessary P v P code
					break;
				}
			case 4:
				{
					cout << "You have selected the Obeserve option, you will join the game shortly...\n";
					game = new GameObserver();
					//call the necessary Obeserver code
					break;
				}
			default:
				{
					cout << "You broke the computer!";
					exit(0);
				}
		}
        
        game->play();

    
		cout << "Would you like to play another game (y/n)? ";
		char quickstart; cin >> quickstart;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

		if ((quickstart | 32) == 'y');
		else break;
    }//while

}