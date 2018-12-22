//
//  polygon.hpp
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef polygon_hpp
#define polygon_hpp

#include <stdio.h>
#include <vector>
#include "utilities.h"
#include "point.hpp"

const int FILL_TYPE_EVEN_ODD = 0;
const int FILL_TYPE_NON_ZERO_WINDING = 1;

const int CROSS_LEFT  = 1;
const int CROSS_RIGHT = -1;
const int INESETIONAL = 0;
const int TOUCHING   = 2;

using namespace std;

class Polygon {
public:
    Polygon(vector<Point>);
    void draw();
    bool isPointInside();
    bool isConvex();
    bool isComplex();
    bool isMyPixelEvenOdd(Point p);
    bool isMyPixelNonZeroWinding(Point p);
    void fillWith(const int FILL_TYPE);
    vector<Point> getEdge(int edgeNum);
    int EdgeType(vector<Point> edge, Point p);
    vector<Point> _points;
private:
    int topBorder, bottomBorder, rightBorder, leftBorder;
};

#endif /* polygon_hpp */
