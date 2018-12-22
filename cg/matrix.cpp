//
//  matrix.cpp
//  cg
//
//  Created by Андрей Михин on 21.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "matrix.hpp"
#include <iostream>


ProjectionMatrix::ProjectionMatrix(int n) {
    for (int i = 0; i < 4; ++i) {
        vector<double> k({0, 0, 0, 0});
        m.push_back(k);
    }
    m[0][0] = 1;
    m[1][1] = 1;
    m[3][3] = 1;
    m[3][2] = n;
}


OnePointMatrix::OnePointMatrix(int n) {
    for (int i = 0; i < 4; ++i) {
        vector<double> k({0, 0, 0, 0});
        m.push_back(k);
    }
    m[0][0] = 1.0;
    m[1][1] = 1.0;
    m[3][3] = 1.0;
    m[3][2] = n;
    m[2][3] = 1.0 / n;
}

RodriguezMatrix::RodriguezMatrix(double x, double y, double z, double phi) {
    for (int i = 0; i < 4; ++i) {
        vector<double> k({0, 0, 0, 0});
        m.push_back(k);
    }
    double r = sqrt(x*x + y * y + z * z);
    double nx = x / r;
    double ny = y / r;
    double nz = z / r;
    m[0][0] = cos(phi) + nx * nx*(1 - cos(phi));
    m[0][1] = nz * sin(phi) + nx * ny*(1 - cos(phi));
    m[0][2] = -ny * sin(phi) + nx * nz*(1 - cos(phi));
    m[0][3] = 0;
    m[1][0] = nx * ny*(1 - cos(phi)) - nz * sin(phi);
    m[1][1] = cos(phi) + ny * ny*(1 - cos(phi));
    m[1][2] = nx * sin(phi) + ny * nz*(1 - cos(phi));
    m[1][3] = 0;
    m[2][0] = ny * sin(phi) + nx * nz*(1 - cos(phi));
    m[2][1] = -nx * sin(phi) + ny * nz*(1 - cos(phi));
    m[2][2] = cos(phi) + nz * nz*(1 - cos(phi));
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1.0;
}

Matrix operator * (Matrix a, Matrix b) {
    Matrix result;
    for (int i = 0; i < 4; ++i) {
        vector<double> k({0, 0, 0, 0});
        result.m.push_back(k);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}
