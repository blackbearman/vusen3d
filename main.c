#include <stdio.h>
#include <stdlib.h>
#include "vusen.h"
#include "geometry.h"
//#include <opencv2/core/fast_math.hpp>
#include "drawing.h"

int main()
{
    int width = 400;
    int height = 300;
    IplImage *img =  cvCreateImage( cvSize(width,height), IPL_DEPTH_8U, 3 );

    int i,j;
    int step  = img->widthStep/sizeof(uchar);
    int channels = img->nChannels;
    uchar* data = (uchar*) img->imageData;
    for(i = 0; i< height; i++)
        for(j = 0; j< width; j++) {
            data[i*step+j*channels+0] = 255;
            data[i*step+j*channels+1] = 255;
            data[i*step+j*channels+2] = 255;
    }

    Point p1;
    setPoint(&p1,0,20,20,20);
    Line l = toLine(0,0,100,100);
    setLine(&l,0,&p1,100,0.5,0.00);
    drawLine(img,&l);
    Line l2[10];
    for(i = 0; i < 10; i++) {
        setNextLine(l2+i,0,&l,100,0.1*i,0.0);
        printLine(l2+i);
        drawLine(img,l2+i);
    }
    //setNextLine(&l2,0,&l,100,0.1,0.02);
    //printLine(&l);
    //printLine(&l2);

    Line l3[10];
    setLine(l3,0,&p1,200,0.5,0.0);
    for(i = 1; i < 10; i++) {
        setNextLine(l3+i,0,l3+i-1,10,0.1,0.1*i);
        printLine(l3+i);
        drawLine(img,l3+i);
    }
    freeLine(&l);
    freePoint(&p1);

    int p[3];
    p[0] = 6;
    p[1] = 100;
    p[2] = 0;

    Point p3;
    setPoint(&p3,0,100,100,100);
    Line l5;
    Square sq0;
    setLine(&l5,0,&p3,50,2*M_PI_2/3,0);
    setSquare(&sq0,0,&l5,0);
    drawSquare(img,&sq0);

    setLine(&l5,0,&p3,50,2*M_PI_2/3,0);
    setSquare(&sq0,0,&l5,2*M_PI_2/3);
    drawSquare(img,&sq0);

    setLine(&l5,0,&p3,50,2*M_PI_2/3,0);
    setSquare(&sq0,0,&l5,0);
    //drawSquare(img,&sq0);

    setLine(&l5,0,&p3,50,2*M_PI_2/3,2*M_PI_2/3);
    setSquare(&sq0,0,&l5,2*M_PI_2/3);
    //drawSquare(img,&sq0);
  printSquare(&sq0);

    Point pxy;
    printf("red %x\n",rgb(255,0,0));
    setPoint(&pxy,rgb(255,0,0),2,2,2);
    Line lx;
    setLine(&lx,rgb(255,0,0),&p3,300,0,0.0);
    Line ly;
    setLine(&ly,rgb(255,0,0),&p3,200,0.0,M_PI_2);
    drawLine(img,&lx);
    drawLine(img,&ly);
    drawPoint(img,&pxy);
    cvSaveImage("out2.jpg", img, p);
    setLine(&l,0,&pxy,100,M_PI_2,0);
    setPoint(&p3,0,1,0,0);
    printPoint(&p3);
    rotate(&pxy,&p3,&l,M_PI_2);
    printPoint(&pxy);
    return 0;
}
