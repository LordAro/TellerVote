#ifndef COMMAND_H
#define COMMAND_H

#include <array>
#include <string>

enum CommandType {
	CommandType_Ident,
	CommandType_Player,
	CommandType_Draw,
	CommandType_Swap,
	CommandType_Played,
	CommandType_Reveal,
	CommandType_Discard,
	CommandType_Out,
	CommandType_Protected,
	CommandType_Players,
	CommandType_Start,

	CommandType_Play,
	CommandType_Forfeit,

	CommandType_Length
};

static const std::array<const char *, CommandType_Length> COMMANDTYPE_MAP = {{
	"ident",
	"player",
	"draw",
	"swap",
	"played",
	"reveal",
	"discard",
	"out",
	"protected",
	"players",
	"start",

	"play",
	"forfeit"
}};
static_assert(COMMANDTYPE_MAP.size() == CommandType_Length, "COMMANDTYPE_MAP.size() == CommandType_Length");

CommandType StringToCommandType(const std::string &str);
std::string CommandTypeToString(const CommandType cmd);

class Command {
public:
	Command(const std::string &cmdstr);

	CommandType type;
	std::vector<std::string> params;
};

Command GetCommand();

#endif /* COMMAND_H */
