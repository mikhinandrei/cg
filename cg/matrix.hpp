//
//  matrix.hpp
//  cg
//
//  Created by Андрей Михин on 21.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp


#include <math.h>
#include <vector>

using namespace std;

class Matrix {
public:
    vector< vector<double> > m;
};

class ProjectionMatrix : public Matrix {
public:
    ProjectionMatrix(int);
};

class OnePointMatrix : public Matrix {
public:
    OnePointMatrix(int);
};

class RodriguezMatrix : public Matrix {
public:
    RodriguezMatrix(double, double, double, double);
};

Matrix operator * (Matrix, Matrix);

#endif /* matrix_hpp */
