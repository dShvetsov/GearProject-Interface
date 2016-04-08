#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <limits>
#include <vector>
#include <tuple>
#include <memory>
#include <cstdio>
#include <list>
#include "gear_object.h"


using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::ofstream;
using std::vector;
using std::tuple;
using std::tie;
using std::make_tuple;
using std::shared_ptr;
using std::vector;
using std::iterator;
using std::list;
using std::tuple;

#include "io.h"
#include "matrix.h"
#include "MyObject.h"





typedef unsigned long long ulonglong; 


bool suitable_gear(const Object &q, const Object &one, const Object &where)
{
	uint a, b, c, d;
	tie(a,b) = where.center;
	tie(c, d) = one.center;
	double r = sqrt( (a - c) * (a - c) + (b - d) * (b - d));
	return (r > q.rmax + one.rmin && r > q.rmin + one.rmax && r < q.rmax + one.rmax);
}

double distance_beetwen_objects(const Object& one, const Object& two){
	uint x1, x2, y1, y2;
	tie(x1, y1) = one.center;
	tie(x2, y2) = two.center;
	return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}







/*

int main1(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: " << endl << argv[0]
             << " <in_image.bmp> <out_image.bmp> <out_result.txt>" << endl;
        return 0;
    }

    try {
        Image src_image = load_image(argv[1]);
        ofstream fout(argv[3]);

        vector<shared_ptr<IObject>> object_array;
        Image dst_image;
        int result_idx;
        tie(result_idx, object_array, dst_image) = repair_mechanism(src_image,  argv[1]);
        save_image(dst_image, argv[2]);

        fout << result_idx << endl;
        fout << object_array.size() << endl;
        for (const auto &obj : object_array)
            obj->Write(fout);

    } catch (const string &s) {
        cerr << "Error: " << s << endl;
        return 1;
    }
} */
