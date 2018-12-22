//
//  bezier.cpp
//  cg
//
//  Created by Андрей Михин on 14.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "bezier.hpp"
#include <math.h>

int dist(int x, int y) {
    int d = abs(x) + abs(y);
    return d;
}

Bezier::Bezier(Point x0, Point x1, Point x2, Point x3) {
    p0 = new Point(x0.x(), x0.y());
    p1 = new Point(x1.x(), x1.y());
    p2 = new Point(x2.x(), x2.y());
    p3 = new Point(x3.x(), x3.y());
}

Point Bezier::curve(Point p0, Point p1, Point p2, Point p3, double t) {
    int x = round((1.0 - t)*(1.0 - t)*(1.0 - t)*(p0.x()*1.0) +
                 3 * (1.0 - t)*(1.0 - t)*(t)*(p1.x()*1.0) +
                 3 * (t)*(t)*(1.0 - t)*(p2.x()*1.0) +
                 (t)*(t)*(t)*(p3.x()*1.0));
    int y = round((1.0 - t)*(1.0 - t)*(1.0 - t)*(p0.y()*1.0) +
                  3 * (1.0 - t)*(1.0 - t)*(t)*(p1.y()*1.0) +
                  3 * (t)*(t)*(1.0 - t)*(p2.y()*1.0) +
                  (t)*(t)*(t)*(p3.y()*1.0));
    
    return Point(x, y);
}

void Bezier::draw() {
    int D = max<int>(abs(p0->x() - 2 * p1->x() + p2->x()) + abs(p0->y() - 2 * p1->y() + p2->y()),
                     abs(p1->x() - 2 * p2->x() + p3->x()) + abs(p1->y() - 2 * p2->y() + p3->y()));
    int n = 1 + ceil(pow(D*3.0, 0.5));
    double len = 1.0 / n;
    Point start = *p0;
    Point finish(0, 0);
    
    double t = 0.0;
    for (int i = 0; i <= n; ++i) {
        finish = curve(*p0, *p1, *p2, *p3, t);
        Brezenham(start, finish);
        start = finish;
        t += len;
    }
}
