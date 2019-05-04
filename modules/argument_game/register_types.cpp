#include "register_types.h"

#include "core/class_db.h"
#include "game_grid.h"

void register_argument_game_types()
{
	ClassDB::register_class<GameGrid>();
}

void unregister_argument_game_types()
{

}
