///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: David Krutsko                                             //
//   Filename: ShipList.h                                                //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef SHIP_LIST_H
#define SHIP_LIST_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//


class Ship;

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a linked list of ships. </summary>

class ShipList
{
    friend class Player;
    
public:
	// Classes
	///////////////////////////////////////////////////////////////////////////
	/// <summary> Represents a single node inside the ship list. </summary>

	class Node
	{
        friend class ShipList;
        
	public:
		// Constructors
		///////////////////////////////////////////////////////////////////////////
		/// <summary> Instantiates this node with a specified ship. </summary>

		Node (Ship *ship) { this->ship = ship; mNext = 0; }

	public:
		// Accessors
		///////////////////////////////////////////////////////////////////////////
		/// <summary> Returns the data node following this node. </summary>

		const Node *next (void) const { return mNext; }


	public:
		// Variables
		Ship *ship;
        
	private:
		Node *mNext;
	};

public:
	// Constructors
	 ShipList			(void);
	~ShipList			(void);
    

	// ShipList
	void add			(Ship *ship);
	void clear			(void);

	int  size			(void) const;
	bool isEmpty		(void) const;

	const Node* head	(void) const;
    

private:
	// Variables
	int mSize;
	Node *mHead;
};

#endif // SHIP_LIST_H
