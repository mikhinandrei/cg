//
//  piped.hpp
//  cg
//
//  Created by Андрей Михин on 20.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef piped_hpp
#define piped_hpp

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
    private:
        vector<Point> _points;
};

#endif /* piped_hpp */
