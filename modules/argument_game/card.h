#pragma once
#include "core/resource.h"
#include "scene/resources/texture.h"
#include "card_types.h"

class GridState;
class ImageTexture;

class Card : public Resource
{
	GDCLASS(Card, Resource);

public:
	Card();
	static void _bind_methods();

	void set_GridState(const Ref<GridState>& gridState);
	Ref<GridState> get_GridState() const					{ return GridStateRef; }

	void set_Texture(const Ref<Texture>& texture);
	Ref<ImageTexture> get_Texture() const					{ return TextureRef; }

	void set_Name(const String& name)						{ Name = name; }
	String get_Name() const									{ return Name; }

	void set_Deck(const String& deck)						{ Deck = deck; }
	String get_Deck() const									{ return Deck; }

	void set_CardType(ECardType cardType)					{ CardType = cardType; }
	ECardType get_CardType() const							{ return CardType; }

	void resolveNameAndDeckFromPath(const String& path);
	String get_DescriptionBBCode() const;

private:
	Ref<GridState> GridStateRef;
	Ref<ImageTexture> TextureRef;
	String Name;
	String Deck;
	ECardType CardType;
};
