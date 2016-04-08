#ifndef RGB2BRIGHT_H
#define RGB2BRIGHT_H

#include <vector>
#include "matrix.h"
#include "io.h"
#include "histogram.h"
using std::vector;




class rgb2bright
{
public:
    Histogram<uint> hist = Histogram<uint>(256, 0); //create histogram with 256 elements, which have value 0
    uint operator() (const Image &im);
    uint otsu_threshold();
    const static int radius = 0;
};

class bright2bin
{
public:
    uint threshold;
    static const int radius = 0;
    bright2bin(uint thrs): threshold(thrs){}
    uint operator ()(const Matrix<uint> &im) const{
        return im(0,0) > threshold ? 1 : 0;
    }
};

#endif // RGB2BRIGHT_H
