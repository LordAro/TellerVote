#ifndef TELLERVOTE_H
#define TELLERVOTE_H

#include <map>
#include <string>
#include <vector>

enum Card {
	Soldier   = 1,
	Clown     = 2,
	Knight    = 3,
	Priestess = 4,
	Wizard    = 5,
	General   = 6,
	Minister  = 7,
	Princess  = 8
};

static const std::vector<Card> ALL_CARDS = {
	Soldier,   Soldier, Soldier, Soldier, Soldier,
	Clown,     Clown,
	Knight,    Knight,
	Priestess, Priestess,
	Wizard,    Wizard,
	General,
	Minister,
	Princess
};

static const std::map<std::string, Card> STR2CARDS = {
	{"Soldier",   Soldier},
	{"Clown",     Clown},
	{"Knight",    Knight},
	{"Priestess", Priestess},
	{"Wizard",    Wizard},
	{"General",   General},
	{"Minister",  Minister},
	{"Princess",  Princess}
};

static const std::map<Card, std::string> CARDS2STR = {
	{Soldier,   "Soldier"},
	{Clown,     "Clown"},
	{Knight,    "Knight"},
	{Priestess, "Priestess"},
	{Wizard,    "Wizard"},
	{General,   "General"},
	{Minister,  "Minister"},
	{Princess,  "Princess"}
};

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
