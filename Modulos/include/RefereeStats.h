#pragma once
#include <clients/referee/refereeclient.h>

#define PenaltiAzul 0
#define PenaltiAmarelo 1
#define GoalkickAzul 2
#define GoalkickAmarelo 3
#define FreeballQ1 4
#define FreeballQ2 5
#define FreeballQ3 6
#define FreeballQ4 7

class RefereeStats{
private:
    RefereeClient *refereeClient;

    VSSRef::Foul lastFoul;

    int dataReferee[8];
public:
    RefereeStats(RefereeClient *refereeClient);
    void checkReferee();
    int getDataReferee(int data);
};