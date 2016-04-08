#include "rgb2bin.h"
#include <tuple>
using std::tie;
using std::tuple;

uint max(uint a, uint b, uint c){
    if (a > b){
        return (a > c)? a : c;
    }
    else{
        return (b > c)?  b : c;
    }
}


uint rgb2bright::operator() (const Image &im)
{
    uint r,g,b,l;
    tie(r,g,b) = im(0,0);
    l = max(r,g,b);
    hist[l]++;
    return l;
}

uint rgb2bright::otsu_threshold()
{
    uint allsum = hist.sum();
    Histogram<double> probably_hist(256, 0);
    for (uint i = 0; i < 256; i++)
    {
         probably_hist[i] = double(hist[i]) / allsum;
    }
    double p = 0, exp = probably_hist.math_expection();
    double part_expection = 0;
    double m1, m2;
    double disp, dispmax = 0;
    uint thershold = 0;
    for (uint i = 0; i < 255; i++)
    {
        p += probably_hist[i];
        part_expection += i * probably_hist[i];
        m1 = part_expection / p;
        m2 = (exp - part_expection) / (1 - p);
        disp = p * (1 - p) * (m2 - m1)*(m2 - m1);
        if (disp > dispmax)
        {
            thershold = i;
            dispmax = disp;
        }
    }
    return thershold;
};
