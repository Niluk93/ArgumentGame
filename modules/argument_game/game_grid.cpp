#include "game_grid.h"
#include "core/print_string.h"
#include "core/os/input.h"
#include "game_input_handler.h"
#include "scene/scene_string_names.h"
#include "core/engine.h"

GameGrid::GameGrid()
	: Pivot(0, 0)
	, GridSize(1, 1)
{
	using std::placeholders::_1;
	GameInputHandler::InputCallback tileSelect = std::bind(&GameGrid::tileSelected, this, _1);
	GameInputHandler::GetSingletonInstance()->BindInputEvent("argument_tile_select", tileSelect);
}

void GameGrid::draw()
{
	draw_mesh(MeshRef.get_mesh(), get_texture(), get_texture());
}

bool GameGrid::tileSelected(const InputDetails& inputDetails)
{
	int index = positionToTileIndex(Input::get_singleton()->get_mouse_position());
	set_nodeTexture(index, GridTextures::Turn1TeamA);

	return true;
}

bool GameGrid::processMouseMovement(const Ref<InputEventMouseMotion> &mouseMove)
{
	Vector2 currMousePosition = mouseMove->get_position();
	int currIndex = positionToTileIndex(currMousePosition);
	static int lastIndex = 0;

	if (	currIndex != lastIndex
		&&	currIndex >= 0 && currIndex < GridNodes.Textures.size())
	{
		set_nodeTexture(currIndex, GridTextures::Highlighted);
		set_nodeTexture(lastIndex, GridTextures::First);

		lastIndex = currIndex;
	}

	return true;
}

int GameGrid::positionToTileIndex(Point2 position)
{
	int gridElementWidth = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().width : defaultTileSize;
	int gridElementHeight = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().height : defaultTileSize;

	Vector2i gridPosition(position.x / gridElementWidth, position.y / gridElementHeight);
	return (GridSize.width * gridPosition.y) + gridPosition.x;
}

void GameGrid::_notification(int p_what)
{
	
	switch (p_what)
	{
	case NOTIFICATION_PROCESS:
	{
		Variant time = get_process_delta_time();
		const Variant *ptr[1] = { &time };
		call_multilevel(SceneStringNames::get_singleton()->_process, ptr, 1);
	}
	break;
	case NOTIFICATION_READY:
	{
		if (!Engine::get_singleton()->is_editor_hint())
		{
			set_process(true);
			set_process_input(true);
		}
	}
	break;
	case NOTIFICATION_DRAW:
	{
		draw();
	}
	break;
	default:
		break;
	}
}


void GameGrid::_process(float p_time)
{

}


void GameGrid::_input(const Ref<InputEvent> &event)
{
	Ref<InputEventMouseMotion> mm = event;
	if (mm.is_valid())
	{
		processMouseMovement(mm);
	}
}

void GameGrid::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("draw"), &GameGrid::draw);
	ClassDB::bind_method(D_METHOD("set_pivot", "pivot"), &GameGrid::set_pivot);
	ClassDB::bind_method(D_METHOD("get_pivot"), &GameGrid::get_pivot);
	ClassDB::bind_method(D_METHOD("set_gridSize", "gridSize"), &GameGrid::set_gridSize);
	ClassDB::bind_method(D_METHOD("get_gridSize"), &GameGrid::get_gridSize);
	ClassDB::bind_method(D_METHOD("set_spriteSettings", "settings"), &GameGrid::set_spriteSettings);
	ClassDB::bind_method(D_METHOD("get_spriteSettings"), &GameGrid::get_spriteSettings);
	ClassDB::bind_method(D_METHOD("get_texture"), &GameGrid::get_texture);
	ClassDB::bind_method(D_METHOD("_process", "delta"), &GameGrid::_process);
	ClassDB::bind_method(D_METHOD("_input", "event"), &GameGrid::_input);

	ADD_GROUP("Grid", "");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Pivot"), "set_pivot", "get_pivot");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "GridSize"), "set_gridSize", "get_gridSize");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "GridTexture", PROPERTY_HINT_RESOURCE_TYPE, "GridSpriteSettings"), "set_spriteSettings", "get_spriteSettings");
}

