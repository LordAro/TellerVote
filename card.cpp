#include <cassert>
#include <algorithm>

#include "card.h"
#include "player.h"

Card StringToCard(const std::string &str)
{
	auto found = std::find(CARD_MAP.begin(), CARD_MAP.end(), str);
	if (found == CARD_MAP.end()) return Card_Length;
	int dist = found - CARD_MAP.begin();
	return static_cast<Card>(dist);
}

std::string CardToString(const Card card)
{
	if(card < Card_Length) {
		return CARD_MAP[card];
	} else {
		return nullptr;
	}
}

void DrawCard(int self_id)
{
	std::vector<std::string> cmd = GetCommand();
	assert(cmd[0] == "draw" && cmd.size() == 2);
	Card c = StringToCard(cmd[1]);
	assert(c != Card_Length);
	_players[self_id].hand.push_back(c);
	RemoveCardAllPlayers(cmd[1]);
}
