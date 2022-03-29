#pragma once
#include <clients/vision/visionclient.h>
#include "FFtypes.h"
#include "ffMath.h"

#define PosseAzul 0
#define PosseAmarelo 1
#define ladoEsquerdo 2
#define ladoDireito 3

class VisionStats{
private:
    VisionClient *visionClient;

    bool game_on;
    int qtdeRobots;
    Point2f tamCampo;

    int dataVision[4];

    double tempoAzul;
    double tempoAmarelo;

    double tempoEsquerdo;
    double tempoDireito;

    void setQtdeRobots(int qtde);
    infoPack vision(fira_message::Frame objects);
    void checkPossession(infoPack visionPack);
    void checkLadoCampo(infoPack visionPack);
public:
    VisionStats(VisionClient *visionClient);
    void checkVision(bool game_on);
    int getDataVision(int data);
};