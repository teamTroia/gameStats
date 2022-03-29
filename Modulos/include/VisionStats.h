#pragma once
#include <clients/vision/visionclient.h>
#include "FFtypes.h"
#include "ffMath.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

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

    double dataVision[4];

    double tempoAzul;
    double tempoAmarelo;

    double tempoEsquerdo;
    double tempoDireito;

    double** tempoParteCampo;
    double tempoTotal;

    void setQtdeRobots(int qtde);
    infoPack vision(fira_message::Frame objects);
    void checkPossession(infoPack visionPack);
    void checkLadoCampo(infoPack visionPack);
    void checkParteCampo(infoPack visionPack);
    cv::Point2f cvt(cv::Point2f pt);
public:
    VisionStats(VisionClient *visionClient);
    void checkVision(bool game_on);
    double getDataVision(int data);
    void plotMapaCalor();
};