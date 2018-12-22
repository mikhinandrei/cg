//
//  piped.cpp
//  cg
//
//  Created by Андрей Михин on 20.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "piped.hpp"

Piped::Piped(vector<Point> points) {
    for (int i = 0; i < points.size(); i++) {
        _points.push_back(points[i]);
    }
}

void Piped::draw() {
    for (int i = 0; i < 4; i++) { // Фронтальный полигон
        Brezenham(_points[i], _points[(i + 1) % 4]);
    }
    for (int i = 0; i < 4; i++) { // Задний полигон
        Brezenham(_points[i + 4], _points[(i + 1) % 4 + 4]);
    }
    for (int i = 0; i < 4; i++) { // Соединяем полигоны
        Brezenham(_points[i], _points[i + 4]);
    }
}

void Piped::proect(int n) {
    ProjectionMatrix T = ProjectionMatrix(n);
    for (int i = 0; i < _points.size(); i++) {
        _points[i] *= T;
        _points[i].norm();
    }
    draw();
}

void Piped::perspective(int n) {
    OnePointMatrix T = OnePointMatrix(n);
    for (int i = 0; i < _points.size(); i++) {
        _points[i] *= T;
        _points[i].norm();
    }
    draw();
}
