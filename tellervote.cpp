#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>

#include "debug.h"
#include "player.h"
#include "tellervote.h"

std::vector<Player> _players;

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
std::vector<std::string> GetCommand()
{
	std::string cmdstr;
	std::getline(std::cin, cmdstr);
	Debug() << cmdstr;
	return split(cmdstr, ' ');
}

void RemoveCardAllPlayers(std::string cardstr)
{
	auto c = STR2CARDS.find(cardstr);
	assert(c != STR2CARDS.end());
	Card card = c->second;
	for (auto player : _players) {
		player.RemoveCard(card);
	}
}

void DrawCard(int self_id)
{
	std::vector<std::string> cmd = GetCommand();
	assert(cmd[0] == "draw" && cmd.size() == 2);
	_players[self_id].hand.push_back(STR2CARDS.find(cmd[1])->second);
	RemoveCardAllPlayers(cmd[1]);
}

void MakeMove(int self_id)
{
	Debug() << "Oop, it's our go";
	DrawCard(self_id);
	// It's our go, play a card
	Card card;
	for (auto c : _players[self_id].hand) {
		if (c == Princess) continue;
		card = c;
		break;
	}
	std::cout << "play " << CARDS2STR.find(card)->second << std::endl;
	std::cout.flush();

	_players[self_id].RemoveCard(card);
	// Handle changes to hand in the played cmd
}

int main()
{
	srand(time(0));
	std::vector<std::string> cmd = GetCommand();
	assert(cmd[0] == "ident" && cmd.size() == 4);
	int self_id      = std::stoi(cmd[1]);
	int num_players  = std::stoi(cmd[2]);
	int first_player = std::stoi(cmd[3]);
	for (int i = 0; i < num_players; i++) {
		_players.emplace_back(i, i == self_id);
	}
	std::cout << "TellerVote" << std::endl;
	std::cout.flush();

	DrawCard(self_id);
	cmd = GetCommand();
	assert(cmd[0] == "begin");

	for (;;) {
		std::vector<std::string> cmd = GetCommand();

		/* No switch for strings :( */
		if (cmd[0] == "reveal") {
			assert(cmd.size() == 3);
		} else if (cmd[0] == "out") {
			assert(cmd.size() >= 2 && cmd.size() <= 4);
			if (std::stoi(cmd[1]) == self_id) {
				Debug() << "Oh noes, we lost!";
				exit(0);
			}
			for (uint i = 2; i < cmd.size(); i++) {
				// Remove cards from players possibilities
			}
		} else if (cmd[0] == "player") {
			assert(cmd.size() == 2);
			if (std::stoi(cmd[1]) != self_id) continue;

			MakeMove(self_id);
		} else if (cmd[0] == "played") {
			assert(cmd.size() >= 2 && cmd.size() <= 5);
			// Remove played card (cmd[2]) from possibilities
		} else if (cmd[0] == "protected") {
			assert(cmd.size() == 2);
			Debug() << "Dammit, didn't realise player " << cmd[1] << " was protected";
		} else if (cmd[0] == "swap") {
			assert(cmd.size() == 2);
		} else if (cmd[0] == "discard") {
			assert(cmd.size() == 3);
		} else {
			Debug() << "D: Unrecognised command! \"" << cmd[0] << "\"";
			exit(1);
		}
	}
}
