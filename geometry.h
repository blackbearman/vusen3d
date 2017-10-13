#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "vusen.h"

typedef struct v_Vector Vector;

struct v_Vector{
    double x,y,z;
};

Vector subsPoints(Point* from, Point* to);
Vector toVector(double x, double y, double z);
void addVectorToPoint(Point* dest, Point* src, Vector r);

void recalcCartesian(Line* l);

void rotate(Point* dest, Point* src, Line* axe, double angle);

#endif // GEOMETRY_H_INCLUDED
