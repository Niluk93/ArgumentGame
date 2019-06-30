#pragma once
#include "grid_controller_base.h"
#include "grid_sprite_textures.h"

struct InputDetails;

class CardEditorGridController : public GridControllerBase
{
	GDCLASS(CardEditorGridController, GridControllerBase);

public:
	enum ETurn
	{
		INVALID_TURN_START = -1,
		TURN_ONE,
		TURN_TWO,
		TURN_THREE,
		TURN_FOUR,
		INVALID_TURN_END
	};

	enum ECardType
	{
		INVALID_CARD_START = -1,
		CARD_ARGUMENT,
		CARD_COUNTER_ARGUMENT,
		CARD_SPECIAL,
		INVALID_CARD_END
	};

public:
	CardEditorGridController();
	static void _bind_methods();

	void set_Turn(ETurn turn)									{ Turn = turn; }
	ETurn get_Turn() const										{ return Turn; }

	void set_CardType(ECardType cardType)						{ CardType = cardType; }
	ECardType get_CardType() const { return CardType; }

	void saveCard();

protected:
	virtual void process_tileHoverImpl(int oldTileIndex, int newTileIndex) override;
	virtual void process_tileSelectedImpl(int tileIndex) override;
	virtual void process_gridStateChangedImpl(bool bNext) override;

private:
	bool switchCardTypePrev(const InputDetails& inputDetails);
	bool switchCardTypeNext(const InputDetails& inputDetails);

protected:
	ETurn Turn;
	ECardType CardType;
};

VARIANT_ENUM_CAST(CardEditorGridController::ETurn);
VARIANT_ENUM_CAST(CardEditorGridController::ECardType);
