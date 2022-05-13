#ifndef ARR_H
#define ARR_H

#include <vector>
#include "Vec3.h"


namespace math {

	template <class T>
	class Array {
	protected:

		std::vector<T> buffer;

		unsigned int width, height;

	public:
		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		std::vector<T> getVectorData() const {
			return buffer;
		}

		T getObject(unsigned int x, unsigned int y) const {
			return buffer[(x + y*width)];
		}

		void setObject(unsigned int x, unsigned int y, T & value) {
			buffer[(x + y*width)] = value;
		}

		void setData(const std::vector<T> & data) {
			if (width == 0 || height == 0)
				return;
			buffer = data;
		}

		Array() {
			width = 0;
			height = 0;
		}

		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
		}

		Array(unsigned int width, unsigned int height, const std::vector<T> data_ptr) {
			this->width = width;
			this->height = height;
			buffer = data_ptr;
		}

		Array(const Array<T> &src) {
			width = src.getWidth();
			height = src.getHeight();
			buffer = src.getVectorData();
		}

		Array & operator = (const Array<T> & right) {
			width = right.getWidth();
			height = right.getHeight();
			buffer = right.getVectorData();
			return *this;
		}

		T operator()(int i, int j) {
			return buffer[(x + y*width)];
		}
	};
}
#endif