//
//  ppp.cpp
//  cg
//
//  Created by Андрей Михин on 21.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "ppp.hpp"

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
        Point a = _points[i] * T;
        _points[i] = Point(a.x(), a.y(), a.z(), a.h());
        _points[i].norm();
    }
    
    draw();
}

void Piped::perspective(int n) {
    OnePointMatrix T = OnePointMatrix(n);
    for (int i = 0; i < _points.size(); i++) {
        Point a = _points[i] * T;
        _points[i] = Point(a.x(), a.y(), a.z(), a.h());
        _points[i].norm();
    }
    draw();
}

void Piped::proectRot(int n , int a, int b, int c, int phi) {
    ProjectionMatrix T = ProjectionMatrix(n);
    RodriguezMatrix R = RodriguezMatrix(a, b, c, phi * 3.1415926 / 180);
    for (int i = 0; i < _points.size(); i++) {
        Point a = _points[i] * R;
        Point b = a * T;
        _points[i] = Point(b.x(), b.y(), b.z(), b.h());
        _points[i].norm();
    }
    draw();
}

void Piped::perspectiveRot(int n , int a, int b, int c, int phi) {
    OnePointMatrix T = OnePointMatrix(n);
    RodriguezMatrix R = RodriguezMatrix(a, b, c, phi * 3.1415926 / 180);
    for (int i = 0; i < _points.size(); i++) {
        Matrix Z = R * T;
        Point b = _points[i] * Z;
        _points[i] = Point(b.x(), b.y(), b.z(), b.h());
        _points[i].norm();
    }
    draw();
}
