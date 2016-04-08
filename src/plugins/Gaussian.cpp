
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

class Gauss
{
public:
    tuple<uint, uint, uint> operator () (const Image &m) const
    {
        double factor[5][5] = {{ 0.003, 0.013, 0.022, 0.013, 0.003},
				{0.013, 0.059, 0.097, 0.059, 0.013},
				{0.022, 0.097, 0.159, 0.097, 0.013},
				{0.013, 0.059, 0.097, 0.059, 0.013},
				{ 0.003, 0.013, 0.022, 0.013, 0.003}};
        uint r, g, b;
        double r1 = 0, g1 = 0, b1 = 0;
		uint size = 2 * radius + 1;
		for (uint i = 0; i < size; i++)
		{
			for (uint j = 0; j < size; j++)
			{
				tie(r,g,b) = m(i,j);
				r1 += double(r) * factor[i][j];
				g1 += double(g) * factor[i][j];
				b1 += double(b) * factor[i][j];
			}
		}
        return make_tuple((uint)r1, (uint)g1, (uint)b1);
    }
    // Radius of neighbourhoud, which is passed to that operator
    static const int radius = 2;
};

class GaussFilter : public IPlugin
{
	const char *stringType(){
		return "Gaussian";
	}
	Image operation(Image &im){
		Image ans = Image(im.unary_map(Gauss()));
		return ans;
	}
};

// list of constructed plugins to perform memory managment
IPlugin* plugin;

// entry point in the dll
extern "C" IPlugin* registerPlugins(const char* type)
{
	plugin = new GaussFilter;
	return plugin;
}


void _init(){
}
void _fini(){
	delete plugin;
}
