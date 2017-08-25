#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "vusen.h"


void recalcCartesian(Line* l);

void rotate(Point* dest, Point* src, Line* axe, double angle);

#endif // GEOMETRY_H_INCLUDED
