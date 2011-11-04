#ifndef MENU_H
#define MENU_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//
class GameSuper;

///////////////////////////////////////////////////////////////////////////
/// <summary> Controls the primary aspects of the game. </summary>

class Menu
{
public:
	// Game
	Menu();
	void run ();
private:
	GameSuper * game;
    
};

#endif //End Menu