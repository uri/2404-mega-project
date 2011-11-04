///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, Uri Gorelik                                //
//   Filename: Renderer.cpp                                              //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "Renderer.h"
#include "Ship.h"
#include "Board.h"
#include "ShipList.h"
//#include "PositionList.h"
#include "List.h"
#include "Player.h"
#include "Position.h"

#include <iostream>
using std::cout;
using std::endl;



//-----------------------------------------------------------------------//
// Renderer                                                              //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Draws the player and enemy boards to the screen. </summary>

void Renderer::draw (Player *player, Player *enemy)
{
	const int width  = 100;
	const int height = 35;

	char buffer[width][height];
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			buffer[x][y] = ' ';



	//-----------------------------------------------------------------------//
	// Outer Border                                                          //
	//-----------------------------------------------------------------------//

	buffer[0      ][0       ] = '+';
	buffer[width-1][0       ] = '+';
	buffer[0      ][height-1] = '+';
	buffer[width-1][height-1] = '+';

	for (int x = 1; x < width-1; ++x)
	{
		buffer[x][0       ] = '-';
		buffer[x][height-1] = '-';
	}

	for (int y = 1; y < height-1; ++y)
	{
		buffer[0      ][y] = '|';
		buffer[width-1][y] = '|';
	}



	//-----------------------------------------------------------------------//
	// Player Border                                                         //
	//-----------------------------------------------------------------------//
	
	for (int i = 1, x = 4; x < (player->getBoard()->mWidth+2) * 2; x += 2, ++i)
	{
		if (i % 5 == 0)
		{
			buffer[x][2                    ] = '|';
			buffer[x][(player->getBoard()->mHeight+1)*2] = '|';
		}

		else
		{
			buffer[x][2                    ] = '-';
			buffer[x][(player->getBoard()->mHeight+1)*2] = '-';
		}
	}

	for (int i = 1, y = 3; y < (player->getBoard()->mHeight+1) * 2; y += 2, ++i)
	{
		if (i % 5 == 0)
		{
			buffer[3                   ][y] = '-';
			buffer[(player->getBoard()->mWidth+2)*2][y] = '-';
		}

		else
		{
			buffer[3                   ][y] = '|';
			buffer[(player->getBoard()->mWidth+2)*2][y] = '|';
		}
	}



	//-----------------------------------------------------------------------//
	// Enemy Border                                                          //
	//-----------------------------------------------------------------------//

	for (int i = 1, x = 65; x < enemy->getBoard()->mWidth + 65; ++x, ++i)
	{
		if (i % 5 == 0)
		{
			buffer[x][9                ] = '|';
			buffer[x][enemy->getBoard()->mHeight+10] = '|';
		}

		else
		{
			buffer[x][9                ] = '-';
			buffer[x][enemy->getBoard()->mHeight+10] = '-';
		}
	}

	for (int i = 1, y = 10; y < enemy->getBoard()->mHeight + 10; ++y, ++i) // Used to be player instead of enemy.. Bug?
	{
		if (i % 5 == 0)
		{
			buffer[64              ][y] = '-';
			buffer[enemy->getBoard()->mWidth+65][y] = '-';
		}

		else
		{
			buffer[64              ][y] = '|';
			buffer[enemy->getBoard()->mWidth+65][y] = '|';
		}
	}



	//-----------------------------------------------------------------------//
	// Player Board                                                          //
	//-----------------------------------------------------------------------//
	
	for (const List<Ship *>::ListNode<Ship *> *node = player->getBoard()->mShips->head(); node != 0; node = node->next())
	{
		int xPos = node->data->position().x;
		int yPos = node->data->position().y;

		for (int x = 0; x < node->data->width(); ++x)
			for (int y = 0; y < node->data->height(); ++y) 
                if (node->data->mDesign[x][y])
					buffer[(xPos+x)*2+4][(yPos+y)*2+3] = node->data->icon();
	}

    // Hits
    for (const List<Position *>::ListNode<Position *> * node = enemy->getHits()->head(); node != 0; node = node->next())
	{
		int xPos = node->data->x;
		int yPos = node->data->y;
        
        buffer[(xPos)*2+4][(yPos)*2+3] = 'X';
	}
    
    for (const List<Position *>::ListNode<Position *> *node = enemy->getMisses()->head(); node != 0; node = node->next())
	{
		int xPos = node->data->x;
		int yPos = node->data->y;
        
        buffer[(xPos)*2+4][(yPos)*2+3] = '0';
	}

	//-----------------------------------------------------------------------//
	// Enemy Board                                                           //
	//-----------------------------------------------------------------------//

	for (const List<Ship *>::ListNode<Ship *> *node = enemy->getBoard()->mShips->head(); node != 0; node = node->next())
	{
		int xPos = node->data->position().x;
		int yPos = node->data->position().y;

		for (int x = 0; x < node->data->width(); ++x)
			for (int y = 0; y < node->data->height(); ++y)
				if (node->data->mDesign[x][y])
					buffer[xPos+x+65][yPos+y+10] = node->data->icon();
	}
    
    // Enemy hits and misses
    // Hits
    for (const List<Position *>::ListNode<Position *> *node = player->getHits()->head(); node != 0; node = node->next())
	{
		int xPos = node->data->x;
		int yPos = node->data->y;
        
        buffer[xPos + 65][yPos + 10] = 'X';
	}
    
    for (const List<Position *>::ListNode<Position *> *node = player->getMisses()->head(); node != 0; node = node->next())
	{
		int xPos = node->data->x;
		int yPos = node->data->y;
        
        buffer[xPos + 65][yPos + 10] = '0';
	}



	//-----------------------------------------------------------------------//
	// Print the buffer                                                      //
	//-----------------------------------------------------------------------//

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
			cout << buffer[x][y];
		cout << endl;
	}
}
