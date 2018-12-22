//
//  main.cpp
//  cg
//
//  Created by Андрей Михин on 02.12.18.
//  Copyright © 2018 Андрей Михин. All rights reserved.
//

#include "point.hpp"
#include "polygon.hpp"
#include "bezier.hpp"
#include "utilities.h"
#include "ppp.hpp"
#include <unistd.h>

int angle = 0;

void drawLines(void) {
    Brezenham(Point(3 ,1), Point(85, 40));
    Brezenham(Point(5 ,15), Point(85, 116));
    Brezenham(Point(88 ,-42), Point(15, -10));
    Brezenham(Point(49 , -101), Point(0, -60));
    Brezenham(Point(-2 ,-3), Point(4, -91));
    Brezenham(Point(-200 ,-50), Point(-40, -30));
    Brezenham(Point(-3 ,1), Point(-152, 16));
    Brezenham(Point(-39, 140), Point(-15, 199));
}

void drawPolygons() {
    vector<Point> tr({Point(-150, 100), Point(-100, 150), Point(-130, 10)});
    Polygon triangle = Polygon(tr);
    triangle.draw();
    // triangle.fillWith(FILL_TYPE_NON_ZERO_WINDING);
    cout << "Triangle is convex: " << triangle.isConvex() << endl;
    cout << "Triangle is complex: " << triangle.isComplex() << endl;
    
    vector<Point> st({Point(30, 30), Point(130, 200), Point(210, 30), Point(-50, 120), Point(240, 120)});
    Polygon star = Polygon(st);
    star.draw();
    // star.fillWith(FILL_TYPE_NON_ZERO_WINDING);
    cout << "Star is complex: " << star.isComplex() << endl;
    cout << "Star is convex: " << star.isConvex() << endl;
    
    vector<Point> z({Point(-220, -30), Point(-30, -30), Point(-180, -50), Point(-220, -220)});
    Polygon p = Polygon(z);
    p.draw();
    // p.fillWith(FILL_TYPE_NON_ZERO_WINDING);
    cout << "Rect is convex: " << p.isConvex() << endl;
    cout << "Rect is complex: " << p.isComplex() << endl;
}

void bezier(void) {
    Point p0 = Point(-50, 30);
    Point p1 = Point(50, 200);
    Point p2 = Point(130, 30);
    Point p3 = Point(-130, 120);
    Brezenham(p0, p1);
    Brezenham(p1, p2);
    Brezenham(p2, p3);
    Bezier b = Bezier(p0, p1, p2, p3);
    b.draw();
    
    // vector<Point> s({Point(-130, -200), Point(0, 200), Point(110, 30), Point(150, 120)});
    // Bezier l = Bezier(s);
    // l.draw();
}

void clip(void) {
    vector<Point> line({Point(-200, -100), Point(250, 250)});
    //vector<Point> z({Point(-150, -100), Point(-100, 150), Point(130, 10)});
    vector<Point> z({Point(-120, -120), Point(-120, 0), Point(0, 0), Point(0, -120)});
    Polygon p = Polygon(z);
    p.draw();
    clipLine(line, p._points);
}

void perspective(void) {
    vector<Point> z({
        Point(-50, -50, 100), Point(10, -50, 100), Point(10, 10, 100), Point(-50, 10, 100),
        Point(-50, -50, 200), Point(10, -50, 200), Point(10, 10, 200), Point(-50, 10, 200),
    });
    Piped p = Piped(z);
    glClear(GL_COLOR_BUFFER_BIT);
    p.perspective(150);
    glFlush();
}

void rotate(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    vector<Point> z({
        Point(0, 0, 100), Point(0, 100, 100), Point(100, 100, 100), Point(100, 0, 100),
        Point(0, 0, 200), Point(0, 100, 200), Point(100, 100, 200), Point(100, 0, 200),
    });
    Piped p = Piped(z);
    p.perspectiveRot(100, 1, 1, 1, angle);
    
    vector<Point> k({
        Point(0, 0, 100), Point(0, 100, 100), Point(100, 100, 100), Point(100, 0, 100),
        Point(0, 0, 200), Point(0, 100, 200), Point(100, 100, 200), Point(100, 0, 200),
    });
    Piped pp = Piped(k);
    pp.proectRot(100, 1, 1, 1, angle);
    glFlush();
    glutPostRedisplay();
    angle += 5;
}

void timf(int value) // Timer function
{
    glutPostRedisplay();  // Redraw windows
    glutTimerFunc(40, timf, 0); // Setup next timer
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_POINTS);
        glColor3f(1,1,1);
        // drawLines();
        // drawPolygons();
        // bezier();
        // clip();
    //parallel();
    // perspective();
    rotate();
    glEnd();
    
    glutSwapBuffers();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(500,500);
    glutCreateWindow("A Simple OpenGL Program");
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, 500.0, 500.0,0.0 );
    
    glutDisplayFunc(renderScene);
    glutTimerFunc(40, timf, 0);
    glutMainLoop();
    
    return 0;
}


