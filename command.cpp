#include <algorithm>
#include <cassert>
#include <sstream>

#include "command.h"
#include "debug.h"

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

/* split functions stolen from http://stackoverflow.com/a/236803 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	assert(elems.size() > 0); // Command should never be empty.
	return elems;
}

/* Blocking */
Command GetCommand()
{
	std::string cmdstr;
	std::getline(std::cin, cmdstr);
	Debug() << cmdstr;
	return Command(cmdstr);
}

Command::Command(const std::string &cmdstr)
{
	std::vector<std::string> cmdstrs = split(cmdstr, ' ');
	this->type = StringToCommandType(cmdstrs[0]);
	cmdstrs.erase(cmdstrs.begin());
	this->params = cmdstrs;
}
