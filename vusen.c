#include "vusen.h"
#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"
/// //////////// POINT //////////////////
/// Point constructor
void setPoint(Point* p,int color,double x, double y, double z){
    p->color = color;
    p->x = x;
    p->y = y;
    p->z = z;
}
void printPoint(Point* p){
    printf("(%lf,%lf,%lf)\n",p->x,p->y,p->z);
}
/// Point destructor
void freePoint(Point* p){}
/// ///////////////// LINE ///////////////////////////////
void setLineBase(Line* l,int color, Point* p0, double length, double phi, double theta){
    l->color = color;
    l->length = length;
    l->phi = phi;
    l->theta = theta;
    l->p[0] = malloc(sizeof(Point));
    l->p[1] = malloc(sizeof(Point));
    *(l->p[0]) = *p0;
    l->p0 = l->p[0];
    l->p[1]->color = l->p[0]->color;
}

/// Line constructor from Point (when last line is assumed as (-1,0,0)-(0,0,0)
void setLine(Line* l,int color, Point* p0, double length, double phi, double theta){
    setLineBase(l,color,p0,length,phi,theta);
    /// Calc second point
    recalcCartesian(l);
    l->gamma = p0;
    l->gammaLine = NULL;
    l->gammaPointIndex = -1;
}
void calcSecondPointsInLine(Point* p1, Point* p0, double length, double phi, double theta, double alpha, double gamma);
/// Line constructor from Line
void setNextLine(Line* l,int color, Line* l0, double length, double phiChange, double thetaChange){
    setLineBase(l,color,l0->p[1],length,l0->phi+phiChange,l0->theta + thetaChange);
    //calcSecondPointsInLine(l->p[1], l->p[0],l->length, l0->phi, l0->theta, phi, theta);
    /// Calc second point
    recalcCartesian(l);
    //printLine(l);
    l->gamma = l0->p[1];
    l->gammaLine = l0;
    l->gammaPointIndex = 1;
}

void setTurnLine(Line* l,int color, Line* l0, double length, double turnAngle, double dirAngle){
    Point endPoint;
    double phi = l0->phi;
    double theta = l0->theta - turnAngle;
    if(theta > M_PI) {
        theta -= M_PI;
        phi = -phi;
    }
    if(theta < 0) {
        theta = -theta;
        phi = -phi;
    }
    setPoint(&endPoint,l0->p[1]->color,
             l0->p[1]->x + length * cos(phi) * sin(theta),
             l0->p[1]->y + length * sin(phi) * sin(theta),
             l0->p[1]->z + length * cos(theta));
    Point turnPoint;
    rotate(&turnPoint,&endPoint,l0,dirAngle);
    phi = atan2(turnPoint.y - l0->p[1]->y, turnPoint.x - l0->p[1]->x);
    theta = acos((turnPoint.z - l0->p[1]->z)/length);
    setLineBase(l,color,l0->p[1],length,phi,theta);
    *(l->p[1]) = turnPoint;
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
/// /////////////////// SQUARE //////////////////////////////
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
    sq->lin0 = sq->lin[0];
    sq->lin[0]->p[0] = sq->p[0];
    sq->lin[0]->p[1] = sq->p[1];
    *(sq->p[0]) = *(l0->p[0]);
    *(sq->p[1]) = *(l0->p[1]);
    calcPointsInSquare(sq);
    for(i=1; i<4; i++)
        fillLineInSquare(sq,i);
}

void setNextSquare(Square* sq, Square* sq0, double alpha){
    Line lin0;
    setLine(&lin0,sq->lin[2]->color,sq0->p[3],sq->lin[2]->length,-sq->lin[2]->phi,M_PI-sq->lin[2]->theta);
    setSquare(sq,sq0->color,&lin0,alpha);
    freeLine(&lin0);
}
void setSquareFromPoint(Square* sq, int color, Point* p0, double length, double phi, double theta, double alpha){
    Line lin0;
    setLine(&lin0,color,p0,length,phi,theta);
    setSquare(sq,color,&lin0,alpha);
    freeLine(&lin0);
}

