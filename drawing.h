#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "vusen.h"

int rgb(unsigned char red, unsigned char green, unsigned char blue);
CvPoint toCvPoint(Point* p);
void drawPoint(IplImage* img,Point* l);
void drawLine(CvArr* img,Line* l);
void drawSquare(CvArr* img,Square* l);
int cvRound(double value);

#endif // DRAWING_H_INCLUDED
