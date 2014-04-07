#ifndef TELLERVOTE_H
#define TELLERVOTE_H

#include <array>
#include <sstream>
#include <vector>

enum Command {
	Command_Ident,
	Command_Begin,
	Command_Player,
	Command_Draw,
	Command_Swap,
	Command_Played,
	Command_Reveal,
	Command_Discard,
	Command_Out,
	Command_Protected,

	Command_Play,
	Command_Forfeit,

	Command_Length
};

static const std::array<std::string, Command_Length> COMMAND_MAP = {{
	"ident",
	"begin",
	"player",
	"draw",
	"swap",
	"played",
	"reveal",
	"discard",
	"out",
	"protected",

	"play",
	"forfeit"
}};
static_assert(COMMAND_MAP.size() == Command_Length, "COMMAND_MAP.size() == Command_Length");

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
