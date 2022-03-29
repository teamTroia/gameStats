#pragma once
#include <utils/timer/timer.h>
#include <thread>
#include <clients/vision/visionclient.h>
#include <clients/referee/refereeclient.h>
#include "RefereeStats.h"
#include "VisionStats.h"

class GameStats{
private:    
    VisionClient *visionClient;
    RefereeClient *refereeClient;

    RefereeStats *refereeStats;
    VisionStats *visionStats;
public:
    GameStats();
    ~GameStats();
    void loop();
};