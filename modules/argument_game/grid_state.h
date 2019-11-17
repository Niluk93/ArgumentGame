#pragma once
#include "core/resource.h"

enum GridTextures;

class GridState : public Resource
{
	GDCLASS(GridState, Resource);

public:
	GridState();

	void _notification(int p_notification);
	void set_GridRef(Variant grid);
	void set_NodeTemporaryState(int index, GridTextures state);
	void set_NodeState(int index, GridTextures state);
	GridTextures get_NodeState(int index) const;
	void resetGrid();

	void set_NodeStates(const PoolIntArray& States)		{ NodeStates = States; }
	PoolIntArray get_NodeStates() const					{ return NodeStates; }

	static void _bind_methods();
private:
	Variant Grid;
	PoolIntArray NodeStates;
};
