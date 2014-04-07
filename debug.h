#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <vector>

class Debug {
public:
	Debug()
	{
		std::cout.flush();
		std::cerr << "[TellerVote] ";
	}

	template <class T>
	Debug &operator<<(const T &v)
	{
		std::cerr << v;
		return *this;
	}

	template <class T>
	Debug &operator<<(const std::vector<T> &v)
	{
		if (v.size() == 0) return *this;
		std::cerr << v[0];
		for (uint i = 1; i < v.size(); i++)
			std::cerr << " " << v[i];
		return *this;
	}

	~Debug()
	{
		std::cerr << std::endl;
	}
};

#endif /* DEBUG_H */
