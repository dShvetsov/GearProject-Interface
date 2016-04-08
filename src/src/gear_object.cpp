#include "gear_object.h"
#include <tuple>
using std::tie;
using std::tuple;

void Object::mark(Image &in){
    uint x, y;
    tie(x, y) = center;
    in(x, y) = make_tuple(255, 255, 255);
}

uint Object::operator()(const Matrix<uint> &in) const {
    return in(0,0) == objid;
}
Object::Object(uint _objid, uint x, uint y):objid(_objid), mass_center(make_tuple(0,0)){
    xstart = xend = x;
    ystart = yend = y;
}
Matrix<uint> Object::GetBinPic(const Matrix<uint> &pic)
{
    Matrix<uint> ans = (pic.submatrix(xstart, ystart, xend - xstart, yend - ystart)).deep_copy();
    for (uint i = 0; i < ans.n_rows; i++){
        for (uint j = 0; j < ans.n_cols; j++){
            ans(i,j) = uint(pic(xstart + i, ystart + j) == objid);
        }
    }
    return ans;
}

Matrix<uint> Object::get_teeth(const Matrix<uint> &pic)
{
    double r, x, y;
    tie(x, y) = center;
    auto binpic = GetBinPic(pic);
    double thrs = ( rmax + rmin ) / 2;
    for (uint i = 0; i < binpic.n_rows; i++){
        for (uint j = 0; j < binpic.n_cols; j++){
            r = sqrt(((xstart + i) - x) * ((xstart + i) - x) + ((ystart + j) - y) * ((ystart + j) - y));
            if ( r  < thrs ){
                binpic(i,j) = 0;
            }
        }
    }
    return binpic;
}

double Object::compute_radius(Matrix<uint> &pic){
    double r;
    uint x, y;
    tie (x, y) = center;
    auto tmp =(pic.submatrix(xstart, ystart, xend - xstart, yend - ystart)).unary_map(*this);
    auto borderpic = tmp.unary_map(border());
    for (uint i = 1; i < borderpic.n_rows - 1; i++){
        for (uint j = 1; j < borderpic.n_cols - 1; j++){
            if (borderpic(i, j) == 1){
                r = sqrt(((xstart + i) - x) * ((xstart + i) - x) + ((ystart + j) - y) * ((ystart + j) - y));
                if (r > rmax){
                    rmax = r;
                }
                if (r < rmin){
                    rmin = r;
                }
            }
        }
    }
    return rmax;

}
object_t Object::detect_type(){
    if ((rmax - rmin) < 1.5){
        return AXIS;
    }else{
        return GEAR;
    }
}
tuple<uint, uint> Object::detect_mass_center(Matrix<uint> &pic){
    unsigned long long mass = 0;
    unsigned long long x = 0, y = 0;
    for(uint i = xstart; i <= xend; i++){
        for (uint j = ystart; j <= yend; j++){
             mass += (pic(i,j) == id);
              x += i * (pic(i,j) == id);
              y += j * (pic(i,j) == id);
          }
      }
      x = x / mass;
      y = y / mass;
      mass_center = make_tuple(x, y);
      return make_tuple(y, x);
}

void Object::merge(Object &obj){
    if (xstart > obj.xstart)
        xstart = obj.xstart;
    if (xend < obj.xend)
        xend = obj.xend;
    if (ystart > obj.ystart)
        ystart = obj.ystart;
    if (yend < obj.yend)
        yend = obj.yend;
}
void Object::update_axis(uint x, uint y){
    if (x < xstart)
        xstart = x;
    if (x > xend)
        xend = x;
    if (y < ystart)
        ystart = y;
    if (y > yend)
        yend = y;
}
tuple <uint, uint> Object::center_byDT(const Matrix<uint> &m){
    uint x, y;
    uint max = 0;
    for (uint i = 0; i < m.n_rows; i++){
        for (uint j = 0; j < m.n_cols; j++){
            if (m(i,j) > max){
                x = i;
                y = j;
                max = m(i,j);
            }
        }
    }
    center = make_tuple(xstart + x, ystart + y);
    return make_tuple(ystart + y, xstart + x);
}
void Object::insert(Image &in, const Image &from, Matrix<uint> grind, const Object &where)
{
    uint x, y, x1, y1;
    tie(x, y) = where.center;
    tie(x1, y1) = center;
    uint tmpx = x - x1, tmpy = y - y1;
    for (uint i = 0; i < grind.n_rows; i++){
        for (uint j = 0; j < grind.n_cols; j++){
            if (grind(i,j) == objid){
                in(tmpx + i, tmpy + j) = from(i, j);
            }
        }
    }
}
