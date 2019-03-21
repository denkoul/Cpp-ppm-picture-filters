#include "Image.h"

#ifndef _FILTER

#define _FILTER



namespace imaging {
	class Filter {
	public:
		virtual Image operator << (const Image & image) = 0;
	};

}
#endif // !FILTER




#ifndef _gamma
#define _gamma

#include <math.h>  

namespace imaging {
	class FilterGamma : public Filter {
	protected:
		float c;


	public:
		//default constructor will remain the same
		FilterGamma() {
			c = 1;
		}

		//constructor with parameter for c
		FilterGamma(float c) {
			this->c = c;
		}

		Image operator << (const Image & image) {

			int width = image.getWidth();
			int height = image.getHeight();
			Image im2(image.getWidth(), image.getHeight());      //im2 is the copy of the image (cause the image is const)
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {



					Vec3<float> temp = image.getPoint(i, j);

					temp.r = pow(temp.r, c);
					temp.g = pow(temp.g, c);
					temp.b = pow(temp.b, c);

					//if the color range extends the bounds (0.0, 1.0) set to the max/min value
					if (temp.r > 1.0) temp.r = 1.0;
					if (temp.r < 0.0) temp.r = 0.0;

					if (temp.g > 1.0) temp.g = 1.0;
					if (temp.g < 0.0) temp.g = 0.0;

					if (temp.b > 1.0) temp.b = 1.0;
					if (temp.b < 0.0) temp.b = 0.0;



					im2.setPoint(i, j, temp);


				}

			}
			return im2;
		}

	};
}
#endif // !_gamma




#ifndef _linear
#define _linear

namespace imaging {
	class FilterLinear : public Filter {
	protected:
		Vec3<float> _a, _c;


	public:
		//default constructor will create negative
		FilterLinear() {
			_a.r = -1;
			_a.g = -1;
			_a.b = -1;
			_c.r = 1;
			_c.g = 1;
			_c.b = 1;
		}

		//constructor with parameters for the static a and c
		FilterLinear(float a1, float a2, float a3, float c1, float c2, float c3) {
			_a.r = a1;
			_a.g = a2;
			_a.b = a3;
			_c.r = c1;
			_c.g = c2;
			_c.b = c3;
		}

		Image operator << (const Image & image) {

			int width = image.getWidth();
			int height = image.getHeight();

			Image im2(image.getWidth(), image.getHeight());


			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					Vec3<float> temp = _a*image.getPoint(i, j) + _c;


					//if the color range extends the bounds (0.0, 1.0) set to the max/min value
					if (temp.r > 1.0) temp.r = 1.0;
					if (temp.r < 0.0) temp.r = 0.0;

					if (temp.g > 1.0) temp.g = 1.0;
					if (temp.g < 0.0) temp.g = 0.0;

					if (temp.b > 1.0) temp.b = 1.0;
					if (temp.b < 0.0) temp.b = 0.0;

					im2.setPoint(i, j, temp);

				}

			}
			return im2;
		}

	};
}

#endif



#ifndef _blur
#define _blur

#include "Array.h"
#include <math.h>  

namespace imaging {
	class FilterBlur : public Filter,public Array<float> {
	protected:
		float N;
	public:
		//default constructor will give 1 value to N
		FilterBlur() {
			N = 1;
			float _n = 1 / pow(N, 2);
			//set the array dimensions
			Array::width = N;
			Array::height = N;
			for (int i = 0; i < N*N; i++) {
				Array::buffer.push_back(_n);
			}
		}

		//constructor with parameter for N
		FilterBlur(int N) {
			this->N = N;
			float _n = 1 / pow(N, 2);
			//set the array dimensions
			Array::width = N;
			Array::height = N;
			for (int i = 0; i < N*N; i++) {
				Array::buffer.push_back(_n);
			}
		}

		~FilterBlur() { //destructor
			Array<float>::~Array();
		}
		Image operator << (const Image & image) {
			Image im2(image.getWidth(), image.getHeight());


			for (int i = 0; i < image.getWidth(); i++) {
				for (int j = 0; j < image.getHeight(); j++) {
					Vec3<float> sum;
					for (int m = -N / 2; m < N / 2; m++) {
						for (int n = -N / 2; n < N / 2; n++) {
							//bound check
							if (0 <= i + m && i + m < image.getWidth() && 0<= j+n && j+n < image.getHeight() ) {
								sum += image.getPoint(i + m, j + n)*Array::getPoint(m+N/2, n+N/2 );
							}
							else if (0 <= i + m && i + m < image.getWidth()) {//if n out of bounds
								sum += image.getPoint(i + m, j )*Array::getPoint(m + N / 2, n + N / 2);
							}
							else if (0 <= j + n && j + n < image.getHeight()) { // if m out of bounds
								sum += image.getPoint(i, j + n)*Array::getPoint(m + N / 2, n + N / 2);
							}
						}
					}



					if (sum.r > 1.0) sum.r = 1.0;
					if (sum.r < 0.0) sum.r = 0.0;

					if (sum.g > 1.0) sum.g = 1.0;
					if (sum.g < 0.0) sum.g = 0.0;

					if (sum.b > 1.0) sum.b = 1.0;
					if (sum.b < 0.0) sum.b = 0.0;




					im2.setPoint(i, j, sum);
				}
			}
			return im2;
		}
	};
}
#endif // !_blur




#ifndef _laplace
#define _laplace

#include "Array.h"
#include <math.h> 
#include "Vec3.h"

namespace imaging {
	class FilterLaplace : public FilterBlur {
	public:
		FilterLaplace()  {
			Array::width = 3;
			Array::height = 3;
		}
		Image operator << (const Image & image) {

			//fin pointer represents the const casted image
			//im2 is a copy of the original image so we can get the original values from there


			//Image * fin = const_cast<Image*>(&image); const cast solution. it will return the *fin

			Image im2(image.getWidth(), image.getHeight());
			buffer.resize(9);
			Array<float>::buffer[0] = 0;
			Array<float>::buffer[1] = 1;
			Array<float>::buffer[2] = 0;
			Array<float>::buffer[3] = 1;
			Array<float>::buffer[4] = -4;   // buffer allocation
			Array<float>::buffer[5] = 1;
			Array<float>::buffer[6] = 0;
			Array<float>::buffer[7] = 1;
			Array<float>::buffer[8] = 0;
			for (int i = 0; i < image.getWidth(); i++) {
				for (int j = 0; j < image.getHeight(); j++) {
					Vec3<float> sum(0,0,0);
					for (int m = -1; m <= 1; m++) {
						for (int n = -1; n <= 1; n++) {
							if (0 <= i + m && i + m < image.getWidth() && 0 <= j + n && j + n < image.getHeight()) {
								sum += image.getPoint(i + m, j + n)*getPoint(m + 1, n + 1); //the sum
							}
						}
					}
					//the min and max
					Vec3<float> min = sum.clampToUpperBound(1.0);
					Vec3<float> max = min.clampToLowerBound(0.0);
					im2.setPoint(i, j, max);

				}

			}
			
			return im2;
		}
	};
}

#endif // !_laplace








