#include "include/Area.h"

Area::Area(int xInf, int xSup, int yInf, int ySup){
    this->xInf = xInf;
    this->xSup = xSup;
    this->yInf = yInf;
    this->ySup = ySup;
}

bool Area::dentroDaArea(Point2f pt){
    return (pt.x > xInf and pt.x < xSup and pt.y > yInf and pt.y < ySup);
}