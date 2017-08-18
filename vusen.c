#include "vusen.h"

/// Point constructor
void setPoint(Point* p,int color,double x, double y, double z){
    p->color = color;
    p->x = x;
    p->y = y;
    p->z = z;
}
/// Point destructor
void freePoint(Point* p){}

/// Line constructor from Point (when last line is assumed as (-1,0,0)-(0,0,0)
void setLine(Line* l,int color, Point* p0, double length, double phi, double theta){
    l->color = color;
    l->length = length;
    l->phi = phi;
    l->theta = theta;
    l->p[0] = malloc(sizeof(Point));
    l->p[1] = malloc(sizeof(Point));
    *(l->p[0]) = *p0;
    l->p0 = l->p[0];
    calcPointsInLine(l);
    l->gamma = p0;
    l->gammaLine = NULL;
    l->gammaPointIndex = -1;
}
void calcSecondPointsInLine(Point* p1, Point* p0, double length, double phi, double theta, double alpha, double gamma);
/// Line constructor from Line
void setNextLine(Line* l,int color, Line* l0, double length, double phiChange, double thetaChange){
    l->color = color;
    l->length = length;
    l->phi = l0->phi + phiChange;
    l->theta = l0->theta + thetaChange;
    l->p[0] = malloc(sizeof(Point));
    l->p[1] = malloc(sizeof(Point));
    *(l->p[0]) = *(l0->p[1]);
    l->p0 = l->p[0];
    //printLine(l);
    //calcSecondPointsInLine(l->p[1], l->p[0],l->length, l0->phi, l0->theta, phi, theta);
    calcPointsInLine(l);
    //printLine(l);
    l->gamma = l0->p[1];
    l->gammaLine = l0;
    l->gammaPointIndex = 1;
}

/// Calc second point
void calcPointsInLine(Line* l){
    l->p[1]->color = l->p[0]->color;
    l->p[1]->x = l->p[0]->x + l->length * cos(l->phi) * cos(l->theta);
    l->p[1]->y = l->p[0]->y + l->length * sin(l->phi) * cos(l->theta);
    l->p[1]->z = l->p[0]->z + l->length * sin(l->theta);
}

/// Calc second point
void calcSecondPointsInLine(Point* p1, Point* p0, double length, double phi, double theta, double alpha, double gamma){
    double s = sin(gamma);
    double b = s * sin(alpha);
    double c = s * cos(alpha);
    double d = sin(phi);
    double e = cos(phi);
    double f = cos(gamma);
    double g = sin(theta);
    double h = cos(theta);
    double a = f*h+c*g;
    p1->color = p0->color;
    p1->x = p0->x + length * (a * c - b * d);
    p1->y = p0->y + length * (-a * d - b * e);
    p1->z = p0->z + length * (f * g - c * h);
}
void printLine(Line* l){
    printf("(%lf,%lf,%lf)-(%lf,%lf,%lf)\n",l->p[0]->x,l->p[0]->y,l->p[0]->z,l->p[1]->x,l->p[1]->y,l->p[1]->z);
}
/// Line destructor
void freeLine(Line* l){
    free(l->p[0]);
    free(l->p[1]);
}

/// Square constructor
void setSquare(Square* sq, int color, Line* l0, double alpha){
    sq->color = color;
    sq->alpha = alpha;
    int i;
    for(i=0; i<4; i++){
        sq->lin[i] = malloc(sizeof(Line));
        sq->p[i] = malloc(sizeof(Point));
    }
    *(sq->lin[0]) = *l0;
    *(sq->p[0]) = *(l0->p[0]);
    *(sq->p[1]) = *(l0->p[1]);
    calcPointsInSquare(sq);
    for(i=1; i<4; i++)
        fillLineInSquare(sq,i);
}

/// Fill third and fourth point
void calcPointsInSquare(Square* sq){
    sq->p[2]->color = sq->p[0]->color;
    sq->p[3]->color = sq->p[1]->color;
}
///
void fillLineInSquare(Square* sq,int i){}

/// Square destructor
void freeSquare(Square* sq){
    int i;
    for(i=0; i<4; i++){
        free(sq->lin[i]);
        free(sq->p[i]);
    }
}


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
