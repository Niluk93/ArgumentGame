#include "grid_state.h"
#include "game_grid.h"

GridState::GridState()
{
}

void GridState::_notification(int p_notification)
{

}

void GridState::set_GridRef(Variant grid)
{
	Grid = grid.duplicate();
	const Vector2 gridDimensions = Grid.call("get_gridSize");
	const int gridSize = gridDimensions.width * gridDimensions.height;

	// If grids are already the same size and compatible, no need to reset the state? Or maybe make it optional?
	if (gridSize != NodeStates.size())
	{
		NodeStates.resize(gridSize);
		for (int i = 0; i < gridSize; ++i)
		{
			NodeStates.set(i, GridTextures::First);
		}
	}

	Grid.call("_update_dirty");
}

void GridState::set_NodeTemporaryState(int index, GridTextures state)
{
	if (Grid && index >= 0 && index < NodeStates.size())
	{
		Grid.call("set_nodeTexture", index, state, true);
	}
}

void GridState::set_NodeState(int index, GridTextures state)
{
	if (Grid && index >= 0 && index < NodeStates.size())
	{
		NodeStates.set(index, state);
		Grid.call("set_nodeTexture", index, state, true);
	}
}

GridTextures GridState::get_NodeState(int index) const
{
	if (index >= 0 && index < NodeStates.size())
		return static_cast<GridTextures>(NodeStates.get(index));

	return GridTextures::First; // should probably add an invalid state sprite to make debugging this case easier
}

void GridState::resetGrid()
{
	for (int i = 0; i < NodeStates.size(); ++i)
	{
		NodeStates.set(i, GridTextures::First);
		Grid.call("set_nodeTexture", i, GridTextures::First, false);
	}

	Grid.call("_update_mesh");
}

void GridState::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_NodeState", "index", "state"), &GridState::set_NodeState);
	ClassDB::bind_method(D_METHOD("set_NodeTemporaryState", "index", "state"), &GridState::set_NodeTemporaryState);
	ClassDB::bind_method(D_METHOD("get_NodeState", "index"), &GridState::get_NodeState);
	ClassDB::bind_method(D_METHOD("resetGrid"), &GridState::resetGrid);
	ClassDB::bind_method(D_METHOD("set_NodeStates", "gridController"), &GridState::set_NodeStates);
	ClassDB::bind_method(D_METHOD("get_NodeStates"), &GridState::get_NodeStates);

	ADD_GROUP("GridState", "");
	ADD_PROPERTY(PropertyInfo(Variant::POOL_INT_ARRAY, "Node States"), "set_NodeStates", "get_NodeStates");
}
