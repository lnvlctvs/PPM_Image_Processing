#include "FilterLinear.h"


imaging::Image FilterLinear::operator << (const imaging::Image & image) {
	//p'(x,y) = a*p(x,y) + c
	
	imaging::Image tmp = imaging::Image(image);
	
	for (int x = 0; x < tmp.getWidth(); x++) {
		for (int y = 0; y < tmp.getHeight(); y++) { //Every single pixel

			math::Vec3<float> tmpColor = tmp.getObject(x,y);

			//a*p(x,y)
			tmpColor = tmpColor * imaging::Color(params[0], params[1], params[2]);

			//+ c
			tmpColor = tmpColor + imaging::Color(params[3], params[4], params[5]);

			tmpColor = tmpColor.clampToLowerBound(0);
			tmpColor = tmpColor.clampToUpperBound(1);
			tmp.setObject(x, y, tmpColor);
		}
	}
		return tmp;
	}