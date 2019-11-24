#pragma once
#include "core/resource.h"
#include "grid_sprite_textures.h"

class GridState;

class GridControllerBase : public Resource
{
	GDCLASS(GridControllerBase, Resource);

public:
	GridControllerBase();

	static void _bind_methods();

	virtual void init(Variant owner);

	void process_tileHover(int oldTileIndex, int newTileIndex)				{ if(bAcceptingInput) process_tileHoverImpl(oldTileIndex, newTileIndex); }
	void process_tileSelected(int tileIndex)								{ if(bAcceptingInput) process_tileSelectedImpl(tileIndex); }
	void process_gridStateChanged(bool bNext)								{ if(bAcceptingInput) process_gridStateChangedImpl(bNext); }

	void toggleAcceptingInput(bool toggleTo);

	GridTextures get_GridStateAtNode(int nodeIndex);

protected:
	virtual void process_tileHoverImpl(int oldTileIndex, int newTileIndex);
	virtual void process_tileSelectedImpl(int tileIndex);
	virtual void process_gridStateChangedImpl(bool bNext);

protected:
	Ref<GridState> GridStateRef;
	Variant OwningGrid;

	bool bAcceptingInput;
};
