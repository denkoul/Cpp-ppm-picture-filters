#include "ppm.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define _PPM
namespace imaging {
	float * ReadPPM(const char * filename, int * w, int * h) {
		//cout << filename << endl;
		

		//check if the file ends with .ppm
		/*
		int filename_len = strlen(filename);
		if (filename_len >= 4 && strcmp(filename + filename_len - 4, ".ppm") == 0) {
		
		..

		}
		*/

		ifstream ppm_file;
		ppm_file.open(filename, ios::in | ios::binary);
		if (!ppm_file.is_open()) {
			cout << "Error! File could not be opened" << endl;
		}
		else {



			//check if the file is P6 type
			string p_type;
			ppm_file >> p_type;
			if (p_type == "P6") {
				
				//get header data

				string  line;
				int width;
				int height;
				int color = -1;
				int counter = 0;



				/*counter: counter state defines the level of data entry
				counter == 1 : width is entered
				counter == 2 : height is entered
				counter == 3 : color is entered
				counter == 4 : everything is ok
				if line starts with # skip it

				*/
				while (counter < 4) {
					
					ppm_file >> line;
					
					
					//check if line starts with # and skip it
					while (line.at(0) == '#') {
						ppm_file.ignore(256, '\n'); // ignore the line untill line break is found
						ppm_file >> line;
					}

					try {
						

						//cout << line << endl;
						
						if (counter == 0) {
							counter = 1;
							width = stoi(line);
						}
						else if (counter == 1) {
							counter = 2;
							height = stoi(line);
							
						}
						else if (counter == 2) {
							counter = 3;
							color = stoi(line);
							
							if (color > 255) {
								cout << "Error! Reached color limit!" << endl;
								break;
							}
							
							//print dimensions
							cout << "Image dimensions are: " << width << " X " << height << endl;
							//program is ready to procceed
							counter = 4;
							
						}



					}
					catch (invalid_argument &e) {

						//catch the stoi ecxeption
						cout << "There are some errors in the header!!!" << endl;
						//try to find where the error is
						if (counter == 1) {
							cout << "Width is not entered correctly" << endl;
						}
						if (counter == 2) {
							cout << "height is not entered correctly" << endl;
						}
						if (counter == 3) {
							cout << "Color is not entered correctly" << endl;
						}
						break;
					}
				}

				if (counter == 4) {
					/*so if we have reached this place it means
					that the ppm survived the header check

					here we will try to read the image data to the array
					*/
					*w = width;
					*h = height;

					ppm_file.get();//skip the white-space


					//initialize temp array to store the binary values
					unsigned char*buffer;

					// size: the sum of all the rbg colors
					unsigned int size = 3 * width * height;


					//temp array 
					buffer = new unsigned char[size];
					

					//add the binary data to the array
					ppm_file.read((char*)buffer, size);
					

					//create the new float array
					float * image_data = new float[size];
					

					//store to the new array the final values (0.0 to 1.0)
					for (unsigned int i = 0; i < size; ++i) {
						image_data[i] = (float)(int)buffer[i]/(float)color; //cast buffer to int and cast the result to float
						
					}

					ppm_file.close();
					//erase the memory
					delete buffer;
					//return the pointer
					return image_data;

					




				}
				else {
					cout << "The program will now terminate!" << endl;
					ppm_file.close();
				}
				


			}
			else {
				cout << "This PPM file is not P6 type" << endl;
				ppm_file.close();
			}
		}
		

		ppm_file.close();
		return nullptr;

	}


	bool WritePPM(const float * data, int w, int h, const char * filename) {



		//read again the original image to get the max color
		ifstream ppm_file;
		//remove the filtered_
		string oldname = string(filename).substr(9,strlen(filename));
		ppm_file.open(oldname, ios::out | ios::binary);
		//because the filename will pass all the checks in the ReadPPM, we will just read the max color again
		int color;
		string type;
		ppm_file >> type;
		ppm_file >> color >> color >> color;
		ppm_file.close();





		
		//generate the new name that ends to _neg.ppm
		// we removed the last 4 chars (the extension .ppm) and added the new extension with a _neg in front
		//string newname = string(filename).substr(0, strlen(filename)-4);
		

		ofstream ppm_neg(filename, ios::binary);
		

		ppm_neg << "P6";

		ppm_neg << endl;

		ppm_neg << w;

		ppm_neg << endl;

		ppm_neg << h;

		ppm_neg << endl;

		ppm_neg << color;

		ppm_neg << endl;
		
		//header is ready

		
		
		
		for (unsigned int i = 0; i < h * w * 3; i++) {
			ppm_neg << (char)((data[i])*(float)color);
		}







		ppm_neg.close();
		if (ppm_neg.is_open()) {
			return false;
		}
		else {
			return true;
		}
		

	}
}
