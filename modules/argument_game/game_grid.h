#pragma once
#include "scene/2d/node_2d.h"
#include "scene/2d/mesh_instance_2d.h"

#include "grid_sprite_settings.h"
#include "grid_controller_base.h"

struct InputDetails;
class GridState;
class GridControllerBase;

struct GridNodesSoA {
public:
	Vector<Point2> Points;
	Vector<Color> Colors;
	Vector<GridTextures> Textures;
	Vector<Point2> UVs;
};

class GameGrid : public Node2D
{
	GDCLASS(GameGrid, Node2D);

public:
	GameGrid();

	void set_pivot(const Point2& pivot)														{ Pivot = pivot; UpdateDirty(); }
	Point2 get_pivot() const																{ return Pivot; }

	void set_gridSize(const Vector2& gridSize)												{ GridSize = gridSize; UpdateDirty(); }
	Vector2 get_gridSize() const															{ return GridSize; }

	void set_spriteSettings(const Ref<GridSpriteSettings>& setting)							{ SpriteSettings = setting; UpdateDirty(); }
	Ref<GridSpriteSettings> get_spriteSettings() const										{ return SpriteSettings; }

	Ref<Texture> get_texture() const														{ return SpriteSettings.is_valid() ? SpriteSettings->get_texture() : NULL; }

	void set_nodeTexture(int index, GridTextures texture, bool bAutogenerateMesh = true)	{ GridNodes.Textures.set(index, texture); UpdateTile(index, bAutogenerateMesh); }

	void set_gridController(const Ref<GridControllerBase>& gridController)					{ GridController = gridController; }
	Ref<GridControllerBase> get_gridController() const										{ return GridController; }

	void _notification(int p_what);
	void _process(float p_time);
	void _input(const Ref<InputEvent>& event);

protected:

	void draw();
	bool tileSelected(const InputDetails& inputDetails);
	bool gridStatePrev(const InputDetails& inputDetails);
	bool gridStateNext(const InputDetails& inputDetails);
	bool processMouseMovement(const Ref<InputEventMouseMotion>& mouseMove);
	Point2 absolutePositionToRelative(const Point2& position);
	int positionToTileIndex(Point2 position);

	static void _bind_methods();

private:
	void UpdateDirty();
	void UpdateTile(int index, bool autoGenerateMesh = true);
	void GenerateArrayMesh();

protected:
	Point2						Pivot;
	Vector2i					GridSize;
	GridNodesSoA				GridNodes;
	Ref<GridSpriteSettings>		SpriteSettings;

	// Current state of the grid.
	// TODO : Hold an array of grid states up to 4 turns in the future and swap them out as turns play out.
	Ref<GridState>				CurrentGridState;

	// handles what should be done with the input.
	// Important, since we will be using grid for editing cards, displaying cards and while playing the game
	Ref<GridControllerBase>		GridController;

	MeshInstance2D				MeshRef;

private:
	static constexpr int defaultTileSize = 32;
};
