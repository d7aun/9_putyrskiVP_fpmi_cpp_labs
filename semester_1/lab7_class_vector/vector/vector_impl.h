#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <initializer_list>

class Vector {
	int* data;
	size_t size;
	size_t cap;
public:
	Vector();
	Vector(size_t xSize);

	//initializer_list
	Vector(std::initializer_list<int> numbers);

	Vector(const Vector& other);
	~Vector();
	bool operator ==(const Vector& other);
	Vector operator =(const Vector& other);
	void Swap(Vector& other);
	int& operator [](size_t i) const;
	int& operator [](size_t i);
	int& At(size_t i) const;
	int& At(size_t i);
	size_t Size() const;
	size_t Capacity() const;
	void PushBack(int a);
	void PopBack();
	void Clear();
	void Reserve(size_t xCap);
};
std::ostream& operator<<(std::ostream& out, const Vector& vec);
