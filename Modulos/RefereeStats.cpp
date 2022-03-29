#include "include/RefereeStats.h"

RefereeStats::RefereeStats(RefereeClient *refereeClient){
    this->refereeClient = refereeClient;

    for (int i = 0; i < 8; i ++){
        dataReferee[i] = 0;
    }
}

void RefereeStats::checkReferee(){
    VSSRef::Foul currentFoul = refereeClient->getLastFoul();

    if (lastFoul != currentFoul){
        if (currentFoul == VSSRef::Foul::PENALTY_KICK){
            if (refereeClient->getLastFoulColor() == VSSRef::Color::BLUE) dataReferee[PenaltiAzul]++;
            else if (refereeClient->getLastFoulColor() == VSSRef::Color::YELLOW) dataReferee[PenaltiAmarelo]++;
        } 
        
        else if (currentFoul == VSSRef::Foul::GOAL_KICK){
            if (refereeClient->getLastFoulColor() == VSSRef::Color::BLUE) dataReferee[GoalkickAzul]++;
            else if (refereeClient->getLastFoulColor() == VSSRef::Color::YELLOW) dataReferee[GoalkickAmarelo]++;
        }
        
        else if (currentFoul == VSSRef::Foul::FREE_BALL){
            if (refereeClient->getLastFoulQuadrant() == VSSRef::Quadrant::QUADRANT_1) dataReferee[FreeballQ1]++;
            else if (refereeClient->getLastFoulQuadrant() == VSSRef::Quadrant::QUADRANT_2) dataReferee[FreeballQ2]++;
            else if (refereeClient->getLastFoulQuadrant() == VSSRef::Quadrant::QUADRANT_3) dataReferee[FreeballQ3]++;
            else if (refereeClient->getLastFoulQuadrant() == VSSRef::Quadrant::QUADRANT_4) dataReferee[FreeballQ4]++;
        }

        lastFoul = currentFoul;
    }
}

int RefereeStats::getDataReferee(int data){
    return dataReferee[data];
}