#include <algorithm>

#include "command.h"

CommandType StringToCommandType(const std::string &str)
{
	auto found = std::find(COMMANDTYPE_MAP.begin(), COMMANDTYPE_MAP.end(), str);
	if (found == COMMANDTYPE_MAP.end()) return CommandType_Length;
	int dist = found - COMMANDTYPE_MAP.begin();
	return static_cast<CommandType>(dist);
}

std::string CommandTypeToString(const CommandType cmd)
{
	if(cmd < CommandType_Length) {
		return COMMANDTYPE_MAP[cmd];
	} else {
		return nullptr;
	}
}

