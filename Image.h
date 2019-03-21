//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

//#pragma once

#ifndef _image
#define _image
#include <string>

#include "Vec3.h"
#include "Array.h"



using namespace math;

namespace imaging
{

	class Image : public math::Array<math::Vec3<float>>
	{
	public:
		Image::Image() : Array<Vec3<float>>() {}

		Image::Image(unsigned int w, unsigned int h) : Array<Vec3<float>>(w,h) {}

		Image::Image(unsigned int w, unsigned int h, const vector<Vec3<float>> * data) : Array<Vec3<float>>(w, h, data) {}

		Image::Image(const Image &src) : Array(src) {}

		

		bool load(const std::string & filename, const std::string & format);
		bool save(const std::string & filename, const std::string & format);

	protected:

	};

}

#endif // !image