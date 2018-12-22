//
//  point.cpp
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "point.hpp"
#include <iostream>


Point::Point(int x, int y) {
    _x = x;
    _y = y;
    _z = 0.0;
}

Point::Point(int x, int y, int z) {
    _x = x;
    _y = y;
    _z = z;
    _h = 1.0;
}

Point::Point(double x, double y, double z, double h) {
    _x = x;
    _y = y;
    _z = z;
    _h = h;
}

void Point::norm() {
    _z = _z / _h;
    _x = _x / _h;
    _y = _y / _h;
    _h = 1;
}

void Point::draw() {
    glVertex2d(_x + 250, 250 - _y);
}

Point operator * (Point p, Matrix M) {
    double x = p.x() * M.m[0][0] + p.y() * M.m[1][0] + p.z() * M.m[2][0] + p.h() * M.m[3][0];
    double y = p.x() * M.m[0][1] + p.y() * M.m[1][1] + p.z() * M.m[2][1] + p.h() * M.m[3][1];
    double z = p.x() * M.m[0][2] + p.y() * M.m[1][2] + p.z() * M.m[2][2] + p.h() * M.m[3][2];
    double h = p.x() * M.m[0][3] + p.y() * M.m[1][3] + p.z() * M.m[2][3] + p.h() * M.m[3][3];
    
    //cout << x << ' ' << y << ' ' << z <<  ' ' << h << endl;
    //float x = (p.x() * M.m[0][0] + p.y() * M.m[0][1] + p.z() * M.m[0][2] + p.h() * M.m[0][3]);
    //float y = (p.x() * M.m[1][0] + p.y() * M.m[1][1] + p.z() * M.m[1][2] + p.h() * M.m[1][3]);
    //float z = (p.x() * M.m[2][0] + p.y() * M.m[2][1] + p.z() * M.m[2][2] + p.h() * M.m[2][3]);
    //float h = (p.x() * M.m[3][0] + p.y() * M.m[3][1] + p.z() * M.m[3][2] + p.h() * M.m[3][3]);

    return Point(x, y, z, h);
}

Point operator *= (Point p, Matrix M) {
    return p * M;
}
