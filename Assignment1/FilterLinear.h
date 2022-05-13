#ifndef _FILTERLIN
#define _FILTERLIN

#include "Filter.h"

class FilterLinear : public Filter {
public:
	
	imaging::Image operator << (const imaging::Image & image);

};



#endif