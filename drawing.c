#include "drawing.h"

int rgb(unsigned char red, unsigned char green, unsigned char blue) {
    int a;
    unsigned char* p = (unsigned char*)&a;
    p[0] = red;
    p[1] = green;
    p[2] = blue;
    return a;
}

CvPoint toCvPoint(Point* p){
    static double half_s45 = M_SQRT2 / 4.0;
    double x_projection = p->x * half_s45;
    double sz = p->z - x_projection;
    double sy = p->y - x_projection;
    return cvPoint(cvRound(sy),cvRound(sz));
}

unsigned char component(int color, int index) {
    unsigned char *p = (unsigned char *)&color;
    return p[index];
}

void drawPoint(IplImage *img,Point* p){
    int step  = img->widthStep/sizeof(uchar);
    int channels = img->nChannels;
    uchar* data = (uchar*) img->imageData;
    CvPoint cvp = toCvPoint(p);
    int i = cvp.x - 1;
    int j = cvp.y - 1;
    data[i * step + j * channels + 0] = component(p->color,2);
    data[i * step + j * channels + 1] = component(p->color,1);
    data[i * step + j * channels + 2] = component(p->color,0);
    //CvScalar color = CV_RGB(component(p->color,0),component(p->color,1),component(p->color,2));
    //cvLine(img,toCvPoint(p[0]),toCvPoint(p[0]),color,1,8,0);
}

void drawLine(CvArr* img,Line* l){
    CvScalar color = CV_RGB(component(l->color,0),component(l->color,1),component(l->color,2));
    cvLine(img,toCvPoint(l->p[0]),toCvPoint(l->p[1]),color,1,8,0);
}

void drawSquare(CvArr* img,Square* sq){
    int i;
    for(i = 0; i < 4; i++)
        drawLine(img,sq->lin[i]);
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

