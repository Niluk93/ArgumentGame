#pragma once
#include "grid_controller_base.h"

class Deck;

class ArgumentGameGridController : public GridControllerBase
{
	GDCLASS(ArgumentGameGridController, GridControllerBase);

public:
	static void _bind_methods();

	virtual void init(Variant owner) override;

protected:
	virtual void process_tileHoverImpl(int oldTileIndex, int newTileIndex) override;
	virtual void process_tileSelectedImpl(int tileIndex) override;
	virtual void process_gridStateChangedImpl(bool bNext) override;

private:
	Ref<Deck> SelectedDeck;
};
