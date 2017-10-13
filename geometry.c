#include "geometry.h"
#include <stdio.h>

Vector subsPoints(Point* from, Point* to) {
    Vector t;
    t.x = to->x - from->x;
    t.y = to->y - from->y;
    t.z = to->z - from->z;
    return t;
}

Vector toVector(double x, double y, double z) {
    Vector t;
    t.x = x;
    t.y = y;
    t.z = z;
    return t;
}

void addVectorToPoint(Point* dest, Point* src, Vector r) {
    dest->x = r.x + src->x;
    dest->y = r.y + src->y;
    dest->z = r.z + src->z;
}

Vector multiplyMatrix(double m[3][3], Vector t)
{
    Vector r;
    r.x = m[0][0] * t.x + m[0][1] * t.y + m[0][2] * t.z;
    r.y = m[1][0] * t.x + m[1][1] * t.y + m[1][2] * t.z;
    r.z = m[2][0] * t.x + m[2][1] * t.y + m[2][2] * t.z;
    return r;
}
void setUpRotationMatrix(double rotationMatrix[3][3], double angle, double u, double v, double w)
{
    //angle = angle * M_PI / 180.0; //converting to radian value
    double ca = cos(angle);
    double sa = sin(angle);
    double cam = 1 - ca;

    rotationMatrix[0][0] = u * u * cam + ca;
    rotationMatrix[0][1] = u * v * cam - w * sa;
    rotationMatrix[0][2] = u * w * cam + v * sa;

    rotationMatrix[1][0] = u * v * cam + w * sa;
    rotationMatrix[1][1] = v * v * cam + ca;
    rotationMatrix[1][2] = v * w * cam - u * sa;

    rotationMatrix[2][0] = u * w * cam - v * sa;
    rotationMatrix[2][1] = v * w * cam + u * sa;
    rotationMatrix[2][2] = w * w * cam + ca;
}

void printMatrix(double m[3][3]) {
    int i,j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++)
            printf("%lf ",m[i][j]);
        printf("\n");
    }
}
void rotate(Point* dest, Point* src, Line* axe, double angle){
    dest->color = src->color;
    double u = (axe->p[1]->x - axe->p[0]->x) / axe->length;
    double v = (axe->p[1]->y - axe->p[0]->y) / axe->length;
    double w = (axe->p[1]->z - axe->p[0]->z) / axe->length;
    Vector t = subsPoints(src,axe->p[0]);
    double m[3][3];
    setUpRotationMatrix(m,angle,u,v,w);
    //printMatrix(m);
    Vector r = multiplyMatrix(m,t);
    addVectorToPoint(dest,axe->p[0],r);
}

void recalcCartesian(Line* l) {
    l->p[1]->x = l->p[0]->x + l->length * cos(l->phi) * sin(l->theta);
    l->p[1]->y = l->p[0]->y + l->length * sin(l->phi) * sin(l->theta);
    l->p[1]->z = l->p[0]->z + l->length * cos(l->theta);
}
