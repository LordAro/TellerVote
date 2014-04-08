#include <algorithm>
#include <cassert>

#include "card.h"
#include "debug.h"
#include "player.h"
#include "tellervote.h"

Player::Player(int pos, bool self)
{
	this->position = pos;
	this->is_self = self;

	/* Init possible cards list */
	if (!this->is_self) {
		this->poss_cards = ALL_CARDS;
	}
}

/* Doesn't remove anything if it's not present (i.e. self) */
void Player::RemoveCard(Card card)
{
	this->poss_cards.erase(std::remove(this->poss_cards.begin(), this->poss_cards.end(), card), this->poss_cards.end());
}

void Player::RemoveHandCard(Card card)
{
	this->hand.erase(std::remove(this->hand.begin(), this->hand.end(), card), this->hand.end());
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
	os << "Player " << p.position << (p.is_self ? " (self), " : ", ");
	os << "Known hand: " << p.hand << ", ";
	os << "Poss cards: " << p.poss_cards;
	return os;
}

void RemoveCardAllPlayers(Card card)
{
	assert(card != Card_Length);
	for (auto &player : _players) {
		player.RemoveCard(card);
	}
}
