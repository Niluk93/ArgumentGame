#include "game_grid.h"
#include "grid_state.h"
#include "game_input_handler.h"

#include "scene/scene_string_names.h"

#include "core/print_string.h"
#include "core/os/input.h"
#include "core/engine.h"
#include "scene/main/viewport.h"

GameGrid::GameGrid()
	: Pivot(0, 0)
	, GridSize(1, 1)
{
	BIND_INPUT_CALLBACK("argument_tile_select", this, &GameGrid::tileSelected);
	BIND_INPUT_CALLBACK("argument_grid_state_next", this, &GameGrid::gridStateNext);
	BIND_INPUT_CALLBACK("argument_grid_state_prev", this, &GameGrid::gridStatePrev);
}

void GameGrid::draw()
{
	draw_mesh(MeshRef.get_mesh(), get_texture(), get_texture());
}

bool GameGrid::tileSelected(const InputDetails& inputDetails)
{
	Vector2 currMousePosition = get_viewport()->get_mouse_position();
	int index = positionToTileIndex(currMousePosition);

	if (GridController.is_valid() && !(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
		GridController->process_tileSelected(index);

	return true;
}

bool GameGrid::gridStatePrev(const InputDetails &inputDetails)
{
	if (GridController.is_valid() && !(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
		GridController->process_gridStateChanged(false);

	return true;
}


bool GameGrid::gridStateNext(const InputDetails &inputDetails)
{
	if (GridController.is_valid() && !(inputDetails.ActionState ^ EInputActionStatus::JustPressed))
		GridController->process_gridStateChanged(true);

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
		if (GridController.is_valid())
			GridController->process_tileHover(lastIndex, currIndex);

		lastIndex = currIndex;
	}

	return true;
}


Point2 GameGrid::absolutePositionToRelative(const Point2 &position)
{
	Transform2D globalTransform = get_global_transform();
	Point2 newZeroOffset = Point2(0.f, 0.f) - globalTransform.get_origin();
	Point2 targetPosition = position + newZeroOffset;

	return targetPosition;
}

int GameGrid::positionToTileIndex(Point2 position)
{
	int gridElementWidth = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().width : defaultTileSize;
	int gridElementHeight = (SpriteSettings.is_valid()) ? SpriteSettings->get_sprite_size().height : defaultTileSize;

	if (position.x < 0 || position.x > gridElementWidth * GridSize.width)
		return -1;

	if (position.y < 0 || position.y > gridElementHeight * GridSize.height)
		return -1;

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

		if (GridController.is_valid())
		{
			GridController->init(this);
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
	ClassDB::bind_method(D_METHOD("set_gridController", "gridController"), &GameGrid::set_gridController);
	ClassDB::bind_method(D_METHOD("get_gridController"), &GameGrid::get_gridController);
	ClassDB::bind_method(D_METHOD("set_nodeTexture", "index", "texture", "bAutogenerateMesh"), &GameGrid::set_nodeTexture);

	ClassDB::bind_method(D_METHOD("_process", "delta"), &GameGrid::_process);
	ClassDB::bind_method(D_METHOD("_input", "event"), &GameGrid::_input);
	ClassDB::bind_method(D_METHOD("_update_mesh"), &GameGrid::GenerateArrayMesh);
	ClassDB::bind_method(D_METHOD("_update_dirty"), &GameGrid::UpdateDirty);

	ADD_GROUP("Grid", "");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Pivot"), "set_pivot", "get_pivot");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "GridSize"), "set_gridSize", "get_gridSize");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "GridTexture", PROPERTY_HINT_RESOURCE_TYPE, "GridSpriteSettings"), "set_spriteSettings", "get_spriteSettings");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "GridController", PROPERTY_HINT_RESOURCE_TYPE, "GridControllerBase"), "set_gridController", "get_gridController");
}

void GameGrid::UpdateDirty()
{
	// can't draw without a valid controller to tell us what we must draw
	if (!GridController.is_valid())
		return;

	GridNodes.Points.clear();
	GridNodes.Points.resize((GridSize.width * GridSize.height) * 6);

	GridNodes.Colors.clear();
	GridNodes.Colors.resize(((GridSize.width * GridSize.height) * 6));

	GridNodes.Textures.clear();
	GridNodes.Textures.resize(GridSize.width * GridSize.height);

	for (int i = 0; i < GridNodes.Textures.size(); ++i)
	{
		GridNodes.Textures.set(i, GridController->get_GridStateAtNode(i));
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
	update();
}
