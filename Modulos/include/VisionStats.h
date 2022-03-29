#pragma once
#include <clients/vision/visionclient.h>
#include "FFtypes.h"
#include "ffMath.h"
#include "Area.h"

#define PosseAzul 0
#define PosseAmarelo 1
#define PosseNeutro 2

class VisionStats{
private:
    VisionClient *visionClient;

    bool game_on;
    int qtdeRobots;
    Point2f tamCampo;

    int dataVision[3];

    double tempoAzul;
    double tempoAmarelo;
    double tempoNeutro;

    void setQtdeRobots(int qtde);
    infoPack vision(fira_message::Frame objects);
    void checkPossession(infoPack visionPack);
public:
    VisionStats(VisionClient *visionClient);
    void checkVision(bool game_on);
    int getDataVision(int data);
};