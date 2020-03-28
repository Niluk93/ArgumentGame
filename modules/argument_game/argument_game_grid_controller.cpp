#include "argument_game_grid_controller.h"
#include "grid_sprite_textures.h"
#include "grid_state.h"
#include "deck.h"

void ArgumentGameGridController::_bind_methods()
{
}


void ArgumentGameGridController::init(Variant owner)
{
	GridControllerBase::init(owner);

	SelectedDeck.instance();
	SelectedDeck->loadAllCards(L"res://Assets/CardPrefabs/Art/");
}

void ArgumentGameGridController::process_tileHoverImpl(int oldTileIndex, int newTileIndex)
{
	if (GridStateRef.is_valid())
	{
		GridStateRef->set_NodeTemporaryState(newTileIndex, GridTextures::Highlighted);
		GridStateRef->set_NodeTemporaryState(oldTileIndex, GridStateRef->get_NodeState(oldTileIndex));
	}
}

void ArgumentGameGridController::process_tileSelectedImpl(int tileIndex)
{
	static GridTextures textureToAdd = GridTextures::Turn1TeamA;
	textureToAdd = (textureToAdd != GridTextures::Last) ? static_cast<GridTextures>(textureToAdd + 1) : GridTextures::Turn1TeamA;

	if (GridStateRef.is_valid())
	{
		GridStateRef->set_NodeState(tileIndex, textureToAdd);
	}
}

void ArgumentGameGridController::process_gridStateChangedImpl(bool bNext)
{
}
