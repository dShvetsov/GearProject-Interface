

//.dll 1

#include <forward_list>
#include "../API.h"
#include <string>
#include <iostream>
#include "matrix.h"
#include "io.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;

using std::tuple;
using std::get;
using std::tie;
using std::make_tuple;

// Matrix usage example
// Also see: matrix.h, matrix.hpp for comments on how filtering works

class Median
{
public:
    tuple<uint, uint, uint> operator () (const Image &m) const
    {
		
        uint r, g, b;
        vector<uint> rset, gset, bset;
		uint size = 2 * radius + 1;
		for (uint i = 0; i < size; i++)
		{
			for (uint j = 0; j < size; j++)
			{
				tie(r,g,b) = m(i,j);
				rset.push_back(r);
				gset.push_back(g);
				bset.push_back(b);
			}
		}
		std::sort(rset.begin(), rset.end());
		std::sort(gset.begin(), gset.end());
		std::sort(bset.begin(), bset.end());
        return make_tuple(rset[12], gset[12], bset[12]);
    }
    // Radius of neighbourhoud, which is passed to that operator
    static const int radius = 2;
};

class MedianFilter : public IPlugin
{
	const char *stringType(){
		return "Median";
	}
	Image operation(Image &im){
		Image ans = Image(im.unary_map(Median()));
		return ans;
	}
};

// list of constructed plugins to perform memory managment
IPlugin* plugin;

// entry point in the dll
extern "C" IPlugin* registerPlugins(const char* type)
{
	plugin = new MedianFilter;
	return plugin;
}


void _init(){
}
void _fini(){
	delete plugin;
}
