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

class Inv
{
public:
    tuple<uint, uint, uint> operator () (const Image &m) const
    {
        uint r, g, b;
        tie(r, g, b) = m(0, 0);
        return make_tuple(g, b, r);
    }
    // Radius of neighbourhoud, which is passed to that operator
    static const int radius = 0;
};

class Inversion : public IPlugin
{
	const char *stringType(){
		return "inversepic";
	}
	Image operation(Image &im){
		Image ans = Image(im.unary_map(Inv()));
		return ans;
	}
};

// list of constructed plugins to perform memory managment
IPlugin* plugin;

// entry point in the dll
extern "C" IPlugin* registerPlugins(const char* type)
{
	plugin = new Inversion;
	return plugin;
}

void _init(){
}
void _fini(){
	delete plugin;
}
