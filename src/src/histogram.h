#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <vector>
#include "matrix.h"
using std::vector;

template <typename ValueT>
class Histogram
{
private:
    const uint size;
    vector<ValueT> hist;
public:
    Histogram(uint _size, ValueT value);
    ~Histogram ();
    ValueT sum() const;
    ValueT &operator [](uint i);
    double math_expection();
};

template <typename ValueT>
Histogram<ValueT>::Histogram(uint _size, ValueT value): size(_size), hist(_size, value){}

template<typename ValueT>
Histogram<ValueT>::~Histogram(){}

template<typename ValueT>
ValueT Histogram<ValueT>:: sum() const
{
    ValueT ans = 0;
    for (auto i = hist.begin(); i != hist.end(); i++)
        ans += *i;
    return ans;
}

template<typename ValueT>
ValueT &Histogram<ValueT>:: operator [](uint i)
{
    return hist[i];
}

template<typename ValueT>
double Histogram<ValueT>:: math_expection()
{
    ValueT ans = 0;
    for (uint i = 0; i < size; i++)
    {
        ans += i * hist[i];
    }
    return ans;
}

#endif // HISTOGRAMM_H
