#ifndef _IMAGE
#define _IMAGE

#include "Array.h"
#include "Vec3.h"

namespace imaging
{
	typedef math::Vec3<float> Color;
	class Image: public math::Array<Color> {
	public:
		bool load(const std::string & filename, const std::string & format);

		bool save(const std::string & filename, const std::string & format);

		//Calling constructors
		Image() : math::Array<Color>() {

		}
		Image(unsigned int width, unsigned int height) : math::Array<Color>(width, height) {

		}
		Image(unsigned int width, unsigned int height, const std::vector<Color> data_ptr) : math::Array<Color>(width, height, data_ptr) {

		}
		Image(const Image &image) : math::Array<Color>(image) {

		}
	};

}

#endif