///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: Player.cpp                                                //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////



#include "Player.h"
//#include "PositionList.h"
#include "Statistics.h"
#include "Position.h"
#include "Board.h"
#include "ShipList.h"
#include "Ship.h"
#include "Random.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <limits>
using std::endl;
using std::cerr;
using std::cout;
using std::cin;

//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

Player::Player()
{
    mStats = new Statistics();
    mBoard = new Board();
    mHiddenBoard = new Board();
    
    mHitPos = new List<Position *>();
    mMissPos = new List<Position *>();
    mHitsandMisses = new List<Position *>();
    
	recentHits = new vector<Position>();
	recentMisses = new vector<Position>();
    seekers = 0;
}

Player::~Player()
{
    delete mHitsandMisses;
    delete mMissPos;
    delete mHitPos;
    delete mHiddenBoard;
    delete mBoard;
    delete mStats;
	delete recentHits;
	delete recentMisses;
    
}


//-----------------------------------------------------------------------//
// Methods                                                               //
//-----------------------------------------------------------------------//

void Player::printStats() {
    // Print the hits and misses in order
    const List<Position *>::ListNode<Position *> * curr = getHitsAndMisses()->head();
    while (curr != 0) {
        // Print the hits and misses
        cout << (*curr->data) << ", ";
        curr = curr->next();
    }
    
    cout << endl;
    
    // Number of moves
    int misses = getStats()->getMissCount();
    int hits = getStats()->getHitCount();
    int total = hits + misses;
    float ratio = (float)hits / (float)misses;
    

    
    cout << "Number of moves required for victory: "<< total << endl;
    cout << "Number of hits: "<< hits << endl;
    cout << "Number of misses: "<< misses << endl;
    
    if (misses != 0)
        cout << "Hit-Miss ratio: "<< ratio << endl;
    else    
        cout << "Hit-Miss ratio: PERFECT" << endl;    
}

//returns true if you can still shoot here, false if you have already shot here
bool Player::checkPosition(int x, int y){
	const List<Position *>::ListNode<Position *> * currPos = mHitPos->head();
    while (currPos != 0) {
        if ((currPos->data->x == x) && currPos->data->y == y) {
            return false;
        }
        currPos = currPos->next();
    }
    
    currPos = mMissPos->head();
    while (currPos != 0) {
        if ((currPos->data->x == x) && currPos->data->y == y) {
            return false;
        }
        currPos = currPos->next();
    }
	return true;
}
void Player::destroyShip(Player * opponent, Ship* ship){
    int xPos, yPos, width, height;
    xPos = ship->position().x;    // x Pos
    yPos = ship->position().y;    // y Pos
    width = ship->width();       // width
    height = ship->height();     // height
	for(int i = xPos; i < xPos+width; i++)
		for (int j = yPos; j < yPos+height; j++){
			if(ship->getDesign()[i-xPos][j-yPos]){
				firePointMissile(opponent,Position(i,j));
				mHitPos->add(new Position(i,j));    // Store hit in hitlist
				mStats->addHit();                   // Update stats
				mHitsandMisses->add(new Position(i,j));
			}
		}
    return;
}
//asks the player where they would like to target their missile. 
//If checkPos = true, will make sure they havent' already shot there
Position Player::querryTarget(bool check){
	int x =0; int y = 0;
	bool loop = true;
	//select coordinates for missile fire.
	cout << "Select a position for a " << missileName << ". {Or (-1,-1) for a seeker(" <<seekers<<") \n"
		<< "(Enter an x value from 0-24 and a y value from 0-14): ";
	//make sure the coordinates are valid
	while (loop){
		while (!(cin >> x >> y)){
			cerr << "Invalid input, try again: ";
			cin.clear(); // Remove error
			cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); // Flush
		}
		if( x == -1 && y == -1 && seekers > 0){
			return Position(x,y);
		}
		if (x > 24 || x < 0 || y > 14 || y < 0)
		{
			cout << "Attack Out Of Bounds Try Again...\n";
			loop = true;
		}
		else if(check && !checkPosition(x,y)){
			cerr << "Already shot there, try again: ";  // Print already shot message
			loop = true;
		}
		else
			loop = false;
	}
	return Position(x,y);
}

bool Player::firePointMissile(Player * opponent, Position pos){
	int x = pos.x;
	int y = pos.y;
	const List<Ship *>::ListNode<Ship *> * curr = opponent->getBoard()->getShipList()->head();
    while (curr != 0)
	{
        int xPos, yPos, sWidth, sHeight;
        xPos = curr->data->position().x;    // x Pos
        yPos = curr->data->position().y;    // y Pos
        sWidth = curr->data->width();       // width
        sHeight = curr->data->height();     // height
        
        // Check if it's in the bounding box
        if ( (xPos <= x && yPos <= y) && (x < (sWidth + xPos) && y < (sHeight + yPos)) ) {
            
            // If it is we check the same and if it's a one
            if (curr->data->getDesign()[x - xPos][y - yPos]) {
                mHitPos->add(new Position(x,y));    // Store hit in hitlist
                mStats->addHit();                   // Update stats
                mHitsandMisses->add(new Position(x,y));
				recentHits->push_back(Position(x,y));		//add to the queue for transmission
                return true;                        // Do not need to check other ships
            } else {
                mMissPos->add(new Position(x, y));  // Mark a miss
                mStats->addMiss();                  // Update stats
                mHitsandMisses->add(new Position(x,y));
				recentMisses->push_back(Position(x,y));		//add to the queue for transmission
                return false;                        // Do not need to check other ships
            }//inner if
        } else {
            curr = curr->next();  
        }//if
	}//while
    mHitsandMisses->add(new Position(x,y));
    mMissPos->add(new Position(x, y));  // Mark a miss
    mStats->addMiss();                  // Update stats
	recentMisses->push_back(Position(x,y));		//add to the queue for transmission
	return false;
	
}
bool Player::fireQuadMissile(Player *opponent, Position pos){
	int x =pos.x; int y = pos.y;
	firePointMissile(opponent,Position(x+1,y));
	firePointMissile(opponent,Position(x,y+1));
	firePointMissile(opponent,Position(x+1,y+1));
	return firePointMissile(opponent,pos);
}

