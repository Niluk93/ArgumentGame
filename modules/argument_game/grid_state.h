#pragma once
#include "core/resource.h"

enum GridTextures;
class GameGrid;

class GridState : public Resource
{
	GDCLASS(GridState, Resource);

public:
	GridState();

	void _notification(int p_notification);
	void set_GridRef(GameGrid* grid);
	void set_NodeTemporaryState(int index, GridTextures state);
	void set_NodeState(int index, GridTextures state);
	GridTextures get_NodeState(int index) const;
	void resetGrid();

	//void set_NodeTemporaryState_bind(int index, int state)		{ set_NodeTemporaryState(index, static_cast<GridTextures>(state)); }
	//void set_NodeState_bind(int index, int state)				{ set_NodeState(index, static_cast<GridTextures>(state)); }
	//int get_NodeState_bind(int index)							{ return get_NodeState(index); }

	static void _bind_methods();
private:
	GameGrid* Grid;
	Vector<GridTextures> NodeStates;
};
