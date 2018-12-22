//
//  ppp.hpp
//  cg
//
//  Created by Андрей Михин on 21.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef ppp_hpp
#define ppp_hpp

#include "utilities.h"
#include "point.hpp"
#include "polygon.hpp"
#include "matrix.hpp"

class Piped {
public:
    Piped(vector<Point>);
    void draw();
    void proect(int);
    void perspective(int);
    void perspectiveRot(int, int, int, int, int);
    void proectRot(int n , int a, int b, int c, int phi);
private:
    vector<Point> _points;
};
#endif /* ppp_hpp */
