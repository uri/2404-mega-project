///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko, Uri Gorelik                                //
//   Filename: Renderer.h                                                //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef RENDERER_H
#define RENDERER_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//

class Player;

///////////////////////////////////////////////////////////////////////////
/// <summary> Responsible for outputting everything to the screen. </summary>

class Renderer
{
public:
	// Renderer
	static void draw (Player *player, Player *enemy);
};

#endif // RENDERER_H