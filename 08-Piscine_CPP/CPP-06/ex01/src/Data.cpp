#include "../include/Data.hpp"

Data::Data(): value(42) {}

Data::Data(const Data& other): value(other.value) {}

Data::~Data() {}

Data&	Data::operator =(const Data& other)
{
	if (this != &other)
		value = other.value;
	return *this;
}
