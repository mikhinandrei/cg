//
//  utilities.h
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef utilities_h
#define utilities_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <GLUT/GLUT.h>

#include "point.hpp"

using namespace std;

const double EPS = 10e-6;

// positiional consts
const int POS_UNDEF = 0;

const int POS_LEFT = -1;
const int POS_RIGHT = 1;

const int POS_BEHIND = 2;
const int POS_BEYOND = 3;

const int POS_ORIGIN = 4;
const int POS_DEST = 5;

const int POS_BETWEEN = 6;

// colisions consas
const int PARALLEL  = 0;
const int COLLINIAR = 1;
const int INTERSECT = 2;

void Brezenham(int, int, int, int);
void Brezenham(Point, Point);
int ClassifyLeftRight(Point, Point, Point);
int ClassifyLeftRight(vector<Point> AB, Point c);
int Classify(Point a, Point b, Point c);
int Classify(vector<Point> edge, Point c);
double Distance(Point a, Point b);

inline int area (Point a, Point b, Point c) {
    return (b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x());
}

inline bool intersect_1 (int a, int b, int c, int d) {
    if (a > b)  swap (a, b);
    if (c > d)  swap (c, d);
    return max(a,c) <= min(b,d);
}

bool hasIntersect(vector<Point> AB, vector<Point> CD);
void clipLine(vector<Point>, vector<Point>);

#endif /* utilities_h */
