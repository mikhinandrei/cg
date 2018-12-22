//
//  utilities.cpp
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "utilities.h"


void Brezenham(int x0, int y0, int x1, int y1) {
    double dx, dy, e, x, y;
    e = -0.5;
    x = x0;
    y = y0;
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    bool flag = 0;
    int signX = x0 < x1 ? 1 : -1;
    int signY = y0 < y1 ? 1 : -1;
    Point(x0, y0).draw();
    if (dx < dy) {
        swap(x, y);
        swap(dx, dy);
        swap(signX, signY);
        swap(x1, y1);
        flag = 1;
    };
    while ((x != x1) || (y != y1)) {
        e = e + dy / dx;
        x += signX;
        if (flag) {
            Point(y,x).draw();
        }
        else {
            Point(x, y).draw();
        }
        if (e >= 0) {
            e -= 1;
            y += signY;
        }
        
    }
}

void Brezenham(Point start, Point finish) {
    Brezenham(start.x(), start.y(), finish.x(), finish.y());
}

int ClassifyLeftRight(Point a, Point b, Point c) {
    
    Point d_ba = Point(b.x() - a.x(), b.y() - a.y());
    Point d_ca = Point(c.x() - a.x(), c.y() - a.y());
    
    double det = d_ba.x() * d_ca.y() - d_ba.y() * d_ca.x();
    //    qInfo("det=%f", det);
    if (det < 0)
        return POS_LEFT;
    if (det > 0)
        return POS_RIGHT;
    return POS_UNDEF;
}

int ClassifyLeftRight(vector<Point> AB, Point c) {
    return ClassifyLeftRight(AB[0], AB[1], c);
}

double Distance(Point a, Point b) {
    return pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2);
}


int Classify(Point a, Point b, Point c) {
    if (a.x() == c.x() && a.y() == c.y())
        return POS_ORIGIN;
    if (b.x() == c.x() && b.y() == c.y())
        return POS_DEST;
    
    int lr_classify = ClassifyLeftRight(a,b,c);
    if(lr_classify != POS_UNDEF)
        return  lr_classify;
    
    if ( Distance(a, c) < Distance(b, c) )
        return POS_BEHIND;
    if ( Distance(a, c) > Distance(b, c) )
        return POS_BEYOND;
    
    return POS_BETWEEN;
    
}

int Classify(vector<Point> edge, Point c) {
    return Classify(edge[0], edge[1], c);
}

bool hasIntersect(vector<Point> AB, vector<Point> CD) {
    Point a = AB[0];
    Point b = AB[1];
    Point c = CD[0];
    Point d = CD[1];
    
    return intersect_1 (a.x(), b.x(), c.x(), d.x())
    && intersect_1 (a.y(), b.y(), c.y(), d.y());
}

void clipLine(vector<Point> line, vector<Point> points) {
    int xa = line[0].x();
    int xb = line[1].x();
    int ya = line[0].y();
    int yb = line[1].y();
    
    double t, t0 = 0.0, t1 = 1.0;
    int sx = xb - xa;
    int sy = yb - ya;
    double nx, ny, denom, num;
    int n = points.size();
    
    vector<int> px(n);
    vector<int> py(n);
    int j = 0;
    for (int i = 0; i < n; i++, j++) {
        px[j] = points[i].x();
        py[j] = points[i].y();
    }
    for (int i = 0; i < n; i++) {
        nx = py[(i + 1) % n] - py[i];
        ny = px[i] - px[(i + 1) % n];
        denom = (nx * sx + ny * sy);
        num = nx * (xa - px[i]) + ny * (ya - py[i]);
        if (denom != 0) {
            t = - num / denom;
            if (denom > 0) {
                if ((t > t0) && (t >= 0))
                    t0 = t;
            }
            else {
                if ((t < t1) && (t <= 1) && (t >= 0))
                    t1 = t;
            }
        }
        else {
            if (num > 0)
                return;
        }
    }
    if (t1 <= t0)
        swap(t0, t1);
    int xat = static_cast<int>(xa + t0 * (xb - xa));
    int xbt = static_cast<int>(xa + t1 * (xb - xa));
    int yat = static_cast<int>(ya + t0 * (yb - ya));
    int ybt = static_cast<int>(ya + t1 * (yb - ya));
    Brezenham(xat, yat, xbt, ybt);
}
