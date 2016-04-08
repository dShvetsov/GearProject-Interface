//.dll 1

#include <forward_list>
#include "../API.h"
#include <string>
#include <iostream>
#include "matrix.h"
#include "io.h"

using std::string;
using std::cout;
using std::endl;

using std::tuple;
using std::get;
using std::tie;
using std::make_tuple;

// Matrix usage example
// Also see: matrix.h, matrix.hpp for comments on how filtering works

class BoxFilterOp
{
public:
    tuple<uint, uint, uint> operator () (const Image &m) const
    {
        uint size = 2 * radius + 1;
        uint r, g, b, sum_r = 0, sum_g = 0, sum_b = 0;
        for (uint i = 0; i < size; ++i) {
            for (uint j = 0; j < size; ++j) {
                // Tie is useful for taking elements from tuple
                tie(r, g, b) = m(i, j);
                sum_r += r;
                sum_g += g;
                sum_b += b;
            }
        }
        auto norm = size * size;
        sum_r /= norm;
        sum_g /= norm;
        sum_b /= norm;
        return make_tuple(sum_r, sum_g, sum_b);
    }
    // Radius of neighbourhoud, which is passed to that operator
    static const int radius = 1;
};

class filter : public IPlugin
{
	const char *stringType(){
		return "BoxFilter";
	}
	Image operation(Image &im){
		Image ans = Image(im.unary_map(BoxFilterOp()));
		return ans;
	}
};

// list of constructed plugins to perform memory managment
IPlugin* plugin;

// entry point in the dll
extern "C" IPlugin* registerPlugins(const char* type)
{
	plugin = new filter;
	return plugin;
}

