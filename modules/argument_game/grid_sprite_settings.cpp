#include "grid_sprite_settings.h"
#include "scene/resources/texture.h"


void GridSpriteSettings::set_texture(Ref<Texture> texture)
{
	if (texture.is_valid())
	{
		SpriteTexture = texture;
		set_spritesheet_size(Vector2(texture->get_width(), texture->get_height()));
		UpdateUVs();
	}
}


void GridSpriteSettings::UpdateUVs()
{
	for (int i = 0; i < GridTextures::Count; ++i)
	{
		int column = i % 2;
		int row = i / 2;
		float spriteWidth = SpriteSheetSize.x;
		float spriteHeight = SpriteSheetSize.y;

		float colStart = static_cast<float>(column) / static_cast<float>(NumCols);
		float colEnd = static_cast<float>(column + 1) / static_cast<float>(NumCols);
		float rowStart = static_cast<float>(row) / static_cast<float>(NumRows);
		float rowEnd = static_cast<float>(row + 1) / static_cast<float>(NumRows);

		UVs[i].topLeft = Vector2(colStart, rowStart);
		UVs[i].bottomLeft = Vector2(colStart, rowEnd);
		UVs[i].topRight = Vector2(colEnd, rowStart);
		UVs[i].bottomRight = Vector2(colEnd, rowEnd);
	}
}

GridSpriteSettings::GridUVUnion GridSpriteSettings::GetSpriteUVs(GridTextures texture)
{
	return UVs[texture];
}

void GridSpriteSettings::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_sprite_size", "size"), &GridSpriteSettings::set_sprite_size);
	ClassDB::bind_method(D_METHOD("get_sprite_size"), &GridSpriteSettings::get_sprite_size);
	ClassDB::bind_method(D_METHOD("set_spritesheet_size", "size"), &GridSpriteSettings::set_spritesheet_size);
	ClassDB::bind_method(D_METHOD("get_spritesheet_size"), &GridSpriteSettings::get_spritesheet_size);
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &GridSpriteSettings::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &GridSpriteSettings::get_texture);

	ADD_GROUP("Sprite Settings", "");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "SpriteSize"), "set_sprite_size", "get_sprite_size");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture"), "set_texture", "get_texture");
}
