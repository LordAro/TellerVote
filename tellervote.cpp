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

	_players[self_id].RemoveHandCard(card);
	// Handle changes to hand in the played cmd
}

void CommandLoop(int self_id)
{
	Command cmd = GetCommand();

	/* No switch for strings :( */
	switch (cmd.type) {
		case CommandType_Reveal:
			assert(cmd.params.size() == 2);
			break;
		case CommandType_Out:
			assert(cmd.params.size() >= 1 && cmd.params.size() <= 3);
			if (std::stoi(cmd.params[0]) == self_id) {
				Debug() << "Oh noes, we lost!";
				exit(0);
			}
			for (uint i = 1; i < cmd.params.size(); i++) {
				RemoveCardAllPlayers(StringToCard(cmd.params[i]));
			}
			break;
		case CommandType_Player:
			assert(cmd.params.size() == 1);
			if (std::stoi(cmd.params[0]) != self_id) break;

			MakeMove(self_id);
			break;
		case CommandType_Played:
			assert(cmd.params.size() >= 1 && cmd.params.size() <= 4);
			// Remove played card (cmd.params[1]) from possibilities
			break;
		case CommandType_Protected:
			assert(cmd.params.size() == 1);
			Debug() << "Dammit, didn't realise player " << cmd.params[0] << " was protected";
			break;
		case CommandType_Swap:
			assert(cmd.params.size() == 1);
			break;
		case CommandType_Discard:
			assert(cmd.params.size() == 2);
			break;
		/* These commands shouldn't happen here. */
		case CommandType_Ident:
		case CommandType_Players:
		case CommandType_Start:
		case CommandType_Draw:
		default:
			Debug() << "D: Unrecognised command! \"" << cmd.type << "\"";
			exit(1);
	}
}

int main()
{
	Command cmd = GetCommand();
	assert(cmd.type == CommandType_Ident && cmd.params.size() == 1);
	int self_id      = std::stoi(cmd.params[0]);
	std::cout << "TellerVote" << std::endl;
	std::cout.flush();

	cmd = GetCommand();
	assert(cmd.type == CommandType_Players && cmd.params.size() == 1);
	int num_players  = std::stoi(cmd.params[0]);
	for (int i = 0; i < num_players; i++) {
		_players.emplace_back(i, i == self_id);
	}

	/* Firt turn player id unused */
	cmd = GetCommand();
	assert(cmd.type == CommandType_Start && cmd.params.size() == 1);

	/* Draw first card */
	DrawCard(self_id);

	for (;;) CommandLoop(self_id);
}
