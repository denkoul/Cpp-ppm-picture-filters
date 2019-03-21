#ifndef _MATH
#define _MATH
#include <vector>
#include <string>
using namespace std;


namespace math {

	template <typename T> class Array {
	public:

	protected:
		vector<T> buffer;   //! Holds the data.

		unsigned int width,	height; //!Width and height of the image

	public:

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the width and height should be zero and the buffer must be set to nullptr.
		*/
		Array<T>() {
			this->width = 0;
			this->height = 0;
		}

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new Array.
		* \param height is the desired height of the new Array.
		*/
		Array<T>(unsigned int _width, unsigned int _height){
			this->width = _width;
			this->height = _height;
			buffer.resize(_width*_height);
		}

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new Array.
		* \param height is the desired height of the new Array.
		* \param data_ptr is the source of the data to copy to the internal Array buffer.
		*
		* \see setData
		*/
		Array<T>(unsigned int _width, unsigned int _height, const vector<T> * data_ptr) {
			this->width = _width;
			this->height = _height;
			buffer.resize(width*height);
			buffer = *data_ptr;

		}

		/*! Copy constructor.
		*
		* \param src is the source Array to replicate in this object.
		*/
		Array<T>(const Array &src) {
			this->width = src.width;
			this->height = src.height;
			buffer.resize(width*height);
			for (int i = 0; i < buffer.size(); i++) {
				buffer[i] = src.buffer[i];
			}
		}

		/*! The Array destructor.
		*/
		~Array() {
			buffer.clear();
		}

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const vector<T> & data_ptr) {
			if (width == 0 || height == 0 || buffer.empty() == true) {
				

				//buffer = const_cast <vector<T> >(data_ptr);
			}
			else {
				buffer = data_ptr;
			}

		}






		// metric accessors

		/*! Returns the width of the image
		*/
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		*/
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a pointer to the internal data.
		*
		*  This is NOT a copy of the internal image data, but rather a pointer
		*  to the internally allocated space, so DO NOT attempt to delete the pointer.
		*/


		vector<T> * getRawDataPtr() {
			return *buffer;
		};

		/*! Obtains the T item at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the T to get.
		*  \param y is the (zero-based) vertical index of the T to get.
		*
		*  \return The T object (x,y) . Returns a black (0,0,0) T in case of an out-of-bounds x,y pair.
		*/
		T getPoint(unsigned int x, unsigned int y) const {
			if (x <= width && y <= height) {
				unsigned int pixeloffset = y * width + x;
				return buffer.at(pixeloffset);
				
			}
			else {
				T x = 0;
				return x;
			}
		}



		/*! Sets the values for an (x,y) T.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the T to set.
		*  \param y is the (zero-based) vertical index of the T to set.
		*  \param value is the new T for the (x,y) T.
		*/
		void setPoint(unsigned int x, unsigned int y, T & value) {

			if (!(buffer.empty() || width == 0 || height == 0)) {
				buffer[width*y + x] = value;
				//cout << "set";
			}
		}

		T & operator () (int x, int y) {
			return   buffer.at(y * width + x);
		}






	};

}

#endif // !_MATH
