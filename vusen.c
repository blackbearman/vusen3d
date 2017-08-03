#include "vusen.h"

CvPoint toCvPoint(Point* p){
    return cvPoint(cvRound(p->x),cvRound(p->y));
}

Point toPoint(double x, double y){
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Line toLine(double x1, double y1, double x2, double y2){
    Line l;
    l.p[0] = malloc(sizeof(Point));
    l.p[1] = malloc(sizeof(Point));
    *(l.p[0]) = toPoint(x1,y1);
    *(l.p[1]) = toPoint(x2,y2);
    return l;
}

void drawLine(CvArr* img,Line l){
    cvLine(img,toCvPoint(l.p[0]),toCvPoint(l.p[1]),CV_RGB(0,0,0),1,8,0);
}

Square toSquare(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4){
    Square sq;
    sq.p[0] = malloc(sizeof(Point));
    sq.p[1] = malloc(sizeof(Point));
    sq.p[2] = malloc(sizeof(Point));
    sq.p[3] = malloc(sizeof(Point));
    *(sq.p[0]) = toPoint(x1,y1);
    *(sq.p[1]) = toPoint(x2,y2);
    *(sq.p[2]) = toPoint(x3,y3);
    *(sq.p[3]) = toPoint(x4,y4);
    return sq;
}
