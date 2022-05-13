#ifndef _FILTERGAM
#define _FILTERGAM

#include "Filter.h"

class FilterGamma : public Filter {
public:

	imaging::Image operator << (const imaging::Image & image);

};



#endif