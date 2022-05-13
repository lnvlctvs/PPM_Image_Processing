#include <iostream>
#include "Color.h"
#include "ppm.h"
#include "Image.h"
#include <string>

using namespace imaging;

/*
Having:
Color * buffer;                              //! Holds the image data.
unsigned int width, height;
*/

Color * Image::getRawDataPtr() {
	return buffer;
}


Color Image::getPixel(unsigned int x, unsigned int y) const {
	return buffer[(x + y*width)];
}

void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		buffer[(x + y*width)] = value;
}

void Image::setData(const Color * & data_ptr) {
	if (width == 0 || height == 0 || buffer == nullptr)
		return;
	*buffer = *data_ptr;

}

Image::Image() {
	width = 0;
	height = 0;
	buffer = nullptr;
}
	

Image::Image(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
	if (width == 0 || height == 0 || data_ptr == nullptr)
		return;
	this->width = width;
	this->height = height;
	*buffer = *data_ptr;
}

Image::Image(const Image &src) {
	width = src.getWidth();
	height = src.getHeight();
	//Image conv = src;
	//buffer = conv.getRawDataPtr(); /*CHECK ThiS----------------------------------------*/
}

Image::~Image() {
	delete buffer;
}

//Image & Image::operator = (const Image & right) {
//	Image d;
//	width = right.getWidth();
//	height = right.getHeight();
//	Image conv = right;
//	buffer = conv.getRawDataPtr(); /*CHECK ThiS----------------------------------------*/
//	return d;
//}

bool Image::load(const std::string & filename, const std::string & format) {
	if (width != 0) {
		//initialized image object
		width = 0;
		height = 0;
		delete buffer;
	}
	float *img_data = nullptr;
	if (_strcmpi("ppm", format.c_str()))
		return 0;
	int wd, hg;
	//PPM Format
	try {
		img_data = imaging::ReadPPM(filename.c_str(), &wd, &hg);
	}
	catch (int err) {
		switch (err) {
		case 1:
			std::cout << "Error - Failed to open file.";
			break;
		case 2:
			std::cout << "Error - The file is not P6 type.";
			break;
		case 3:
			std::cout << "Error - Missing width/height from the file.";
			break;
		case 4:
			std::cout << "Error - Something happened with the file, maybe has been deleted.";
			break;
		case 5:
			std::cout << "Error - The file is corrupted or missing width/height from the file(got negative values)";
			break;
		case 6:
			std::cout << "Error - Missing maximum value of the colour components.";
			break;
		case 7:
			std::cout << "Error - The file is corrupted or missing maxinum value of the colour components(got negative value).";
			break;
		}
	}
		//We know that wd and hg are >0 (if one of them were negative, it throws error above) so:
		width = wd;
		height = hg;
		int x = 5;
		//Clear with errors
		buffer = new Color[width*height];
		for (int i = 0; i < width*height; i += 1) {
			buffer[i] = Color(img_data[i*3], img_data[i*3 + 1], img_data[i*3 + 2]);
		}
		return 1;
	}
bool Image::save(const std::string & filename, const std::string & format) {
	if (buffer == nullptr)
		return 0;
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (strcmp(extension.c_str(), format.c_str()) != 0)
		return 0;

	//Clear with errors
	float *new_data = new float[width*height * 3];
	
	for (int i = 0; i < width*height; i++) {
		new_data[i * 3] = buffer[i].r;
		new_data[i * 3 + 1] = buffer[i].g;
		new_data[i * 3 + 2] = buffer[i].b;
	}

	try {
		imaging::WritePPM(new_data, width, height, filename.c_str());
		delete new_data;
	}
	catch (void *error) {
		return 0;
	}

	return 1;
}