#include "vector_impl.h"
	Vector::Vector() {
		data = new int[0];
		size = 0;
		cap = 0;
	}
	Vector::Vector(size_t xSize) {
		data = new int[xSize];
		for (size_t i = 0; i < xSize; ++i)
			data[i] = 0;
		size = xSize;
		cap = xSize;
	}
	//initializer_list
	Vector::Vector(std::initializer_list<int> numbers) {
		int num = 0;
		size_t count = 0, i = 0;
		for (int num : numbers)
			++count;
		size = count;
		cap = count;
		data = new int[cap];
		for (int num : numbers) {
			data[i] = num;
			++i;
		}
	}
	Vector::Vector(const Vector& other) {
		size = other.size;
		cap = other.cap;
		data = new int[cap];
		for (size_t i = 0; i < size; ++i)
			data[i] = other.data[i];
	}
	Vector::~Vector() {
		delete[] data;
	}
	bool Vector::operator ==(const Vector& other) {
		if (size != other.size)
			return false;
		for (size_t i = 0; i < size; ++i)
			if (data[i] != other.data[i])
				return false;
		return true;
	}
	Vector Vector::operator =(const Vector& other) {
		if (*this == other)
			return *this;
		delete[] data;
		data = new int[other.cap];
		for (size_t i = 0; i < other.size; ++i)
			data[i] = other.data[i];
		size = other.size;
		cap = other.cap;
		return *this;
	}
	void Vector::Swap(Vector& other) {
		Vector tmp(*this);
		*this = other;
		other = tmp;
	}
	int& Vector::operator [](size_t i) const {
		return data[i];
	}
	int& Vector::operator [](size_t i) {
		return data[i];
	}
	int& Vector::At(size_t i) const  {
		if (i >= size)
			throw std::out_of_range{ "Out of range" };
		return data[i];
	}
	int& Vector::At(size_t i) {
		if (i >= size)
			throw std::out_of_range{ "Out of range" };
		return data[i];
	}
	size_t Vector::Size() const{
		return size;
	}
	size_t Vector::Capacity() const{
		return cap;
	}
	void Vector::PushBack(int a) {
		if (size == cap) {
			int* tmp;
			if (cap != 0) {
				cap *= 2;
				tmp = new int[cap];
 			}
			else {
				cap = 1;
				tmp = new int[1];
			}
				
			for (size_t i = 0; i < size; ++i) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
		}
		data[size] = a;
		++size;
	}
	void Vector::PopBack() {
		data[size-1] = 0;
		--size;
	}
	void Vector::Clear() {
		for (size_t i = 0; i < size; ++i)
			data[i] = 0;
		size = 0;
	}
	void Vector::Reserve(size_t xCap) {
		if (xCap > cap)
		{
			cap = xCap;
			int* tmp = new int[cap];
			for (size_t i = 0; i < size; ++i) {
				tmp[i] = data[i];
			}
			delete[] data;
			data = tmp;
		}
	}

	std::ostream& operator<<(std::ostream& out, const Vector& vec) {
		out << "[";
		size_t sz = vec.Size();
		if (sz > 0) {
			out << vec[0];
			for (size_t i = 1; i < sz; ++i)
				out << ", " << vec[i];
		}
		out << "]";
		return out;
	}
