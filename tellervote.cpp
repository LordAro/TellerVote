#include <algorithm>
#include <cassert>
#include <iostream>

#include "card.h"
#include "debug.h"
#include "player.h"
#include "tellervote.h"

std::vector<Player> _players;

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

void MakeMove(int self_id)
{
	Debug() << "Oop, it's our go";
	DrawCard(self_id);
	// It's our go, play a card
	Card card;
	for (auto c : _players[self_id].hand) {
		if (c == Card_Princess) continue;
		card = c;
		break;
	}
	std::cout << "play " << CardToString(card) << std::endl;
	std::cout.flush();

	_players[self_id].RemoveCard(card);
	// Handle changes to hand in the played cmd
}

void CommandLoop(int self_id)
{
	std::vector<std::string> cmd = GetCommand();

	/* No switch for strings :( */
	switch (StringToCommand(cmd[0])) {
		case Command_Reveal:
			assert(cmd.size() == 3);
			break;
		case Command_Out:
			assert(cmd.size() >= 2 && cmd.size() <= 4);
			if (std::stoi(cmd[1]) == self_id) {
				Debug() << "Oh noes, we lost!";
				exit(0);
			}
			for (uint i = 2; i < cmd.size(); i++) {
				// Remove cards from players possibilities
			}
			break;
		case Command_Player:
			assert(cmd.size() == 2);
			if (std::stoi(cmd[1]) != self_id) break;

			MakeMove(self_id);
			break;
		case Command_Played:
			assert(cmd.size() >= 2 && cmd.size() <= 5);
			// Remove played card (cmd[2]) from possibilities
			break;
		case Command_Protected:
			assert(cmd.size() == 2);
			Debug() << "Dammit, didn't realise player " << cmd[1] << " was protected";
			break;
		case Command_Swap:
			assert(cmd.size() == 2);
			break;
		case Command_Discard:
			assert(cmd.size() == 3);
			break;
		case Command_Ident:
		case Command_Begin:
		case Command_Draw:
		default:
			Debug() << "D: Unrecognised command! \"" << cmd[0] << "\"";
			exit(1);
	}
}

int main()
{
	std::vector<std::string> cmd = GetCommand();
	assert(cmd[0] == "ident" && cmd.size() == 4);
	int self_id      = std::stoi(cmd[1]);
	/* First player turn unused */
	int num_players  = std::stoi(cmd[3]);
	for (int i = 0; i < num_players; i++) {
		_players.emplace_back(i, i == self_id);
	}
	std::cout << "TellerVote" << std::endl;
	std::cout.flush();

	DrawCard(self_id);
	cmd = GetCommand();
	assert(cmd[0] == "begin");

	for (;;) CommandLoop(self_id);
}
