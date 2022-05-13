#include <iostream>
#include <fstream>
#include <string>

#include "ppm.h"
#include "Image.h"
#include "Color.h"
#include "Array.h"

using namespace std;


int main(int argc, char *argv[]) {


	imaging::Image img = imaging::Image();

	string fname;
	argc = 2;
	argv[1] = "Image01.ppm";
	if (argc == 1) {
		cout << "File name of the image to load: ";
		cin >> fname;
	}
	else
		fname = argv[1];
	//Load the image
	if (img.load(fname, "ppm"))
		cout << "Loaded." << endl;

	cout << "Image dimensions are: " << img.getWidth() << "x" << img.getHeight() << endl;


	//Lets calculate the negative of this image
	for (int x = 0; x < img.getWidth(); x++)
		for (int y = 0; y < img.getHeight(); y++) {
			img.setPixel(x, y, imaging::Color(1, 1, 1) - img.getPixel(x, y));
		}
	//imaging::Image img2(img);

	if (!img.save("Image01_neg.ppm", "ppm"))
		cout << "Error in writing the file.";



	
	
	system("pause");
	return 0;
}

































/*
(A)
1. Read image and save it in Image class instance(name is argument 1, if not read from input)
2. Print diastaseis eikonas
3. Calculate the image's negative and save it in new file(by the help of WritePPM): *_neg.ppm


(B)
1. Ulopoiw thn ppm.lib pou antistoixei sthn ulopoihsh twn sunarthsewn ReadPPM kai WritePPM(ppm.h)
2. Ftiaxnw to antikeimeno tupou Image me thn voitheia ths ppm.lib
3. Image: vasikos upodoxeas eikonwn. Parexei sunarthseis gia prosvash k allagh dedomenwn ths eikonas
4. Oi sunarthseis load & save xrhsimopoioun tis ReadPPM kai WritePPM
5. Main: ektelei ta (A)
*/
