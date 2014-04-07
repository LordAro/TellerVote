#include <algorithm>

#include "command.h"

Command StringToCommand(const std::string &str)
{
	auto found = std::find(COMMAND_MAP.begin(), COMMAND_MAP.end(), str);
	if (found == COMMAND_MAP.end()) return Command_Length;
	int dist = found - COMMAND_MAP.begin();
	return static_cast<Command>(dist);
}

std::string CommandToString(const Command cmd)
{
	if(cmd < Command_Length) {
		return COMMAND_MAP[cmd];
	} else {
		return nullptr;
	}
}

