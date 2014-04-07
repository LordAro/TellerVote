#ifndef COMMAND_H
#define COMMAND_H

#include <array>
#include <string>

enum CommandType {
	CommandType_Ident,
	CommandType_Begin,
	CommandType_Player,
	CommandType_Draw,
	CommandType_Swap,
	CommandType_Played,
	CommandType_Reveal,
	CommandType_Discard,
	CommandType_Out,
	CommandType_Protected,

	CommandType_Play,
	CommandType_Forfeit,

	CommandType_Length
};

static const std::array<std::string, CommandType_Length> COMMANDTYPE_MAP = {{
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
static_assert(COMMANDTYPE_MAP.size() == CommandType_Length, "COMMANDTYPE_MAP.size() == CommandType_Length");

CommandType StringToCommandType(const std::string &str);
std::string CommandTypeToString(const CommandType cmd);

#endif /* COMMAND_H */
