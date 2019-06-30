#include "card_editor_grid_controller.h"
#include "game_input_handler.h"
#include <stdexcept>

CardEditorGridController::CardEditorGridController()
	: GridControllerBase()
	, Turn(TURN_ONE)
	, CardType(CARD_ARGUMENT)
{
	BIND_INPUT_CALLBACK("card_editor_card_type_prev", this, &CardEditorGridController::switchCardTypePrev);
	BIND_INPUT_CALLBACK("card_editor_card_type_next", this, &CardEditorGridController::switchCardTypeNext);
}

void CardEditorGridController::_bind_methods()
{
	BIND_ENUM_CONSTANT(TURN_ONE);
	BIND_ENUM_CONSTANT(TURN_TWO);
	BIND_ENUM_CONSTANT(TURN_THREE);
	BIND_ENUM_CONSTANT(TURN_FOUR);

	BIND_ENUM_CONSTANT(CARD_ARGUMENT);
	BIND_ENUM_CONSTANT(CARD_COUNTER_ARGUMENT);
	BIND_ENUM_CONSTANT(CARD_SPECIAL);

	ClassDB::bind_method(D_METHOD("set_Turn", "Turn"), &CardEditorGridController::set_Turn);
	ClassDB::bind_method(D_METHOD("get_Turn"), &CardEditorGridController::get_Turn);
	ClassDB::bind_method(D_METHOD("set_CardType", "CardType"), &CardEditorGridController::set_CardType);
	ClassDB::bind_method(D_METHOD("get_CardType"), &CardEditorGridController::get_CardType);
	ClassDB::bind_method(D_METHOD("saveCard"), &CardEditorGridController::saveCard);

	ADD_GROUP("Card", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Turn", PROPERTY_HINT_ENUM, "Turn 1,Turn 2,Turn 3,Turn 4"), "set_Turn", "get_Turn");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "CardType", PROPERTY_HINT_ENUM, "Argument,Counter Argument,Special"), "set_CardType", "get_CardType");
}

void CardEditorGridController::process_tileHoverImpl(int oldTileIndex, int newTileIndex)
{
	Variant gridStateVariant = GridStateRef.get_ref();
	if (gridStateVariant.is_ref())
	{
		gridStateVariant.call("set_NodeTemporaryState", newTileIndex, GridTextures::Highlighted);
		gridStateVariant.call("set_NodeTemporaryState", oldTileIndex, gridStateVariant.call("get_NodeState", oldTileIndex));
	}
}

void CardEditorGridController::process_tileSelectedImpl(int tileIndex)
{
	if (CardType == ECardType::CARD_SPECIAL)
	{
		throw std::logic_error("Special cards should not define grid setups");
		return;
	}

	Variant gridStateVariant = GridStateRef.get_ref();
	if (gridStateVariant.is_ref())
	{
		int nodeState = gridStateVariant.call("get_NodeState", tileIndex);

		// TODO - Do this better? Super dependent on the sprite sheet asset
		int targetState = ((Turn + 1) * 4) + CardType;
		if (nodeState == targetState)
		{
			gridStateVariant.call("set_NodeState", tileIndex, GridTextures::First);
		}
		else
		{
			gridStateVariant.call("set_NodeState", tileIndex, targetState);
		}
	}
}

void CardEditorGridController::process_gridStateChangedImpl(bool bNext)
{
	int turn	=	bNext ?
					(Turn + 1 == ETurn::INVALID_TURN_END) ? ETurn::INVALID_TURN_START + 1 : Turn + 1
				:	(Turn - 1 == ETurn::INVALID_TURN_START) ? ETurn::INVALID_TURN_END - 1 : Turn - 1;

	set_Turn(static_cast<ETurn>(turn));
}

bool CardEditorGridController::switchCardTypePrev(const InputDetails &inputDetails)
{
	if (bAcceptingInput && !(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
	{
		int cardType = (CardType - 1 == ECardType::INVALID_CARD_START) ? ECardType::INVALID_CARD_END - 1 : CardType - 1;
		set_CardType(static_cast<ECardType>(cardType));

		Variant gridStateVariant = GridStateRef.get_ref();
		if (gridStateVariant.is_ref())
		{
			gridStateVariant.call("resetGrid");
		}

		return true;
	}

	return false;
}

bool CardEditorGridController::switchCardTypeNext(const InputDetails &inputDetails)
{
	if (bAcceptingInput && !(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
	{
		int cardType = (CardType + 1 == ECardType::INVALID_CARD_END) ? ECardType::INVALID_CARD_START + 1 : CardType + 1;
		set_CardType(static_cast<ECardType>(cardType));

		Variant gridStateVariant = GridStateRef.get_ref();
		if (gridStateVariant.is_ref())
		{
			gridStateVariant.call("resetGrid");
		}

		return true;
	}

	return false;
}

void CardEditorGridController::saveCard()
{
	//if (!(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
	{
		print_line("Please don't even");
	}
}
