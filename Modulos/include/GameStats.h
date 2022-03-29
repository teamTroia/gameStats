#pragma once
#include <utils/timer/timer.h>
#include <thread>
#include <clients/vision/visionclient.h>
#include <clients/referee/refereeclient.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RefereeStats.h"
#include "VisionStats.h"

#define bola 0
#define azul1 1
#define azul2 2
#define azul3 3
#define amarelo1 4
#define amarelo2 5
#define amarelo3 6

class GameStats{
private:    
    VisionClient *visionClient;
    RefereeClient *refereeClient;

    RefereeStats *refereeStats;
    VisionStats *visionStats;

    std::string to_string_with_precision(const float a_value, const int n = 1);
    void plotData(int imgMode);
public:
    GameStats();
    ~GameStats();
    void loop();
};