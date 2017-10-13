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
    setPoint(&p1,0,120,120,120);
    Line l;
    setLine(&l,0,&p1,10,M_PI_4,M_PI_2);
    drawLine(img,&l);
    printLine(&l);
    Line up;
    setTurnLine(&up,0,&l,10,M_PI_2,-M_PI_4);
    drawLine(img,&up);
    printLine(&up);
    /*
    Line l2[10];
    for(i = 0; i < 10; i++) {
        setNextLine(l2+i,0,&l,100,0.1*i,0.0);
        printLine(l2+i);
        drawLine(img,l2+i);
    }
    */
    //setNextLine(&l2,0,&l,100,0.1,0.02);
    //printLine(&l);
    //printLine(&l2);
/*
    Line l3[10];
    setLine(l3,0,&p1,200,0.5,0.0);
    for(i = 1; i < 10; i++) {
        setNextLine(l3+i,0,l3+i-1,10,0.1,0.1*i);
        printLine(l3+i);
        drawLine(img,l3+i);
    }
    */
    freeLine(&l);
    freePoint(&p1);

    Point p3;
    setPoint(&p3,0,100,100,100);


    Line l5;
    Square sq0;
    setLine(&l5,0,&p3,50,2*M_PI_2/3,M_PI_4);
    printLine(&l5);
    setSquare(&sq0,0,&l5,M_PI_4);
    drawSquare(img,&sq0);
    printSquare(&sq0);
/*
    setLine(&l5,0,&p3,50,2*M_PI_2/3,0);
    setSquare(&sq0,0,&l5,2*M_PI_2/3);
    drawSquare(img,&sq0);

    setLine(&l5,0,&p3,50,2*M_PI_2/3,0);
    setSquare(&sq0,0,&l5,0);
    //drawSquare(img,&sq0);

    setLine(&l5,0,&p3,50,2*M_PI_2/3,2*M_PI_2/3);
    setSquare(&sq0,0,&l5,2*M_PI_2/3);
    //drawSquare(img,&sq0);
  //printSquare(&sq0);
*/
    Point pxy;
    //printf("red %x\n",rgb(255,0,0));
    setPoint(&pxy,rgb(255,0,0),2,2,2);
    Line lx;
    setLine(&lx,rgb(255,0,0),&p3,300,0.0,M_PI_2);
    Line ly;
    setLine(&ly,rgb(0,255,0),&p3,200,M_PI_2,M_PI_2);
    Line lz;
    setLine(&lz,rgb(0,0,255),&p3,200,0.0,0);
    drawLine(img,&lx);
    drawLine(img,&ly);
    drawLine(img,&lz);
    drawPoint(img,&pxy);

    int p[3];
    p[0] = 6;
    p[1] = 100;
    p[2] = 0;
    //cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE);// Create a window for display.
    //cvShowImage("Display window", img);
    //cvWaitKey(0);
    cvFlip(img,NULL,0);
    cvSaveImage("out2.jpg", img, p);
/*
    setLine(&l,0,&pxy,100,M_PI_2,0);
    setPoint(&p3,0,1,0,0);
    printPoint(&p3);
    rotate(&pxy,&p3,&l,M_PI_2);
    printPoint(&pxy);
    */
    return 0;
}
