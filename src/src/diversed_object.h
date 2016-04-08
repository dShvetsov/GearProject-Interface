#ifndef DIVERSED_OBJECT_H
#define DIVERSED_OBJECT_H
#include "gear_object.h"
#include <vector>
#include <tuple>
using std::vector;
using std::tuple;
using std::tie;

class Diversed_object
{
private:
    uint obj_count = 0;
    uint next_obj_number = 2;
    Matrix<uint> pic;
    vector<uint> equal;
    vector<Object> obj;
    void connect(uint n, uint m);
    uint add_complies(uint n, uint m, uint i, uint j);
    uint add_obj(uint x, uint y);
    uint perfom_obj(uint n, uint x, uint y);
    void perfom();
    uint next_getting_object = 0;
public:
    vector<Object> &get_objects(){
        return obj;
    }
    uint get_obj_count() { return obj_count;}
    Diversed_object(Matrix<uint> &binpic);
    tuple<uint, uint, uint, uint> get_obj_bound(){
        if (next_getting_object == obj_count) return make_tuple(0,0,0,0);
        return obj[next_getting_object++].get_bound();
    }
    void Diver();
    Matrix<uint> &get_Matrix(){return pic;}

};



#endif // DIVERSED_OBJECT_H
