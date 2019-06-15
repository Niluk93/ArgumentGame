#include "register_types.h"

#include "core/class_db.h"

#include "argument_main_loop.h"
#include "game_grid.h"
#include "grid_sprite_settings.h"
#include "game_input_handler.h"

void register_argument_game_types()
{
	ClassDB::register_class<ArgumentMainLoop>();
	ClassDB::register_class<GameInputHandler>();
	ClassDB::register_class<GameGrid>();
	ClassDB::register_class<GridSpriteSettings>();
}

void unregister_argument_game_types()
{

}
