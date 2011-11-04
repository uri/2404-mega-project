///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik, Eric Rhodes                                  //
//   Filename: Player.h                                                  //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "List.h"
#include <vector>

class Board;
class Statistics;
class Position;
class Ship;

using std::vector;


class Player
{
public:
    
    // Constructor
    Player(void);
    ~Player(void);
    
    // Accessors
    Board * getBoard(void);
    Board * getHiddenBoard(void);
    Statistics * getStats(void);
    
    List<Position *> * getHits(void);
    List<Position *> * getMisses(void);
    List<Position *> * getHitsAndMisses(void);
    
    void addToLists(Position, int);

	vector<Position> * getRecentHits();
	vector<Position> * getRecentMisses();
    
    // Methods
	void clearOutputLists();		//clears the recentHits and recentMisses lists
	Position querryTarget(bool);
	bool firePointMissile(Player * opponent,Position pos);
	bool fireQuadMissile(Player *opponent, Position pos);
	bool fireSeekerMissile(Player *opponent);
	bool fireNuke(Player *opponent, Position pos);
	int selectMissile();		
	void destroyShip(Player *, Ship *);
	bool checkPosition(int, int);
    bool shoot(Player *, Position pos, int ordnanceType);	//for when position is pregenereated (AI or networked foe)
    bool shoot(Player *);				//for when you shoot
    void printStats();
private:
    int seekers;
	char missileName[15];
	Board * mBoard;
    Board * mHiddenBoard;
    Statistics * mStats;
    
    List<Position *> * mHitPos;
    List<Position *> * mMissPos;
    List<Position *> * mHitsandMisses;
	vector<Position> * recentHits;
	vector<Position> * recentMisses;


};
#endif