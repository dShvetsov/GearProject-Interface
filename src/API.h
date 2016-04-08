#ifndef API_H
#define API_H

#include <io.h>
// abstract plugin
class IPlugin
{
public:
  // returns string name of the plugin
	virtual const char* stringType() = 0;
  // applyfilter to image
	virtual Image operation(Image& object) = 0;

};


// type of a function that searches plugins in the dll
typedef IPlugin* (*regFuncType)();

#endif
