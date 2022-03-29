#pragma once
#include "FFtypes.h"
#include "ffMath.h"
#include <string>
#include <iostream>

class Area{
private:
    int xInf;
    int xSup;
    int yInf;
    int ySup;
public:
    bool dentroDaArea(Point2f pt);

    Area(int xInf, int xSup, int yInf, int ySup);
};