#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "tellervote.h"

class Player {
public:
	Player(int pos, bool self);
	Player(const Player &rhs) = delete; // No sneaky copying!
	Player(Player &&) = default;
	void RemoveCard(Card card);
	void RemoveHandCard(Card card);

	bool is_self;
	int position;

	std::vector<Card> played_cards;
	std::vector<Card> poss_cards; ///< Possible cards the player could have (Empty for self).
	std::vector<Card> hand;
};

std::ostream &operator<<(std::ostream &os, const Player &p);

void RemoveCardAllPlayers(Card cardstr);

extern std::vector<Player> _players;

#endif /* PLAYER_H */
