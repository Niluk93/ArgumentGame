#include "game_grid.h"

GameGrid::GameGrid()
	: Pivot(0, 0)
	, GridSize(1, 1)
{
}

void GameGrid::draw()
{
	draw_mesh(MeshRef.get_mesh(), GridTexture, GridTexture);
}

void GameGrid::_notification(int p_what)
{
	switch (p_what)
	{
	case NOTIFICATION_DRAW:
	{
		draw();
	}
	break;
	default:
		break;
	}
}

void GameGrid::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("draw"), &GameGrid::draw);
	ClassDB::bind_method(D_METHOD("set_pivot", "pivot"), &GameGrid::set_pivot);
	ClassDB::bind_method(D_METHOD("get_pivot"), &GameGrid::get_pivot);
	ClassDB::bind_method(D_METHOD("set_gridSize", "gridSize"), &GameGrid::set_gridSize);
	ClassDB::bind_method(D_METHOD("get_gridSize"), &GameGrid::get_gridSize);
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &GameGrid::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &GameGrid::get_texture);

	ADD_GROUP("Grid", "");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "Pivot"), "set_pivot", "get_pivot");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "GridSize"), "set_gridSize", "get_gridSize");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");
}

void GameGrid::UpdateDirty()
{
	GridNodes.Points.clear();
	GridNodes.Points.resize((GridSize.width * GridSize.height) * 6);

	GridNodes.Colors.clear();
	GridNodes.Colors.resize(((GridSize.width * GridSize.height) * 6));

	GridNodes.UVs.clear();
	GridNodes.UVs.resize(((GridSize.width * GridSize.height) * 6));

	int gridElementWidth = (GridTexture.is_valid()) ? GridTexture->get_width() : 32;
	int gridElementHeight = (GridTexture.is_valid()) ? GridTexture->get_height() : 32;

	for (int i = 0; i < GridSize.width; ++i)
	{
		for (int j = 0; j < GridSize.height; ++j)
		{
			int pointStartingIndex = ((GridSize.width * j) + i) * 6;
			Vector2 gridNodePosition(i * gridElementWidth, j * gridElementHeight);
			GridNodes.Points.set(pointStartingIndex,		gridNodePosition);
			GridNodes.Points.set(pointStartingIndex + 1,	gridNodePosition + Vector2(gridElementWidth, 0));
			GridNodes.Points.set(pointStartingIndex + 2,	gridNodePosition + Vector2(0, gridElementHeight));

			GridNodes.Points.set(pointStartingIndex + 3,	gridNodePosition + Vector2(0, gridElementHeight));
			GridNodes.Points.set(pointStartingIndex + 4,	gridNodePosition + Vector2(gridElementWidth, 0));
			GridNodes.Points.set(pointStartingIndex + 5,	gridNodePosition + Vector2(gridElementWidth, gridElementHeight));

			GridNodes.Colors.set(pointStartingIndex,			Color(1.f, 1.f, 1.f));
			GridNodes.Colors.set(pointStartingIndex + 1,		Color(1.f, 1.f, 1.f));
			GridNodes.Colors.set(pointStartingIndex + 2,		Color(1.f, 1.f, 1.f));

			GridNodes.Colors.set(pointStartingIndex + 3,		Color(1.f, 1.f, 1.f));
			GridNodes.Colors.set(pointStartingIndex + 4,		Color(1.f, 1.f, 1.f));
			GridNodes.Colors.set(pointStartingIndex + 5,		Color(1.f, 1.f, 1.f));

			GridNodes.UVs.set(pointStartingIndex,			Vector2(0.f, 0.f));
			GridNodes.UVs.set(pointStartingIndex + 1,		Vector2(1.f / 2.f, 0.f));
			GridNodes.UVs.set(pointStartingIndex + 2,		Vector2(0.f, 1.f / 8.f));

			GridNodes.UVs.set(pointStartingIndex + 3,		Vector2(0.f, 1.f / 8.f));
			GridNodes.UVs.set(pointStartingIndex + 4,		Vector2(1.f / 2.f, 0.f));
			GridNodes.UVs.set(pointStartingIndex + 5,		Vector2(1.f / 2.f, 1.f / 8.f));
		}
	}

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
