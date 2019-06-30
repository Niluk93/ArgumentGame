#pragma once
#include "core/resource.h"

class GridState;

class GridControllerBase : public Resource
{
	GDCLASS(GridControllerBase, Resource);

public:
	GridControllerBase();

	static void _bind_methods();

	void process_tileHover(int oldTileIndex, int newTileIndex)				{ if(bAcceptingInput) process_tileHoverImpl(oldTileIndex, newTileIndex); }
	void process_tileSelected(int tileIndex)								{ if(bAcceptingInput) process_tileSelectedImpl(tileIndex); }
	void process_gridStateChanged(bool bNext)								{ if(bAcceptingInput) process_gridStateChangedImpl(bNext); }

	void toggleAcceptingInput(bool toggleTo)								{ bAcceptingInput = toggleTo; }

	void set_GridState(const Ref<GridState>& gridState);

protected:
	virtual void process_tileHoverImpl(int oldTileIndex, int newTileIndex);
	virtual void process_tileSelectedImpl(int tileIndex);
	virtual void process_gridStateChangedImpl(bool bNext);

protected:
	// WeakRef so that we can easily swap out entire grid states when turns change and make sure memory is still properly cleared
	// Also, just to understand the workflow, as we can also manually unref normal references for the same result
	WeakRef GridStateRef;

	bool bAcceptingInput;
};
