#ifndef TELLERVOTE_H
#define TELLERVOTE_H

#include <sstream>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
	if (v.size() == 0) return os;
	os << v[0];
	for (uint i = 1; i < v.size(); i++)
		os << " " << v[i];
	return os;
}

#endif /* TELLERVOTE_H */
