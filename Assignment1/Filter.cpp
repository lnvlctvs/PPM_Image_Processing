#include "Filter.h"

Filter::Filter(Filter &f) {
	//Copy parameters
	params = f.params;
}

Filter::Filter() {
	
}
