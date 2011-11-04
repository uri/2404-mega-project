
#ifndef NETWORK_UTILITY_H
#define NETWORK_UTILITY_H

#include <vector>
#include <cstring>
#include <string>

using namespace std;

class Player;
class Position;

#include "List.h"

//NETWORK UTILITY H FILE
//NETWORKUTILITY is used to parse data that is to be transmitted
class NetworkUtility
{
    
public:
    // Parser
	static bool networkSetup(Player * player, char * str);
	static bool networkShoot(Player * player, char * str);
    static vector<string> parseInput(char *s, char c );
    static vector<string> getType(char * str);
    static vector<string> getPositions(char * str);
    static vector<string> readPositions(char * str);

    // Endcoder
    static const char * shipListToCString(Player * target);
    static const char * shotToCString(int x, int y, char m);
    static const char * convertToString(vector<Position> *,vector<Position> *);
	static const char * convertToStringObserver(List<Position *> *,List<Position *> *);
};

#endif // NETWORKUTILITY_H