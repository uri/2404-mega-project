
#include "NetworkUtility.h"
#include "Player.h"
#include "Board.h"
#include "List.h"
#include "Ship.h"
#include "ShipTypes.h"

#include "Position.h"

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>


bool NetworkUtility::networkShoot(Player * player, char * str){
	stringstream stream, innerStream;
	char temp[100];
	Position pos;
	int type;

	stream << str;

	//check the type to ensure its a shoot string
	stream.getline(temp,100, '_');
	if (strcmp(temp,"shoot"))
		return false;
	while(stream.getline(temp,100,',')){
		innerStream << temp;
		innerStream.getline(temp,5,'-');
		pos.x = atoi(temp);
		innerStream.getline(temp,5,'-');
		pos.y = atoi(temp);
		
		strcpy(temp, innerStream.str().c_str());
        type = temp[strlen(temp) - 1] - '0';
		cout << pos << type;
		player->addToLists(pos,type);

		// Clear inner stream
        innerStream.str("");
        bzero(temp,100);
	}

	return true;
}

bool NetworkUtility::networkSetup(Player * player, char * str) {
	stringstream stream;
    stringstream innerStream;
	char temp [100];
	int x, y;
    int orientation;
	char type[2];
    char realType;
	Ship * ship;

	stream << str;

    // Split it to check the type (should be 'setup')
	stream.getline(temp, 100,'_');
    // Make sure it's the right command
	if (strcmp(temp,"setup"))
		return false;
    
    
	while (stream.getline(temp,100,',')){
        
        innerStream << temp;
        
		innerStream.getline(temp,4,'-');
        x = atoi(temp);
		
        innerStream.getline(temp,4,'-');
        y = atoi(temp);
        
        innerStream.getline(temp,4,'-');
        orientation = atoi(temp);
		
        strcpy(type, innerStream.str().c_str());
        realType = type[strlen(type) - 1];
        
        printf("Current x: %d, current y: %d, type: %c, the orientation:%d\n", x,y,realType, orientation);
        
		switch (realType){
			case 'G':
				ship = new Battlestar();
				break;
			case 'P' :
				ship = new Raptor();
				break;
			case '^' :
				ship = new Viper();
				break;
			case 'B' :
				ship = new Basestar();
				break;
			case 'H' :
				ship = new HeavyRaider();
				break;
			case 'd' :
				ship = new Raider();
				break;
		}
		ship->setPosition(Position(x,y));
        ship->setOrientation((Ship::Orientation)orientation);
		ship->createShip();
		player->getBoard()->addShip(ship);
        
        // Clear inner stream
        innerStream.str("");
        bzero(temp,100);
	}
	return true;
}


vector<string> NetworkUtility::parseInput(char *str, char c)
{
    stringstream stream;
    vector<string> vect;
   
	while (stream.getline(str, 100, c))
	{
		vect.push_back(str);
	}
	return vect;
}

vector<string> NetworkUtility::getType(char * str)
{
    stringstream stream;
	vector<string> vect;
	char c;
	c = '_';
	while (stream.getline(str, 100, c))
	{
		vect.push_back(str);
	}
	return vect;
}

vector<string> NetworkUtility::getPositions(char * str)
{
    stringstream stream;
	vector<string> vect;
	char c;
	c = ',';
	while (stream.getline(str, 100, c))
	{
		vect.push_back(str);
	}
	return vect;

}

vector<string> NetworkUtility::readPositions(char * str)
{
    stringstream stream;
	vector<string> vect;
	char c;
	c = '-';
	while (stream.getline(str, 100, c))
	{
		vect.push_back(str);
	}
	return vect;

}


const char * NetworkUtility::shipListToCString(Player * target)
{
    stringstream ss;
    ss << "setup_";
    
	List<Ship *> * temp = target->getBoard()->getShipList();
	//Node* head = temp->head();
    const List<Ship *>::ListNode<Ship *> * curr = temp->head();
	while (curr != 0)
	{
        ss << curr->data->position().x;
        ss << "-";
        ss << curr->data->position().y;
        ss << "-";
        ss << curr->data->getOrientation();
        ss << "-";
        ss << curr->data->icon();
        ss << ",";
//        cout << "This is the orientation from getOrientation" << curr->data->getOrientation() << endl;

        curr = curr->next();
	}
    
    return ss.str().c_str();
}

const char * NetworkUtility::shotToCString(int x, int y, char m)
{
    stringstream ss;
    ss << "shoot_";
    
    ss << x;
    ss << "-";
    ss << y;
    ss << "-";
    ss << m;
    ss << ",";
    
    return ss.str().c_str();
}


const char * NetworkUtility::convertToString(vector<Position> * hits,vector<Position> * misses)
{
    stringstream ss;
    ss << "shoot_";
    
	vector<Position> * temp = hits;
    
    Position p;
    
    vector<Position>::iterator itr;
    for (itr = temp->begin(); itr != temp->end(); ++itr) {
        
        Position pos = *itr;
        
        
        ss << pos.x;
        ss << "-";
        ss << pos.y;
        ss << "-";
        ss << "1";
        ss << ",";
    }
    
    temp = misses;
    
    for (itr = temp->begin(); itr != temp->end(); ++itr) {
        
        Position pos = *itr;
        
        
        ss << pos.x;
        ss << "-";
        ss << pos.y;
        ss << "-";
        ss << "0";
        ss << ",";
    }
    
    return ss.str().c_str();
}

const char * NetworkUtility::convertToStringObserver(List<Position *> * hits,List<Position *> * misses)
{
    stringstream ss;
    ss << "shoot_";
    
	List<Position *> * temp = hits;
    
    Position *pos;

	for (const List<Position *>::ListNode<Position *> *node = temp->head(); node != 0; node = node->next())
	{
		pos = node->data;
		ss << pos->x;
        ss << "-";
        ss << pos->y;
        ss << "-";
        ss << "1";
        ss << ",";
	}

    temp = misses;
    
    for (const List<Position *>::ListNode<Position *> *node = temp->head(); node != 0; node = node->next())
	{
		pos = node->data;
		ss << pos->x;
        ss << "-";
        ss << pos->y;
        ss << "-";
        ss << "0";
        ss << ",";
	}

    
    return ss.str().c_str();
}








