#ifndef VUSEN_H_INCLUDED
#define VUSEN_H_INCLUDED

#include <opencv/cv.h>
#include <opencv/highgui.h>

struct v_Point{
    int color;

    double x;
    double y;
    double z;
};
typedef struct v_Point Point;
void setPoint(Point* p,int color,double x, double y, double z);

typedef struct v_Line Line;
struct v_Line{
    /// unit
    int color;
    Point* p0;
    double length;
    double phi;
    double theta;
    /// construction
    Point* p[2];
    /// links
    Point* gamma;
    Line* gammaLine;
    int gammaPointIndex;
    Line* shifts;
};

void setLine(Line* l,int color, Point* p0, double length, double phi, double theta);
void calcPointsInLine(Line* l);

struct v_Square{
    int color;
    Line* lin0;
    double alpha;

    Line* lin[4];
    Point* p[4];
};
typedef struct v_Square Square;
void calcPointsInSquare(Square* l);
void fillLineInSquare(Square* c,int i);

struct v_Cube{
    int color;
    Square* sq0;

    Square* sq[6];
    Line* lin[12];
    Point* p[8];
};
typedef struct v_Cube Cube;
void calcPointsInCube(Cube* l);
void fillLineInCube(Cube* c,int i);
void fillSquareInCube(Cube* c,int i);

CvPoint toCvPoint(Point p);
Point toPoint(double x, double y);
Line toLine(double x1, double y1, double x2, double y2);
Square toSquare(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);

void drawLine(CvArr* img,Line l);

void drawSquare(CvArr* img,Square l);
#endif // VUSEN_H_INCLUDED
