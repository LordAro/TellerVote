#ifndef CARD_H
#define CARD_H

#include <array>
#include <string>
#include <vector>

enum Card {
	Card_Soldier,
	Card_Clown,
	Card_Knight,
	Card_Priestess,
	Card_Wizard,
	Card_General,
	Card_Minister,
	Card_Princess,
	Card_Length
};

static const std::array<std::string, Card_Length> CARD_MAP = {{
	"Soldier",
	"Clown",
	"Knight",
	"Priestess",
	"Wizard",
	"General",
	"Minister",
	"Princess"
}};
static_assert(CARD_MAP.size() == Card_Length, "CARD_MAP.size() == Card_Length");

static const std::vector<Card> ALL_CARDS = {
	Card_Soldier,   Card_Soldier, Card_Soldier, Card_Soldier, Card_Soldier,
	Card_Clown,     Card_Clown,
	Card_Knight,    Card_Knight,
	Card_Priestess, Card_Priestess,
	Card_Wizard,    Card_Wizard,
	Card_General,
	Card_Minister,
	Card_Princess
};

Card StringToCard(const std::string &str);
std::string CardToString(const Card card);
void DrawCard(int self_id);

#endif /* CARD_H */
