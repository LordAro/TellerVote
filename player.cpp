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

void Player::RemoveCard(Card card)
{
	this->poss_cards.erase(std::remove(this->poss_cards.begin(), this->poss_cards.end(), card), this->poss_cards.end());
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
	os << "Player " << p.position << (p.is_self ? " (self), " : ", ");
	os << "Known hand: " << p.hand << ", ";
	os << "Poss cards: " << p.poss_cards;
	return os;
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
std::vector<std::string> GetCommand()
{
	std::string cmdstr;
	std::getline(std::cin, cmdstr);
	Debug() << cmdstr;
	return split(cmdstr, ' ');
}

void RemoveCardAllPlayers(std::string cardstr)
{
	Card card = StringToCard(cardstr);
	assert(card != Card_Length);
	for (auto player : _players) {
		player.RemoveCard(card);
	}
}
