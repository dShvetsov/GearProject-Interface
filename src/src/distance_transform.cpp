#include "distance_transform.h"
#include "diversed_object.h"
#include <cstring>

SimpleDT::SimpleDT(const vector<double>& input)
{
    ans = new double[input.size()];
    size = input.size();
    implamatation_of_distance_transform(input);
}
void SimpleDT::implamatation_of_distance_transform(const vector<double> &f){
    uint k = 0;
    double *v = new double[f.size()], *z = new double[f.size() + 10];
    v[0] = 0;
    z[0] = -MyINFINITY;
    z[1] = MyINFINITY;
    double s;
    for (uint q = 1; q < f.size(); q++){
        while ((s = ((f[q] + q * q) - (f[v[k]] + v[k] * v[k]))/(2 * q - 2 * v[k])) <= z[k]){
            k--;
        }
        k++;
        v[k] = q;
        z[k] = s;
        z[k + 1] = MyINFINITY;
    }
    k = 0;
    for (uint q = 0; q < f.size(); q++){
        while (z[k + 1] < q)
            k++;
        ans[q] = (q - v[k]) * (q - v[k]) + f[v[k]];
    }
    delete []z;
    delete []v;
}


SimpleDT::SimpleDT(const SimpleDT& o){
    ans = new double[o.size];
    size = o.size;
    memcpy(ans, o.ans, sizeof(double) * o.size);
}

SimpleDT &SimpleDT::operator= (const SimpleDT &o){
    ans = new double[o.size];
    size = o.size;
    memcpy(ans, o.ans, sizeof(double) * o.size);
    return *this;
}




vector<double> Matrix2vector(const Matrix<uint>& in, uint q){
    vector<double> ans;
    for (uint i = 0; i < in.n_rows; i++){
        ans.push_back( double(in(i, q)));
    }
    return ans;
}

DistanceTransform::DistanceTransform (const Matrix<uint> &_in): grind(_in.deep_copy()), answer(_in){
    for (uint i = 0; i < grind.n_rows; i++){
        for (uint j = 0; j < grind.n_cols; j++){
            if (grind(i,j) != 0){
                grind(i,j) = MyINFINITY;
            }
        }
    }
}
void DistanceTransform::distance_transform(){
    vector<SimpleDT> hlp;
    for (uint i = 0; i < grind.n_cols; i++)
    {
        hlp.push_back(SimpleDT(Matrix2vector(grind, i)));
    }
    vector<double> tmp(grind.n_cols, 0);

    for (uint i = 0; i < grind.n_rows; i++){
        for(uint j = 0; j < grind.n_cols; j++){
            tmp[j] = hlp[j].distance_transform(i);
        }
        SimpleDT temp2DT(tmp);
        for (uint j = 0; j < grind.n_cols; j++){
            answer(i,j) = temp2DT.distance_transform(j);
        }
    }
}
