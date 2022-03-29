#pragma once

class Point2f{
  public:
  double x;
  double y;
  Point2f(double x, double y){
    this->x = x;
    this->y = y;
  }
  Point2f operator+(Point2f& pt2){
    Point2f result;
    result.x = x + pt2.x;
    result.y = y + pt2.y;
    return result;
  }
  Point2f operator-(Point2f& pt2){
    Point2f result;
    result.x = x - pt2.x;
    result.y = y - pt2.y;
    return result;
  }
  Point2f operator*(double& c){
    Point2f result;
    result.x = c * x;
    result.y = c * y;
    return result;
  }
  bool operator==(Point2f& pt2){
    return x==pt2.x && y==pt2.y;
  }
  Point2f(){};
};

struct objectInfo {
	Point2f position = Point2f(0,0);
	double psi;
};

struct infoPack {
	objectInfo blueRobots[5];
	objectInfo yellowRobots[5];
	objectInfo ball;
};