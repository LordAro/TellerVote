#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "tellervote.h"

class Player {
public:
	Player(int pos, bool self);
	void RemoveCard(Card card);

	bool is_self;
	int position;

	std::vector<Card> played_cards;
	std::vector<Card> poss_cards; ///< Possible cards the player could have (Empty for self).
	std::vector<Card> hand;
};

std::ostream &operator<<(std::ostream &os, const Player &p);

#endif /* PLAYER_H */
