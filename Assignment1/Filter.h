#ifndef _FILTER
#define _FILTER

#include "Image.h"

class Filter {
public:
	std::vector<float> params;

	virtual imaging::Image operator << (const imaging::Image & image) = 0;

	Filter();

	Filter(Filter &f);
};


#endif