#pragma once
#include "scene/2d/node_2d.h"
#include "scene/resources/texture.h"
#include "scene/2d/mesh_instance_2d.h"

struct GridNodesSoA {
public:
	Vector<Point2> Points;
	Vector<Color> Colors;
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

	void draw();

	void set_pivot(const Point2& pivot)					{ Pivot = pivot; UpdateDirty(); }
	Point2 get_pivot() const							{ return Pivot; }

	void set_gridSize(const Vector2& gridSize)			{ GridSize = gridSize; UpdateDirty(); }
	Vector2 get_gridSize() const						{ return GridSize; }

	void set_texture(const Ref<Texture>& texture)		{ GridTexture = texture; UpdateDirty(); }
	Ref<Texture> get_texture() const					{ return GridTexture; }

	void _notification(int p_what);
protected:
	static void _bind_methods();

private:
	void UpdateDirty();

protected:
	Point2						Pivot;
	Vector2i					GridSize;
	GridNodesSoA				GridNodes;
	Ref<Texture>				GridTexture;

	MeshInstance2D				MeshRef;
};
