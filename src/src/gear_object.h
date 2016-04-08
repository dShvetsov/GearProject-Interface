#ifndef GEAR_OBJECT_H
#define GEAR_OBJECT_H
#include <tuple>
#include "io.h"
using std::tuple;
using std::make_tuple;

#define MyINFINITY 4294967295

typedef enum{ GEAR, AXIS } object_t;

struct border
{
    static const int radius = 1;
    uint operator() (const Matrix<uint> &in) const{
        bool hlp = false;
        hlp |= (in(1, 0) == 0) | (in(1, 2) == 0);
        hlp |= (in(0, 1) == 0) | (in(2, 1) == 0);
        if (hlp && in(1,1) == 1){
            return 1;
        }
        else{
            return 0;
        }
    }
};

class Object
{
private:
    uint xstart = 0, xend = 0, ystart = 0, yend = 0;
    uint objid;
    bool valid = false;
    uint id = 0;
    tuple <uint, uint> mass_center, center = make_tuple(0,0);
    object_t type = GEAR;
public:
    friend double distance_beetwen_objects(const Object& ,const Object& );
    friend bool suitable_gear(const Object&, const Object&, const Object &);
    double rmin = MyINFINITY, rmax = 0;
    static const int radius = 0;

    void mark(Image &in);

    uint operator()(const Matrix<uint> &in) const;
    Object(uint _objid, uint x, uint y);
    Matrix<uint> GetBinPic(const Matrix<uint> &pic);

    Matrix<uint> get_teeth(const Matrix<uint> &pic);

    double compute_radius(Matrix<uint> &pic);
    object_t detect_type();
    tuple<uint, uint> detect_mass_center(Matrix<uint> &pic);
    tuple<uint, uint> get_mass_center(){return mass_center;}
    tuple<uint, uint, uint, uint> get_bound()
    {
        return make_tuple(xstart, xend, ystart, yend);
    }
    void set_id(uint _id){
        id = _id;
        valid = true;
    }
    bool validable(){return valid;}
    void merge(Object &obj);
    void update_axis(uint x, uint y);
    tuple <uint, uint> center_byDT(const Matrix<uint> &m);
    void insert(Image &in, const Image &from, Matrix<uint> grind, const Object &where);
};



#endif // GEAR_OBJECT_H
