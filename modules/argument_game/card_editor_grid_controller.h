#pragma once
#include "grid_controller_base.h"
#include "grid_sprite_textures.h"
#include "card_types.h"

struct InputDetails;
class Card;

class CardEditorGridController : public GridControllerBase
{
	GDCLASS(CardEditorGridController, GridControllerBase);

public:
	CardEditorGridController();
	static void _bind_methods();

	void set_Turn(ETurn turn)									{ Turn = turn; }
	ETurn get_Turn() const										{ return Turn; }

	void set_CardType(ECardType cardType);
	ECardType get_CardType() const { return CardType; }

	void set_CardRef(const Ref<Card>& card);
	Ref<Card> get_CardRef() const								{ return CardRef; }

	void saveCard(const String& path);
	void loadCard(const String& path);

protected:
	virtual void init(Variant owner) override;

	virtual void process_tileHoverImpl(int oldTileIndex, int newTileIndex) override;
	virtual void process_tileSelectedImpl(int tileIndex) override;
	virtual void process_gridStateChangedImpl(bool bNext) override;

private:
	bool switchCardTypePrev(const InputDetails& inputDetails);
	bool switchCardTypeNext(const InputDetails& inputDetails);

protected:
	ETurn Turn;
	ECardType CardType;

	Ref<Card> CardRef;
};
