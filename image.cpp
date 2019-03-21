#include "Image.h"
#include <algorithm>
#include <string>

#include <ctype.h>
#include <iostream>

#include "ppm\ppm.h"

namespace imaging {



	bool Image::load(const std::string & filename, const std::string & format) {

		//check if the file ends with .ppm
		if (string(filename).substr(strlen(filename.c_str()) - 4, strlen(filename.c_str())) == ".ppm") {

			

			// if image is already initialized, erase width height and buffer
			if (width != 0 && height != 0) {
				width = 0;
				height = 0;
				buffer.clear();
			}




			int h = 0;
			int w = 0;
			//read ppm from the folder
			float *x = ReadPPM(filename.c_str(), &w, &h);

			// if there is no input, it will return false
			if (w == 0 || h == 0) {
				return false;
			}

			this->width = w;
			this->height = h;

			this->buffer.resize(width*height);



			//for each 3 colors (this is a pixel) save them to the color object in the buffer array

			int counter = 0;
			for (int i = 0; i < width*height * 3; i = i + 3) {
				buffer[counter].r = x[i];
				buffer[counter].g = x[i + 1];
				buffer[counter].b = x[i + 2];
				counter++;
			}


			//for every new there is a delete
			delete x;
			return true;


		}


		return false;
	}


	bool Image::save(const std::string & filename, const std::string & format) {


		float * neg_final = new float[width*height * 3]; // the returned array

		int counter = 0;
		
		for (int i = 0; i < width*height; i++) {
			neg_final[counter] = buffer[i].r;
			counter++;
			neg_final[counter] = buffer[i].g;
			counter++;
			neg_final[counter] = buffer[i].b;
			counter++;
		}


		string newname = "filtered_" + string(filename);
		bool x = imaging::WritePPM(neg_final, width, height, newname.c_str());

		//cout << x;

		//for each new there is a delete 
		delete  neg_final;
		if (x) {
			return true;
		}
		else {
			return false;
		}
	}
}


		

