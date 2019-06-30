#include "argument_game_grid_controller.h"
#include "grid_sprite_textures.h"

void ArgumentGameGridController::_bind_methods()
{
}

void ArgumentGameGridController::process_tileHoverImpl(int oldTileIndex, int newTileIndex)
{
	Variant gridStateVariant = GridStateRef.get_ref();
	if (gridStateVariant.is_ref())
	{
		gridStateVariant.call("set_NodeTemporaryState", newTileIndex, GridTextures::Highlighted);
		gridStateVariant.call("set_NodeTemporaryState", oldTileIndex, gridStateVariant.call("get_NodeState", oldTileIndex));
	}
}

void ArgumentGameGridController::process_tileSelectedImpl(int tileIndex)
{
	static GridTextures textureToAdd = GridTextures::Turn1TeamA;
	textureToAdd = (textureToAdd != GridTextures::Last) ? static_cast<GridTextures>(textureToAdd + 1) : GridTextures::Turn1TeamA;

	Variant gridStateVariant = GridStateRef.get_ref();
	if (gridStateVariant.is_ref())
	{
		gridStateVariant.call("set_NodeState", tileIndex, textureToAdd);
	}
}

void ArgumentGameGridController::process_gridStateChangedImpl(bool bNext)
{
}
