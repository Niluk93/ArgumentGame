#pragma once
#include "core/Resource.h"

class Card;

class Deck : public Resource
{
	GDCLASS(Deck, Resource);

public:
	Deck();
	static void _bind_methods();

	void loadAllCards(const String& path);
	Array getAllCards();

private:
	Vector<Ref<Card>> AllCards;
};