/// Fill third and fourth point
void calcPointsInSquare(Square* sq){
    sq->p[2]->color = sq->p[0]->color;
    sq->p[3]->color = sq->p[1]->color;
    double sa = sin(sq->alpha); ///1
    double ca = cos(sq->alpha); ///0
    double sp = sin(sq->lin0->phi);
    double cp = cos(sq->lin0->phi);
    double st = sin(sq->lin0->theta);///0
    double ct = cos(sq->lin0->theta);///1
    double deltaX = sq->lin0->length * ( -ca * ct * cp + sa * sp);
    double deltaY = sq->lin0->length * ( -ca * ct * sp - sa * cp);
    double deltaZ = sq->lin0->length * ( ca * st);
    sq->p[2]->x = sq->p[1]->x + deltaX;
    sq->p[2]->y = sq->p[1]->y + deltaY;
    sq->p[2]->z = sq->p[1]->z + deltaZ;
    sq->p[3]->x = sq->p[0]->x + deltaX;
    sq->p[3]->y = sq->p[0]->y + deltaY;
    sq->p[3]->z = sq->p[0]->z + deltaZ;
}
///
void fillLineInSquare(Square* sq,int i){
    sq->lin[i]->color = sq->lin0->color;
    sq->lin[i]->length = sq->lin0->length;
    switch(i){
    case 1:
        sq->lin[1]->phi = atan2(sq->p[2]->y - sq->p[1]->y, sq->p[2]->x - sq->p[1]->x);
        sq->lin[1]->theta = acos((sq->p[2]->z - sq->p[1]->z)/sq->lin0->length);
        sq->lin[1]->p[0] = sq->p[1];
        sq->lin[1]->p0 = sq->lin[1]->p[0];
        sq->lin[1]->p[1] = sq->p[2];
        break;
    case 2:
        sq->lin[2]->phi = -sq->lin0->phi;
        sq->lin[2]->theta = -sq->lin0->theta;
        sq->lin[2]->p[0] = sq->p[2];
        sq->lin[2]->p0 = sq->lin[2]->p[0];
        sq->lin[2]->p[1] = sq->p[3];
        break;
    case 3:
        sq->lin[3]->phi = -sq->lin[1]->phi;
        sq->lin[3]->theta = -sq->lin[1]->theta;
        sq->lin[3]->p[0] = sq->p[3];
        sq->lin[3]->p0 = sq->lin[3]->p[0];
        sq->lin[3]->p[1] = sq->p[0];
        break;
    }
}

void printSquare(Square* sq){
    printf("{(%lf,%lf,%lf),(%lf,%lf,%lf)\n",sq->p[0]->x,sq->p[0]->y,sq->p[0]->z,sq->p[1]->x,sq->p[1]->y,sq->p[1]->z);
    printf("{(%lf,%lf,%lf),(%lf,%lf,%lf)}\n",sq->p[2]->x,sq->p[2]->y,sq->p[2]->z,sq->p[3]->x,sq->p[3]->y,sq->p[3]->z);
}

/// Square destructor
void freeSquare(Square* sq){
    int i;
    for(i=0; i<4; i++){
        free(sq->lin[i]);
        free(sq->p[i]);
    }
}
void setPointsInLine(Line* lin, Point* p1, Point* p2) {
    lin->p0 = lin->p[0] = p1;
    lin->p[1] = p2;
}
void setNPointsInContour(int n, Line** lin, Point** p) {
    int i;
    for(i = 0; i<n-1; i++)
        setPointsInLine(lin[i],p[i],p[i+1]);
    setPointsInLine(lin[n-1],p[n-1],p[0]);
}
/// ////////////////// CUBE //////////////////////
/// Cube constructor
void setCube(Cube* cb, int color, Square* sq0) {
    int i;
    for(i=0; i<6; i++)
        cb->sq[i] = malloc(sizeof(Square));
    for(i=0; i<4; i++)
        cb->lin[i] = malloc(sizeof(Line));
    for(i=0; i<4; i++)
        cb->p[i] = malloc(sizeof(Point));
    cb->color = color;
    *(cb->sq[0]) = *sq0;
    for(i=0; i<4; i++)
        cb->lin[i] = sq0->lin[i];   /// first 4 lines
    setNPointsInContour(4,cb->lin,cb->p);
    setNPointsInContour(4,cb->lin+4,cb->p+4);
    //setPointsInLine();
    cb->sq0 = cb->sq[0];
    for(i=0; i<4; i++)
        *(cb->p[i]) = *(sq0->p[i]); /// first 4 points
//    calcPointsInCube(cb);     /// another 4 points
}
void setNextCube(Cube* cb, Cube* sq0,int lineIndex, double alpha);

void calcPointsInCube(Cube* cb);
void fillLineInCube(Cube* cb,int i);
void fillSquareInCube(Cube* cb,int i);
void printCube(Cube* cb);
/// Cube destructor
void freeCube(Cube* cb){
    int i;
    for(i=0; i<8; i++)
        free(cb->p[i]);
    for(i=0; i<12; i++)
        free(cb->lin[i]);
    for(i=0; i<6; i++)
        free(cb->sq[i]);
}


/// ////////////////// OTHER //////////////////////
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
