#include "ppm.h"
#include <fstream>

using namespace std;

namespace imaging
{
	bool WritePPM(const float * data, int w, int h, const char * filename) {
		size_t size = w*h * 3;
		//Output buffer
		char *buffer = new char[size];

		//Copy float data to buffer and convert them from [0,1] to [0,255]
		for (int i = 0; i < size; i++)
			buffer[i] = data[i]*255;



		try {
			ofstream f(filename, ios_base::binary);
			f << "P6" << '\n' << w << '\n' << h << '\n' << "255" << '\n';
			f.write(buffer, w*h * 3);
			f.close();
		}
		catch (void *err) {
			delete buffer;
			return 0;
		}
		delete buffer;
		return 1;
	}

	float * ReadPPM(const char * filename, int * w, int * h) {
		//Setup variables
		ifstream f(filename, ios_base::binary);
		if (!f) throw 1;
		int width, height, cMaxValue;
		char ppm_type[3];


		f >> ppm_type;
		if (strcmp(ppm_type, "P6"))
			throw 2; //Error code 2(isn't P6)

					 //Get width value
		if (!f.good())
			if (f.eof())
				throw 3;
			else
				throw 4;
		f >> width;
		if (width <= 0)
			throw 5;

		//Get height value
		if (!f.good())
			if (f.eof())
				throw 3;
			else
				throw 4;
		f >> height;
		if (height <= 0)
			throw 5;

		//Get colour maximum value of the colour components
		if (!f.good())
			if (f.eof())
				throw 6;
			else
				throw 4;
		f >> cMaxValue;
		if (cMaxValue <= 0)
			throw 7;

		*w = width;
		*h = height;
		//All good
		size_t size = width*height * 3;
		char *buffer = new char[size]; //na to kanw free mh ksexasw
		float *float_arr = new float[size];

		f.get();
		f.read(buffer, size);

		//Convert char to float and [0,255] to [0,1]
		for (int i = 0; i < size; i++) {
			float_arr[i] = (float)buffer[i]/255;
		}
		delete buffer;
		return float_arr;
	}
}