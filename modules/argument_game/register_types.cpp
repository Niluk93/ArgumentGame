#include "register_types.h"

#include "core/class_db.h"
#include "editor_plugin.h"

#include "version_tracker.h"
#include "argument_main_loop.h"
#include "game_grid.h"
#include "grid_sprite_settings.h"
#include "game_input_handler.h"
#include "grid_state.h"
#include "grid_controller_base.h"
#include "argument_game_grid_controller.h"
#include "card_editor_grid_controller.h"

void register_argument_game_types()
{
	ClassDB::register_class<VersionTracker>();
	ClassDB::register_class<ArgumentMainLoop>();
	ClassDB::register_class<GameInputHandler>();
	ClassDB::register_class<GameGrid>();
	ClassDB::register_class<GridSpriteSettings>();
	ClassDB::register_class<GridState>();
	ClassDB::register_class<GridControllerBase>();
	ClassDB::register_class<ArgumentGameGridController>();
	ClassDB::register_class<CardEditorGridController>();

#ifdef TOOLS_ENABLED
	EditorPlugins::add_by_type<VersionTrackerPlugin>();
#endif
}

void unregister_argument_game_types()
{

}