bool Player::fireSeekerMissile(Player *opponent){
	int a = random(opponent->getBoard()->getShipList()->size()-2);//select the ship to fire at
	const List<Ship *>::ListNode<Ship *> * curr = opponent->getBoard()->getShipList()->head();	//create a ship node pointer
	for (int i = 0; i < a; i++)
		curr = curr->next();		//set the ship node pointer to the targetted ship
	//pick a random location in the ship's box to target the missile
	int x = random(curr->data->width()-1);
	int y = random(curr->data->height()-1);
	
	while (!curr->data->getDesign()[x][y]){
		x++;
		y++;
	}
	Position temp(x,y);
	temp+=curr->data->position();
	firePointMissile(opponent,temp);
	cout<<"Not really firing a seeker missile\n";//but actually it did
	//decrement the number of seekers
	seekers--;
	return true;
}

bool Player::fireNuke(Player *opponent, Position pos){
	int x = pos.x; int y = pos.y;
	//if it was a hit, nuke the ship, otherwise act as a quad
	const List<Ship *>::ListNode<Ship *> * curr = opponent->getBoard()->getShipList()->head();
    while (curr != 0)
	{
        int xPos, yPos, sWidth, sHeight;
        xPos = curr->data->position().x;    // x Pos
        yPos = curr->data->position().y;    // y Pos
        sWidth = curr->data->width();       // width
        sHeight = curr->data->height();     // height
        
        // Check if it's in the bounding box
        if ( (xPos <= x && yPos <= y) && (x < (sWidth + xPos) && y < (sHeight + yPos)) ) {
            
            // If it is we check the same and if it's a one
            if (curr->data->getDesign()[x - xPos][y - yPos]) {
				destroyShip(opponent,curr->data);
                return true;                        // Do not need to check other ships
            } else {			//if the NUKE missed
				break;                    // Do not need to check other ships
            }//inner if
        } else {
            curr = curr->next();  
        }//if
	}//while
	//only reached if the WARHEAD missed
	fireQuadMissile(opponent,pos);
    return false;    

}
int Player::selectMissile(){
	int ordnanceType = random(99);
	if(ordnanceType<74){			//regular missile
		strcpy(missileName, "POINT burst");
		return 0;
	}
	else if (ordnanceType<89){		//quad missile
		strcpy(missileName, "QUAD burst");
		return 1;
	}
	else if (ordnanceType<97){		//seeker missile
		seekers++;
		return 2;
	}
	else {							//NUKE
		strcpy(missileName, "nuclear WARHEAD");
		return 3;
	}
}
bool Player::shoot(Player * opponent)
{
	int ordnanceType = 0;
	Position pos;
	
	cout<<"Arming a missile...";
	ordnanceType = selectMissile();
	switch (ordnanceType){
		case 0:
			pos = querryTarget(true);
			if(pos == Position(-1,-1))
				return fireSeekerMissile(opponent);
			else
				return firePointMissile(opponent,pos);
			break;
		case 1:
			pos = querryTarget(true);
			if(pos == Position(-1,-1))
				return fireSeekerMissile(opponent);
			else
				return fireQuadMissile(opponent,pos);
			break;
		case 2:	//seeker
			char c;
			cout<< "A new seeker missile available. Use it now?(y/n)";
			while (!(cin >> c)){
				cerr << "Invalid input, try again: ";
				cin.clear(); // Remove error
				cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); // Flush
			}
			if (c=='y'){
				return fireSeekerMissile(opponent);
			}
			return true;
			break;
		case 3:
			pos = querryTarget(false);
			if(pos == Position(-1,-1))
				return fireSeekerMissile(opponent);
			else
				return fireNuke(opponent,pos);
			break;
	}

	
    return true;                             
}
//this is for networked games
bool Player::shoot(Player * opponent, Position pos, int ordnanceType)
{
	switch (ordnanceType){
		case 0:
			return firePointMissile(opponent,pos);
			break;
		case 1:
			return fireQuadMissile(opponent,pos);
			break;
		case 2:	//seeker
			return fireSeekerMissile(opponent);
			break;
		case 3:
			return fireNuke(opponent,pos);
			break;
	}
    return true;
}

void Player::addToLists(Position p, int hm) {
    if(hm) {
        mHitPos->add(new Position(p.x,p.y));
        mStats->addHit();
    } else {
        mMissPos->add(new Position(p.x, p.y));  
        mStats->addMiss();                  
    }
    
    // Add to hits and misses
    mHitsandMisses->add(new Position(p.x,p.y));
}

//-----------------------------------------------------------------------//
// Accessors                                                             //
//-----------------------------------------------------------------------//

Board * Player::getBoard()
{
    return mBoard;
}

Board * Player::getHiddenBoard()
{
    return mHiddenBoard;
}

Statistics * Player::getStats()
{
    return mStats;
}

List<Position *> * Player::getHits(void) {
    return mHitPos;
}
List<Position *> * Player::getMisses(void) {
    return mMissPos;
}

List<Position *> * Player::getHitsAndMisses(void) {
    return mHitsandMisses;
}

vector<Position> * Player::getRecentHits(){
	return recentHits;
}
vector<Position> * Player::getRecentMisses(){
	return recentMisses;
}



