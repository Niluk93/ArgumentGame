#include "deck.h"
#include "card.h"
#include "grid_state.h"
#include "core/bind/core_bind.h"
#include "core/io/resource_loader.h"

Deck::Deck()
{
}

void Deck::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("loadAllCards", "path"), &Deck::loadAllCards);
	ClassDB::bind_method(D_METHOD("getAllCards"), &Deck::getAllCards);
}

void Deck::loadAllCards(const String& path)
{
	AllCards.clear();

	Ref<_Directory> Directory;
	Directory.instance();
	if (Directory->open(path) == Error::OK)
	{
		Directory->list_dir_begin();
		String FileName = Directory->get_next();
		while (FileName != "")
		{
			if (!Directory->current_is_dir())
			{
				AllCards.push_back(ResourceLoader::load(path + FileName));
			}
			FileName = Directory->get_next();
		}
	}
}

Array Deck::getAllCards()
{
	Array CardArray;
	for (int CardIndex = 0; CardIndex < AllCards.size(); ++CardIndex)
	{
		CardArray.push_back(AllCards[CardIndex]);
	}

	return CardArray;
}
