#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include "Array.h"
#include "Image.h"
#include <vector>
#include "Filter.h"
#include <cstdlib>

using namespace std;
using namespace math;


int main(int argc, char *argv[]) {
	
	if (argc == 1) {
		cout << "No args entered." << endl;
		system("pause");
		exit(0);
	}

	string filename;

	/* todo list is a two dimensional vector
	that contains the parameters of the filters
	*/
	vector<vector<float>> todo_list; 
	vector<float> linears; // the two temp vectors
	vector<float> gammas;
	vector<float> blurs;
	vector<float> laplace;


	for (int i = 1; i < argc; i++) {
			if (string(argv[i]) == "-f") {
				//if the following filter exists, its values will be stored to the array
				if (string(argv[i + 1]) == "linear") {
					if (i + 7 < argc) {
						if ( atof(argv[i+2]) != 0 && atof(argv[i + 3]) != 0 && atof(argv[i + 4]) != 0 && atof(argv[i + 5]) != 0 && atof(argv[i + 6]) != 0 && atof(argv[i + 7]) ) {
							linears.push_back(atof(argv[i + 2]));
							linears.push_back(atof(argv[i + 3]));
							linears.push_back(atof(argv[i + 4]));
							linears.push_back(atof(argv[i + 5]));
							linears.push_back(atof(argv[i + 6]));
							linears.push_back(atof(argv[i + 7]));
							todo_list.push_back(linears);
							linears.clear();
							i = i + 7;
						}
					}

				}
				else if (string(argv[i + 1]) == "gamma") {
					if (i + 2 < argc) {
						if (atof(argv[i + 2]) != 0) {
							if (atof(argv[i + 2]) <0.5 || atof(argv[i + 2]) >2.0) {
								cout << "Wront gamma input. The program will now exit." << endl;
								system("pause");
								exit(0);
							}
							gammas.push_back(atof(argv[i + 2]));
							todo_list.push_back(gammas);
							gammas.clear();
							i = i + 2;
						}
					}
				}
				else if (string(argv[i + 1]) == "blur") {
					if (i + 2 < argc) {
						if (atoi(argv[i + 2]) != 0) {
							blurs.push_back(atoi(argv[i + 2]));
							blurs.push_back(0.0);
							todo_list.push_back(blurs);
							blurs.clear();
							i = i + 2;
						}
					}
				}
				else if (string(argv[i + 1]) == "laplace") {
					if (i + 1 < argc) {

						laplace.push_back(0.0);
						laplace.push_back(0.0);
						laplace.push_back(0.0);
						todo_list.push_back(laplace);
						laplace.clear();
						i = i + 1;
					}
					
				}
				else {
					cout << "Wront filter input. The program will now exit." << endl;
					system("pause");
					exit(0);
				}
			}
			else if ( i+1 == argc && string(argv[i]).substr( string(argv[i]).length() - 4 , string(argv[i]).length()) == ".ppm") {
				filename = argv[i];
			}
			else {
				cout << "Undefined word: " << argv[i] << endl << "The program will now exit." << endl;
				system("pause");
				exit(0);
			}
		
	}


	//imaging::Image a;
	
	imaging::Image ret;
	if (!ret.load(filename, ".ppm")) {
		cout << "File not found!" << endl;
		system("pause");
		exit(0);
	}


	for (int i = 0; i < todo_list.size(); i++) {



		if (todo_list[i].size() == 1) {
			imaging::FilterGamma g(todo_list[i][0]);

			ret = g << ret;
			if (ret.save(filename, ".ppm")) {
				cout << "Gamma filter applied" << endl;
			}
			
		}
		else if (todo_list[i].size() == 2) {
			imaging::FilterBlur b(todo_list[i][0]);
			ret = b << ret;
			if (ret.save(filename, ".ppm")) {
				cout << "Blur filter applied" << endl;
			}
		}
		else if (todo_list[i].size() == 3) {
			imaging::FilterLaplace lapl;
			ret = lapl << ret;

			if (ret.save(filename, ".ppm")) {
				cout << "Laplace filter applied" << endl;

			}

		}
		else {
			imaging::FilterLinear l(todo_list[i][0], todo_list[i][1], todo_list[i][2], todo_list[i][3], todo_list[i][4], todo_list[i][5]);
			ret = l << ret;
			if (ret.save(filename, ".ppm")) {
				cout << "Linear filter applied" << endl;
				
			}
		}
	}





	system("pause");
}