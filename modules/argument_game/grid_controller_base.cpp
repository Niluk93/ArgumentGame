#include "grid_controller_base.h"
#include "grid_state.h"
#include "game_grid.h"
#include <stdexcept>

GridControllerBase::GridControllerBase()
	: bAcceptingInput(true)
{
}

void GridControllerBase::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("init", "owner"), &GridControllerBase::init);
	ClassDB::bind_method(D_METHOD("process_tileHover", "oldTileIndex", "newTileIndex"), &GridControllerBase::process_tileHover);
	ClassDB::bind_method(D_METHOD("process_tileSelected", "tileIndex"), &GridControllerBase::process_tileSelected);
	ClassDB::bind_method(D_METHOD("process_gridStateChanged", "bNext"), &GridControllerBase::process_gridStateChanged);
	ClassDB::bind_method(D_METHOD("toggle_acceptingInput", "bAcceptingInput"), &GridControllerBase::toggleAcceptingInput);
}

void GridControllerBase::init(Variant owner)
{
	OwningGrid = owner;

	GridStateRef.instance();
	GridStateRef->set_GridRef(owner);
}

void GridControllerBase::process_tileHoverImpl(int oldTileIndex, int newTileIndex)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GridControllerBase::process_tileSelectedImpl(int tileIndex)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GridControllerBase::process_gridStateChangedImpl(bool bNext)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GridControllerBase::toggleAcceptingInput(bool toggleTo)
{
	GridStateRef->set_GridRef(OwningGrid);
	bAcceptingInput = toggleTo;
}

GridTextures GridControllerBase::get_GridStateAtNode(int nodeIndex)
{
	return GridStateRef->get_NodeState(nodeIndex);
}
