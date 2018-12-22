//
//  bezier.hpp
//  cg
//
//  Created by Андрей Михин on 14.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef bezier_hpp
#define bezier_hpp

#include "point.hpp"
#include "utilities.h"
#include <vector>
#include <math.h>
using namespace std;

const double T_STEP = 0.05;

class Bezier
{
public:
    Bezier(Point x0, Point x1, Point x2, Point x3);
    Point curve(Point, Point, Point, Point, double t);
    void draw();
    
private:
    Point *p0, *p1, *p2, *p3;
};


#endif /* bezier_hpp */
