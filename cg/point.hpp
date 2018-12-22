//
//  point.hpp
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "matrix.hpp"

class Point {
public:
    Point(int, int);
    Point(int, int, int);
    Point(double, double, double, double);
    double x() {return _x;}
    double y() {return _y;}
    double z() {return _z;}
    double h() {return _h;}
    void draw();
    void norm();
private:
    double _x;
    double _y;
    double _z;
    double _h;
};

Point operator * (Point, Matrix);
Point operator *= (Point, Matrix);

#endif /* point_hpp */
