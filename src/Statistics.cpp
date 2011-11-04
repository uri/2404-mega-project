///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: Statistics.cpp                                            //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

#include "Statistics.h"


Statistics::Statistics()
{
	mHits = 0;
	mMisses =0;
}

void Statistics::addHit() {
    mHits++;
}

void Statistics::addMiss() {
    mMisses++;
}

int Statistics::getHitCount() {
    return mHits;
}

int Statistics::getMissCount() {
    return mMisses;
}