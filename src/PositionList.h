///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: PositionList.h                                            //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef POSITION_LIST_H
#define POSITION_LIST_H



//-----------------------------------------------------------------------//
// Classes                                                               //
//-----------------------------------------------------------------------//
#include <iostream>
class Position;

///////////////////////////////////////////////////////////////////////////
/// <summary> Represents a linked list of ships. </summary>
using std::ostream;
using std::endl;
class PositionList
{
    friend class Player; // CHECK: May not be needed
    friend ostream & operator<<( ostream &, const PositionList &);
public:
	// Classes
	///////////////////////////////////////////////////////////////////////////
	/// <summary> Represents a single node inside the ship list. </summary>
    
	class Node
	{
        friend class PositionList;
        
	public:
		// Constructors
		///////////////////////////////////////////////////////////////////////////
		/// <summary> Instantiates this node with a specified ship. </summary>
        
		Node (Position *pos) { this->pos = pos; mNext = 0; }
        
	public:
		// Accessors
		///////////////////////////////////////////////////////////////////////////
		/// <summary> Returns the data node following this node. </summary>
        
		const Node *next (void) const { return mNext; }
        
        
	public:
		// Variables
		Position *pos;
        
	private:
		Node *mNext;
	};
    
public:
	// Constructors
    PositionList			(void);
	~PositionList			(void);
    
    
	// ShipList
	void add			(Position * pos);
	void clear			(void);
    
	int  size			(void) const;
	bool isEmpty		(void) const;
    
	const Node* head	(void) const;
    
    // Operators
    Position & operator[](unsigned int);
    PositionList & operator=(const PositionList &);
    PositionList & operator=(const Position & p);
    PositionList operator+(const Position & p);
    PositionList & operator+=(Position & p);
    PositionList operator-(const Position & p);
    PositionList & operator-=(Position & p);
    bool operator==(const PositionList & list);
    bool operator!=(const PositionList & list);
    PositionList & operator--(void);
    
    
private:
	// Variables
	int mSize;
	Node *mHead;
};



#endif // POSITION_LIST_H