void GameGrid::UpdateDirty()
{
	GridNodes.Points.clear();
	GridNodes.Points.resize((GridSize.width * GridSize.height) * 6);

	GridNodes.Colors.clear();
	GridNodes.Colors.resize(((GridSize.width * GridSize.height) * 6));

	GridNodes.Textures.clear();
	GridNodes.Textures.resize(GridSize.width * GridSize.height);
	for (int i = 0; i < GridNodes.Textures.size(); ++i)
	{
		GridNodes.Textures.set(i, GridTextures::First);
	}

	GridNodes.UVs.clear();
	GridNodes.UVs.resize(((GridSize.width * GridSize.height) * 6));

	int gridElementWidth = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().width : defaultTileSize;
	int gridElementHeight = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().height : defaultTileSize;

	for (int i = 0; i < GridSize.width; ++i)
	{
		for (int j = 0; j < GridSize.height; ++j)
		{
			UpdateTile((GridSize.width * j) + i, false);
		}
	}

	GenerateArrayMesh();

	update();
}

void GameGrid::UpdateTile(int index, bool autoGenerateMesh)
{
	int gridElementWidth = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().width : defaultTileSize;
	int gridElementHeight = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().height : defaultTileSize;

	int col = index % GridSize.width;
	int row = index / GridSize.width;

	int pointStartingIndex = index * 6;
	Vector2 gridNodePosition(col * gridElementWidth, row * gridElementHeight);
	GridNodes.Points.set(pointStartingIndex, gridNodePosition);
	GridNodes.Points.set(pointStartingIndex + 1, gridNodePosition + Vector2(gridElementWidth, 0));
	GridNodes.Points.set(pointStartingIndex + 2, gridNodePosition + Vector2(0, gridElementHeight));

	GridNodes.Points.set(pointStartingIndex + 3, gridNodePosition + Vector2(0, gridElementHeight));
	GridNodes.Points.set(pointStartingIndex + 4, gridNodePosition + Vector2(gridElementWidth, 0));
	GridNodes.Points.set(pointStartingIndex + 5, gridNodePosition + Vector2(gridElementWidth, gridElementHeight));

	GridNodes.Colors.set(pointStartingIndex, Color(1.f, 1.f, 1.f));
	GridNodes.Colors.set(pointStartingIndex + 1, Color(1.f, 1.f, 1.f));
	GridNodes.Colors.set(pointStartingIndex + 2, Color(1.f, 1.f, 1.f));

	GridNodes.Colors.set(pointStartingIndex + 3, Color(1.f, 1.f, 1.f));
	GridNodes.Colors.set(pointStartingIndex + 4, Color(1.f, 1.f, 1.f));
	GridNodes.Colors.set(pointStartingIndex + 5, Color(1.f, 1.f, 1.f));

	int currTexture = GridNodes.Textures.get(index);
	GridSpriteSettings::GridUVUnion UVs = SpriteSettings.is_valid() ? SpriteSettings->GetSpriteUVs(static_cast<GridTextures>(currTexture)) : GridSpriteSettings::GridUVUnion({ Vector2(0.f, 0.f), Vector2(1.f, 0.f), Vector2(0.f, 1.f), Vector2(1.f, 1.f) });

	GridNodes.UVs.set(pointStartingIndex, UVs[0]);
	GridNodes.UVs.set(pointStartingIndex + 1, UVs[1]);
	GridNodes.UVs.set(pointStartingIndex + 2, UVs[2]);

	GridNodes.UVs.set(pointStartingIndex + 3, UVs[2]);
	GridNodes.UVs.set(pointStartingIndex + 4, UVs[1]);
	GridNodes.UVs.set(pointStartingIndex + 5, UVs[3]);

	if (autoGenerateMesh)
	{
		GenerateArrayMesh();
		update();
	}
}

void GameGrid::GenerateArrayMesh()
{
	Ref<ArrayMesh> arrayMesh;
	arrayMesh.instance();

	Array arrays;
	arrays.resize(Mesh::ARRAY_MAX);
	arrays.set(Mesh::ARRAY_VERTEX, GridNodes.Points);
	arrays.set(Mesh::ARRAY_COLOR, GridNodes.Colors);
	arrays.set(Mesh::ARRAY_TEX_UV, GridNodes.UVs);

	arrayMesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

	MeshRef.set_mesh(arrayMesh);
}
