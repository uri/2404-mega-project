///////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- //
//                                                                       //
// Developers: Uri Gorelik                                               //
//   Filename: Statistics.h                                              //
//                                                                       //
// --------------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////////////

#ifndef STATISTICS_H
#define STATISTICS_H


class Statistics {
    
public:
	Statistics();
    void addHit();
    void addMiss();
    int getHitCount();
    int getMissCount();
    
private:
    int mHits;
    int mMisses;
    
};
#endif