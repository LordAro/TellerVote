#ifndef COMMAND_H
#define COMMAND_H

#include <array>
#include <string>

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

Command StringToCommand(const std::string &str);
std::string CommandToString(const Command cmd);

#endif /* COMMAND_H */
