//
//  TestDrive.cpp
//  Assignment03
//
//  Created by ugorelik on 11-03-03.
//  Copyright 2011 Carleton University. All rights reserved.
//

/*
#include "PositionList.h"
#include "Position.h"
#include <iostream>

using std::cout;
using std::endl;
int main (int argc, const char * argv[])
{
    
 
 // insert code here...
 PositionList myList;
 PositionList myList2;
 
 // Add three positions to the list using =
 cout << "Add three positions using +=" << endl;
 Position * p1 = new Position(1,1);
 Position * p2 = new Position(2,2);
 Position * p3 = new Position(3,3);
 Position * p4 = new Position(1,1);
 Position * p5 = new Position(2,2);
 Position * p6 = new Position(3,3);
 
 // Point testing
 cout << "Testing points" << endl;
 cout << "Increment on (1,1)" << endl;
 cout << "Pre inc: " << ++*p1 << endl;
 cout << "Post inc: " << *p1++ << endl;
 
 cout << "Multiplication: "<< *p2 * *p3 << endl;
 
 
 bool myBool = *p4 == *p3;
 cout << "Equality: " << myBool << endl;
 
 myBool = *p3 == *p3;
 cout << "Equality: " << myBool << endl;
 cout << endl;
 
 
 cout << endl << "List stuff" << endl << endl;
 myList += *p1;
 myList += *p2;
 myList += *p3;
 myList2 += *p4;
 myList2 += *p5;
 myList2 += *p6;
 
 // Test =
 myList2 = myList;
 cout << myList2;
 
 cout<< myList;
 cout << endl;
 
 // Get the second ele
 cout << "Get the second element [1]" << endl;
 cout << myList[1] << endl;
 cout << endl;
 cout << endl;
 
 
 // Unions
 cout << "Testing remove (1,1) non-destructive" << endl;
 cout << myList << endl;
 cout << myList - *p1 << endl;
 cout << myList << endl << endl;
 
 // ij
 cout << "Testing add (1,1) non-destructive" << endl;
 cout << myList << endl;
 cout << myList + *p1 << endl;
 cout << myList << endl << endl;
 
 // Print contents
 cout << "Testing remove (1,1) estructive" << endl;
 cout << myList << endl;
 cout << myList - *p1 << endl;
 cout << endl;
 
 cout << "Testing add (1,1) non-destructive" << endl;
 cout << myList << endl;
 cout << myList + *p1 << endl;
 cout << endl;
 
 cout << endl;
 
 
 return 0; 
}
*/