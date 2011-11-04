///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: PositionList.cpp                                          //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#include "PositionList.h"
#include "Position.h"


//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>

PositionList::PositionList (void)
{
	mSize = 0;
	mHead = 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Destructor deallocating class resources. </summary>

PositionList::~PositionList()
{
	clear();
}



//-----------------------------------------------------------------------//
// ShipList                                                              //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Adds the specified ship to the end of this list. </summary>

void PositionList::add (Position * pos)
{
	++mSize;
	Node *node = new Node (pos);
	node->mNext = mHead;
	mHead = node;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Removes all elements from this list. </summary>

void PositionList::clear (void)
{
	mSize = 0;
	Node *curr = mHead;
	while (curr != 0)
	{
		mHead = mHead->mNext;
        
		delete curr->pos;
		delete curr;
		curr = mHead;
	}
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the number of elements in this list. </summary>

int PositionList::size (void) const
{
	return mSize;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Determines if this list is empty. </summary>

bool PositionList::isEmpty (void) const
{
	return mSize == 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the first node in this list. </summary>

const PositionList::Node *PositionList::head (void) const
{
	
    return mHead;
    
}

//-----------------------------------------------------------------------//
// Operators                                                             //
//-----------------------------------------------------------------------//

Position & PositionList::operator[](unsigned int i) {
    
    const PositionList::Node * curr = mHead;
    
    for (int x = 0; x <i; x++) {
        curr = curr->next();
//        if (curr == 0) return 0;
    }
    
    // curr now has the right value
    return *(curr->pos);
}

PositionList & PositionList::operator=(const PositionList & list) {
    
    const PositionList::Node * curr = list.head();
    this->clear();
    while (curr != 0)
    {
        this->add(curr->pos);
        curr = curr->mNext;
    }
    
    return (*this);
}

PositionList & PositionList::operator=(const Position & p) {
    clear();
    add(new Position(p.x, p.y)); 
    return (*this);
}

PositionList PositionList::operator+(const Position & p) {
    PositionList returning;
    
    Position * pos = new Position(p.x,p.y);
    const PositionList::Node * curr = mHead;
    
    while (curr != 0)
    {
        Position * adding = new Position(curr->pos->x, curr->pos->y);
        returning += *adding;
        curr = curr->mNext;
    }
    
    returning += *pos;
    return returning;
}

PositionList & PositionList::operator+=(Position & p) {
    this->add(&p);
    return *this;
}

PositionList PositionList::operator-(const Position & p) {
    const PositionList::Node * curr = mHead;
    PositionList returning;
    
    while (curr != 0)
    {
        if (p != *curr->pos ) {
            Position * adding = new Position(curr->pos->x, curr->pos->y);
            returning += *adding;
        }
            
        curr = curr->mNext;
    }
    
    return returning;
}

PositionList & PositionList::operator-=(Position & p) {
    
    PositionList temp;
    temp = *this - p;
    clear();
    *this = temp;
    return *this;
}

bool PositionList::operator==(const PositionList & list) {
    const PositionList::Node * curr = mHead;
    const PositionList::Node * inner = list.head();
    
    while ( curr != 0) {
        while (inner !=0) {
            if (*curr->pos != *inner->pos)
                return false;
            inner = inner->next();
        }
        inner = list.head();
        curr = curr->next();
    }
    
    return true;
}

bool PositionList::operator!=(const PositionList & list) {
    return !(*this == list);
}

PositionList & PositionList::operator--(void) {
    const PositionList::Node * curr = mHead;
    const PositionList::Node * prev = mHead;
    
    while (curr != 0) {
        prev = curr;
        curr = curr->next();
    }
    
    *this -= *prev->pos;
    return *this;
}

ostream & operator<<( ostream & output, const PositionList & list){
    const PositionList::Node * curr = list.head();
    while (curr != 0) {
        output << *curr->pos << " ";
        curr = curr->next();
    }
    output << endl;
    return output;
}







