#include "grid_state.h"
#include "game_grid.h"

GridState::GridState()
	: Grid(nullptr)
{
}

void GridState::_notification(int p_notification)
{

}

void GridState::set_GridRef(GameGrid* grid)
{
	Grid = grid;
	NodeStates.clear();

	int gridSize = grid->get_gridSize().width * grid->get_gridSize().height;
	NodeStates.resize(gridSize);
	for (int i = 0; i < gridSize; ++i)
	{
		NodeStates.set(i, GridTextures::First);
	}
}

void GridState::set_NodeTemporaryState(int index, GridTextures state)
{
	if (Grid && index >= 0 && index < NodeStates.size())
	{
		Grid->set_nodeTexture(index, state);
	}
}

void GridState::set_NodeState(int index, GridTextures state)
{
	if (Grid && index >= 0 && index < NodeStates.size())
	{
		NodeStates.set(index, state);
		Grid->set_nodeTexture(index, state);
	}
}

GridTextures GridState::get_NodeState(int index) const
{
	if (index >= 0 && index < NodeStates.size())
		return NodeStates.get(index);

	return GridTextures::First; // should probably add an invalid state sprite to make debugging this case easier
}

void GridState::resetGrid()
{
	for (int i = 0; i < NodeStates.size(); ++i)
	{
		NodeStates.set(i, GridTextures::First);
		Grid->set_nodeTexture(i, GridTextures::First, false);
	}

	Grid->call("_update_mesh");
}

void GridState::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_NodeState", "index", "state"), &GridState::set_NodeState);
	ClassDB::bind_method(D_METHOD("set_NodeTemporaryState", "index", "state"), &GridState::set_NodeTemporaryState);
	ClassDB::bind_method(D_METHOD("get_NodeState", "index"), &GridState::get_NodeState);
	ClassDB::bind_method(D_METHOD("resetGrid"), &GridState::resetGrid);
}
