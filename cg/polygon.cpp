//
//  polygon.cpp
//  cg
//
//  Created by Андрей Михин on 04.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "polygon.hpp"

Polygon::Polygon(vector<Point> points) {
    for (int i = 0; i < points.size(); i++) {
        _points.push_back(points[i]);
    }
    this->leftBorder = -250;
    this->rightBorder = 250;
    this->topBorder = -250;
    this->bottomBorder = 250;
}

void Polygon::draw() {
    int s = _points.size();
    for (int i = 0; i < s; i++) {
        Brezenham(_points[i], _points[(i+1) % s]);
    }
}

vector<Point> Polygon::getEdge(int edgeNum) {
    vector<Point> r({_points[edgeNum], _points[(edgeNum+1) % this->_points.size()]});
    return r;
}

bool Polygon::isConvex() {
    for(int i = 0; i < _points.size(); i++){
        vector<Point> e = this->getEdge(i);
        for(int j = 1; j < _points.size(); j++) {
            if(j == i || j == (i+1) % _points.size())
                continue;
            if (ClassifyLeftRight(e, _points[j]) != ClassifyLeftRight(e, _points[(i+2) % _points.size()])){
                return false;
            }
        }
    }
    
    return true;
}

bool Polygon::isComplex() {
    for(int i = 1; i <= _points.size(); i++){
        vector<Point> e1 = this->getEdge(i);
        for(int j = i+1; j < _points.size(); j++){
            if(j == (i+1)% _points.size())
                continue;
            if(hasIntersect(e1, this->getEdge(j)))
                return true;
        }
    }
    
    return false;
}

int Polygon::EdgeType(vector<Point> edge, Point p) {
    switch(Classify(edge, p))
    {
        case POS_LEFT:
            if (p.y() <= edge[0].y() && p.y() > edge[1].y())
                return CROSS_LEFT;
            return INESETIONAL;
        case POS_RIGHT:
            if (p.y() > edge[0].y() && p.y() <= edge[1].y())
                return CROSS_RIGHT;
            return INESETIONAL;
        case POS_BETWEEN:
        case POS_ORIGIN:
        case POS_DEST:
            return TOUCHING;
        default:
            return INESETIONAL;
    }
    
    return INESETIONAL;
}

bool Polygon::isMyPixelEvenOdd(Point p) {
    int eo = 0;
    for(int edgeNum = 0; edgeNum < _points.size(); edgeNum++) {
        switch (this->EdgeType(this->getEdge(edgeNum), p)) {
            case TOUCHING:
                return true;
            case CROSS_RIGHT:
                eo++;
                break;
            case CROSS_LEFT:
                eo++;
                break;
        }
    }
    if (eo & 1)
        return true;
    return false;
}

bool Polygon::isMyPixelNonZeroWinding(Point p) {
    int s = 0;
    for(int edgeNum = 0; edgeNum < _points.size(); edgeNum++) {
        switch (this->EdgeType(this->getEdge(edgeNum), p)) {
            case TOUCHING:
                return true;
            case CROSS_RIGHT:
                s++;
                break;
            case CROSS_LEFT:
                s--;
                break;
        }
    }
    return s != 0;
}

void Polygon::fillWith(const int FILL_TYPE) {
    for(int i = this->leftBorder; i < this->rightBorder; i++) {
        for(int j = this->topBorder; j < this->bottomBorder; j++) {
            Point point(i,j);
            
            switch (FILL_TYPE) {
                case FILL_TYPE_EVEN_ODD:
                    if(this->isMyPixelEvenOdd(point))
                        point.draw();
                    break;
                case FILL_TYPE_NON_ZERO_WINDING:
                    if(this->isMyPixelNonZeroWinding(point))
                        point.draw();
                    break;
                default:
                    break;
            }
        }
    }
}
