#ifndef _ARRAY
#define _ARRAY

#include <string>

namespace math {

	template <class T>
	class Array {
	public:
		std::string tmpp;
	protected:
		std::vector<T> buffer;

		unsigned int width, height;

	public:
		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		std::vector<T> getRawDataPtr();

		T getTriple(unsigned int x, unsigned int y) const;

		void setTriple(unsigned int x, unsigned int y, T & value);

		void setData(const std::vector<T> & data_ptr);

		Array();

		Array(unsigned int width, unsigned int height);

		Array(unsigned int width, unsigned int height, const std::vector<T> data_ptr);

		Array(const Array<T> &src);

		~Array();

		Array & operator = (const Array<T> & right);

		T operator()(int i, j);
	};
}


#endif