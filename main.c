#include <stdio.h>
#include <stdlib.h>
#include "vusen.h"
//#include <opencv2/core/fast_math.hpp>

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

    Line l = toLine(0,0,100,100);
    drawLine(img,l);
    int p[3];
    p[0] = 6;
    p[1] = 100;
    p[2] = 0;

    cvSaveImage("out2.jpg", img, p);
    return 0;
}

#if ((CV_VERSION_EPOCH > 2) || (!defined CV_VERSION_MAJOR))
int
cvRound( double value )
{
#if ((defined _MSC_VER && defined _M_X64) || (defined __GNUC__ && defined __x86_64__ \
    && defined __SSE2__ && !defined __APPLE__)) && !defined(__CUDACC__)
    __m128d t = _mm_set_sd( value );
    return _mm_cvtsd_si32(t);
#elif defined _MSC_VER && defined _M_IX86
    int t;
    __asm
    {
        fld value;
        fistp t;
    }
    return t;
#elif ((defined _MSC_VER && defined _M_ARM) || defined CV_ICC || \
        defined __GNUC__) && defined HAVE_TEGRA_OPTIMIZATION
    TEGRA_ROUND_DBL(value);
#elif defined CV_ICC || defined __GNUC__
# if CV_VFP
    ARM_ROUND_DBL(value);
# else
    return (int)lrint(value);
# endif
#else
    /* it's ok if round does not comply with IEEE754 standard;
       the tests should allow +/-1 difference when the tested functions use round */
    return (int)(value + (value >= 0 ? 0.5 : -0.5));
#endif

}
#endif
