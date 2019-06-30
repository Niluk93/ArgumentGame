#include "grid_controller_base.h"
#include "grid_state.h"
#include <stdexcept>

GridControllerBase::GridControllerBase()
	: bAcceptingInput(true)
{
}

void GridControllerBase::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("process_tileHover", "oldTileIndex", "newTileIndex"), &GridControllerBase::process_tileHover);
	ClassDB::bind_method(D_METHOD("process_tileSelected", "tileIndex"), &GridControllerBase::process_tileSelected);
	ClassDB::bind_method(D_METHOD("process_gridStateChanged", "bNext"), &GridControllerBase::process_gridStateChanged);
	ClassDB::bind_method(D_METHOD("toggle_acceptingInput", "bAcceptingInput"), &GridControllerBase::toggleAcceptingInput);
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

void GridControllerBase::set_GridState(const Ref<GridState> &gridState)
{
	GridStateRef.set_ref(gridState);
}
