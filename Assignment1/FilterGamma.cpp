#include "FilterGamma.h"

imaging::Image FilterGamma::operator << (const imaging::Image & image) {
	//p'(x,y) = p(x,y)^g
	
	imaging::Image tmp = imaging::Image(image);

	
	
	for (int x = 0; x < tmp.getWidth(); x++) {
		for (int y = 0; y < tmp.getHeight(); y++) { //Every single pixel
			
			//We have no operator for power(g is stored in params[0])
			imaging::Color tmpColor = tmp.getObject(x, y);

			tmpColor.r = pow(tmpColor.r, params[0]);


			tmpColor.g = pow(tmpColor.g, params[0]);

			tmpColor.b = pow(tmpColor.b, params[0]);

			
			tmpColor = tmpColor.clampToLowerBound(0);
			tmpColor = tmpColor.clampToUpperBound(1);


			tmp.setObject(x, y, tmpColor);


		}
	}
	return tmp;
}