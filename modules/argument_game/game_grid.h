#pragma once
#include "scene/2d/node_2d.h"
#include "scene/2d/mesh_instance_2d.h"

#include "grid_sprite_settings.h"

struct InputDetails;

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

	/* void draw_colored_polygon (	const Vector<Point2> &p_points,
									const Color &p_color,
									const Vector<Point2> &p_uvs = Vector<Point2>(),
									Ref<Texture> p_texture = Ref<Texture>(),
									const Ref<Texture> &p_normal_map = Ref<Texture>(),
									bool p_antialiased = false);*/
public:
	GameGrid();

	void set_pivot(const Point2& pivot)								{ Pivot = pivot; UpdateDirty(); }
	Point2 get_pivot() const										{ return Pivot; }

	void set_gridSize(const Vector2& gridSize)						{ GridSize = gridSize; UpdateDirty(); }
	Vector2 get_gridSize() const									{ return GridSize; }

	void set_spriteSettings(const Ref<GridSpriteSettings>& setting)	{ SpriteSettings = setting; UpdateDirty(); }
	Ref<GridSpriteSettings> get_spriteSettings() const				{ return SpriteSettings; }

	Ref<Texture> get_texture() const								{ return SpriteSettings.is_valid() ? SpriteSettings->get_texture() : NULL; }

	void set_nodeTexture(int index, GridTextures texture)			{ GridNodes.Textures.set(index, texture); UpdateTile(index); }

	void _notification(int p_what);
	void _process(float p_time);
	void _input(const Ref<InputEvent>& event);

protected:

	void draw();
	bool tileSelected(const InputDetails& inputDetails);
	bool processMouseMovement(const Ref<InputEventMouseMotion>& mouseMove);
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

	MeshInstance2D				MeshRef;

private:
	static constexpr int defaultTileSize = 32;
};
