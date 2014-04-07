#include <cassert>
#include <iostream>

#include "card.h"
#include "command.h"
#include "debug.h"
#include "player.h"
#include "tellervote.h"

std::vector<Player> _players;

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
	switch (StringToCommandType(cmd[0])) {
		case CommandType_Reveal:
			assert(cmd.size() == 3);
			break;
		case CommandType_Out:
			assert(cmd.size() >= 2 && cmd.size() <= 4);
			if (std::stoi(cmd[1]) == self_id) {
				Debug() << "Oh noes, we lost!";
				exit(0);
			}
			for (uint i = 2; i < cmd.size(); i++) {
				// Remove cards from players possibilities
			}
			break;
		case CommandType_Player:
			assert(cmd.size() == 2);
			if (std::stoi(cmd[1]) != self_id) break;

			MakeMove(self_id);
			break;
		case CommandType_Played:
			assert(cmd.size() >= 2 && cmd.size() <= 5);
			// Remove played card (cmd[2]) from possibilities
			break;
		case CommandType_Protected:
			assert(cmd.size() == 2);
			Debug() << "Dammit, didn't realise player " << cmd[1] << " was protected";
			break;
		case CommandType_Swap:
			assert(cmd.size() == 2);
			break;
		case CommandType_Discard:
			assert(cmd.size() == 3);
			break;
		case CommandType_Ident:
		case CommandType_Begin:
		case CommandType_Draw:
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
