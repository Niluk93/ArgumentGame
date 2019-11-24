#include "card.h"
#include "grid_state.h"
#include "core/image.h"
#include "common/debug.h"

Card::Card()
	: CardType(ECardType::CARD_ARGUMENT)
{
	GridStateRef.instance();
	TextureRef.instance();
}

void Card::_bind_methods()
{
	BIND_ENUM_CONSTANT(CARD_ARGUMENT);
	BIND_ENUM_CONSTANT(CARD_COUNTER_ARGUMENT);
	BIND_ENUM_CONSTANT(CARD_SPECIAL);

	ClassDB::bind_method(D_METHOD("set_GridState", "GridState"), &Card::set_GridState);
	ClassDB::bind_method(D_METHOD("get_GridState"), &Card::get_GridState);
	ClassDB::bind_method(D_METHOD("set_Texture", "Texture"), &Card::set_Texture);
	ClassDB::bind_method(D_METHOD("get_Texture"), &Card::get_Texture);
	ClassDB::bind_method(D_METHOD("set_Name", "Name"), &Card::set_Name);
	ClassDB::bind_method(D_METHOD("get_Name"), &Card::get_Name);
	ClassDB::bind_method(D_METHOD("set_Deck", "Deck"), &Card::set_Deck);
	ClassDB::bind_method(D_METHOD("get_Deck"), &Card::get_Deck);
	ClassDB::bind_method(D_METHOD("set_CardType", "CardType"), &Card::set_CardType);
	ClassDB::bind_method(D_METHOD("get_CardType"), &Card::get_CardType);
	ClassDB::bind_method(D_METHOD("resolveNameAndDeckFromPath"), &Card::resolveNameAndDeckFromPath);
	ClassDB::bind_method(D_METHOD("get_DescriptionBBCode"), &Card::get_DescriptionBBCode);

	ADD_GROUP("Card", "");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "Name", PROPERTY_HINT_TYPE_STRING), "set_Name", "get_Name");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "Deck", PROPERTY_HINT_TYPE_STRING), "set_Deck", "get_Deck");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "CardType", PROPERTY_HINT_ENUM, "Argument,Counter Argument,Special"), "set_CardType", "get_CardType");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "GridState", PROPERTY_HINT_RESOURCE_TYPE), "set_GridState", "get_GridState");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Texture", PROPERTY_HINT_RESOURCE_TYPE), "set_Texture", "get_Texture");
}


void Card::set_GridState(const Ref<GridState>& gridState)
{
	GridStateRef = gridState;
}

void Card::set_Texture(const Ref<Texture>& texture)
{
	Ref<Image> image = texture->get_data();
	TextureRef->create_from_image(image);
}


void Card::resolveNameAndDeckFromPath(const String &path)
{
	Vector<String> StringVec = path.split("/");

	// Path name needs at least 2 elements to resolve deck name and card name
	assert(StringVec.size() < 2);

	Deck = StringVec[StringVec.size() - 2];
	int extensionIndex = StringVec[StringVec.size() - 1].find_char('.');
	Name = StringVec[StringVec.size() - 1].substr(0, extensionIndex);

	print_line(Deck);
	print_line(Name);
}

String Card::get_DescriptionBBCode() const
{
	Vector<Variant> vargs = varray();

	vargs.push_back("#ffffff");
	vargs.push_back(Name);
	switch (CardType)
	{
	case ECardType::CARD_ARGUMENT:
		vargs.push_back("#1b9453");
		vargs.push_back("Argument");
		break;
	case ECardType::CARD_COUNTER_ARGUMENT:
		vargs.push_back("#a84c32");
		vargs.push_back("Counter Argument");
		break;
	case ECardType::CARD_SPECIAL:
		vargs.push_back("#ffffff");
		vargs.push_back("Special");
		break;
	default:
		// invalid card type
		assert(false);
		vargs.push_back("#ff0000");
		vargs.push_back("Invalid");
	}

	vargs.push_back("#a969b3");
	vargs.push_back(Deck);
	return String("[center][color={0}]{1}[/color]\n[color={2}]{3}[/color]\n[color={4}]{5}[/color][/center]").format(vargs);
}
