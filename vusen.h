#ifndef VUSEN_H_INCLUDED
#define VUSEN_H_INCLUDED

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <math.h>

typedef struct v_Point Point;
struct v_Point{
    /// unit
    int color;
    double x;
    double y;
    double z;
    /// links on line level (gamma-lambda)
    Point* gamma;

    Point* shifts;
};

void setPoint(Point* p,int color,double x, double y, double z);
void printPoint(Point* p);
void freePoint(Point* p);

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
    /// links on line level (gamma-lambda)
    Point* gamma;
    /// or
    Line* gammaLine;
    int gammaPointIndex; /// in line

    Line* shifts;
};

void setLine(Line* l,int color, Point* p0, double length, double phi, double theta);
void setNextLine(Line* l,int color, Line* l0, double length, double phiChange, double thetaChange);
void calcPointsInLine(Line* l);
void freeLine(Line* l);

typedef struct v_Square Square;
struct v_Square{
    /// unit
    int color;
    Line* lin0;
    double alpha;
    /// construction
    Line* lin[4];
    Point* p[4];
    /// links on square level (gamma-lambda)
    Point* gamma;
    /// or
    Line* gammaLine;
    /// or
    Square* gammaSquare;
    int gammaLineIndex;  /// in square

    Square* shifts;
};

void setSquare(Square* sq, int color, Line* l0, double alpha);
void setNextSquare(Square* sq, Square* sq0, double alpha);
void setSquareFromPoint(Square* sq, int color, Point* p0, double length, double phi, double theta, double alpha);
//void setSquareFromPoints(Square* sq, int color, Point* p0, Point* p1, double alpha);
void setSquareFromCoord(Square* sq, int color, double x, double y, double z, double length, double phi, double theta, double alpha);

void calcPointsInSquare(Square* sq);
void fillLineInSquare(Square* sq,int i);
void printSquare(Square* sq);
void freeSquare(Square* sq);

typedef struct v_Cube Cube;
struct v_Cube{
    /// unit
    int color;
    Square* sq0;
    /// construction
    Square* sq[6];
    Line* lin[12];
    Point* p[8];
     /// links on square level (gamma-lambda)
    Point* gamma;
    /// or
    Line* gammaLine;
    /// or
    Square* gammaSquare;
    /// or
    Cube* gammaCube;
    int gammaSquareIndex;  /// in square

    Cube* shifts;
};

void calcPointsInCube(Cube* l);
void fillLineInCube(Cube* c,int i);
void fillSquareInCube(Cube* c,int i);

CvPoint toCvPoint(Point* p);
Point toPoint(double x, double y);
Line toLine(double x1, double y1, double x2, double y2);
Square toSquare(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4);

void drawLine(CvArr* img,Line l);

void drawSquare(CvArr* img,Square l);
#endif // VUSEN_H_INCLUDED
