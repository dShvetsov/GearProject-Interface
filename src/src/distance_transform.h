#ifndef DISTANCE_TRANSFORM_H
#define DISTANCE_TRANSFORM_H
#include "matrix.h"
#include <vector>

using std::vector;


class SimpleDT{
private:
    double *ans = NULL;
    uint size = 0;
public:
    SimpleDT(const vector<double>& input);
    void implamatation_of_distance_transform(const vector<double> &f);

    ~SimpleDT (){
        delete []ans;
    }

    SimpleDT(const SimpleDT& o);

    SimpleDT &operator= (const SimpleDT &o);

    double distance_transform(uint q){
        return ans[q];
    }
};



class DistanceTransform
{
    Matrix<uint> grind;
    Matrix<uint> answer;
public:
    DistanceTransform (const Matrix<uint> &_in);
    void distance_transform();
    Matrix<uint> &get_answer(){return answer;}
};


#endif // DISTANCE_TRANSFORM_H
