///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: List.h                                                    //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------//
// Preambles                                                             //
//-----------------------------------------------------------------------//

#ifndef LIST_H
#define LIST_H


//class ListNode;

template <typename T>
class List
{
    //friend class Player;
    
//-----------------------------------------------------------------------//
// THE NODE : Nested Class                                               //
//-----------------------------------------------------------------------//
public:
    template < typename V >
    class ListNode
    {
        friend class List < V >;
        
    public:    
        ListNode (V data) { this->data = data; mNext = 0; }
        
    public:
        
        
        const ListNode *next (void) const { return mNext; }
        
        
    public:
        // Variables
        V data;
        
    private:
        ListNode * mNext;
        
    };
//-----------------------------------------------------------------------//
// End of NODE Class                                                     //
//-----------------------------------------------------------------------//
    
    
    
    
//-----------------------------------------------------------------------//
// LIST NODE                                                             //
//-----------------------------------------------------------------------//    
public:
	// Constructors
    List			(void);
	~List			(void);
    
    
	void add			(T);
	void clear			(void);
    
	int  size			(void) const;
	bool isEmpty		(void) const;
    
	const ListNode<T> * head	(void) const{ return mHead; }
    
    
private:
	// Variables
	int mSize;
	ListNode<T> * mHead;
};



//-----------------------------------------------------------------------//
// Constructors                                                          //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Constructor instantiating this class. </summary>

template <typename T>
List<T>::List (void)
{
	mSize = 0;
	mHead = 0;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Destructor deallocating class resources. </summary>

template <typename T>
List<T>::~List (void)
{
	clear();
}



//-----------------------------------------------------------------------//
// List                                                                  //
//-----------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////
/// <summary> Adds the specified ship to the end of this list. </summary>


template <typename T>
void List<T>::add (T data)
{
	++mSize;
	ListNode<T> *node = new ListNode<T>(data);
	node->mNext = mHead;
	mHead = node;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Removes all elements from this list. </summary>

template <typename T>
void List<T>::clear (void)
{
	mSize = 0;
	ListNode<T> *curr = mHead;
	while (curr != 0)
	{
		mHead = mHead->mNext;
        
		delete curr->data;
		delete curr;
		curr = mHead;
	}
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Returns the number of elements in this list. </summary>

template <typename T>
int List<T>::size (void) const
{
	return mSize;
}

///////////////////////////////////////////////////////////////////////////
/// <summary> Determines if this list is empty. </summary>

template <typename T>
bool List<T>::isEmpty (void) const
{
	return mSize == 0;
}



#endif
