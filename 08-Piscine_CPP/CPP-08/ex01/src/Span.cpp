#include "../include/Span.hpp"

Span::Span(void) : _n(1) {}

Span::Span(unsigned int n) : _n(n) {
	if (!_n)
		throw InvalidSizeException();
}

Span::Span(const Span& other): _n(other._n)
{
	*this = other;
}

Span::~Span() {}

Span&	Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_n = other._n;
		_numbers = other._numbers;
	}
	return *this;
}

void	Span::addNumber(int n) {
	if (_numbers.size() == _n)
		throw NoElementsLeftException();
	_numbers.push_back(n);
}

void	Span::addNumber(std::vector<int>::const_iterator it1, std::vector<int>::const_iterator it2) {
	while (it1 < it2)
	{
		if (_numbers.size() == _n)
			throw NoElementsLeftException();
		_numbers.push_back(*it1);
		it1++;
	}
}

unsigned long	Span::shortestSpan() {
	if (_numbers.size() < 2)
		throw NoElementsException();

	std::sort(_numbers.begin(), _numbers.end());

	unsigned int span = -1;
	unsigned int tmp = 0;

	std::vector<int>::const_iterator it = _numbers.begin();

	while (it < _numbers.end())
	{
		if ((tmp = std::abs(*it - *(it + 1))) < span)
			span = tmp;
		++it;
	}

	return span;
}

unsigned long	Span::longestSpan() const{
	if (_numbers.size() < 2)
		throw NoElementsException();

	std::vector<int>::const_iterator min = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator max = std::max_element(_numbers.begin(), _numbers.end());

	return std::labs(long(*min) - long(*max));
}

const char*	Span::InvalidSizeException::what() const throw()
{
	return "Size can't be zero";
}

const char*	Span::NoElementsException::what() const throw()
{
	return "No elements in Span";
}

const char*	Span::NoElementsLeftException::what() const throw()
{
	return "Elements size reached";
}
