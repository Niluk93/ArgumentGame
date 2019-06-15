#pragma once
#include "core/resource.h"
#include "common/debug.h"

class Texture;

enum GridTextures
{
	None = -1,

	Blank,
	Highlighted,
	TeamA,
	TeamB,
	Turn1TeamA,
	Turn1TeamB,
	Turn2TeamA,
	Turn2TeamB,
	Turn3TeamA,
	Turn3TeamB,
	Turn4TeamA,
	Turn4TeamB,

	Last,
	
	First = None + 1,
	Count = Last - First,
	NumRows = Count / 2,
	NumCols = 2,
};

class GridSpriteSettings : public Resource
{
	GDCLASS(GridSpriteSettings, Resource);
private:
	typedef struct
	{
		Vector2 topLeft;
		Vector2 topRight;
		Vector2 bottomLeft;
		Vector2 bottomRight;
	} GridUVs;

public:
	union GridUVUnion
	{
		GridUVs AsStruct;
		Vector2 AsArray[4];

	public:
		GridUVUnion(GridUVs UVs) : AsStruct(UVs) { }
		GridUVUnion(Vector2 UVs[4])
		{
			AsArray[0] = UVs[0];
			AsArray[1] = UVs[1];
			AsArray[2] = UVs[2];
			AsArray[3] = UVs[3];
		}

		Vector2 operator[](int index) const
		{
			assert(index < 0 || index >= 4); // Array index out of bounds
			return AsArray[index];
		}
	};

public:
	void set_sprite_size(const Vector2& _Size) { SpriteSize = _Size; UpdateUVs(); }
	const Vector2& get_sprite_size() const					{ return SpriteSize; }

	void set_spritesheet_size(const Vector2& _Size)			{ SpriteSheetSize = _Size; }
	const Vector2& get_spritesheet_size() const				{ return SpriteSheetSize; }

	void set_texture(Ref<Texture> texture);
	Ref<Texture> get_texture() const						{ return SpriteTexture; }

	void UpdateUVs();
	GridUVUnion GetSpriteUVs(GridTextures texture);

protected:
	static void _bind_methods();

private:
	Vector2						SpriteSize;
	Vector2						SpriteSheetSize;
	Ref<Texture>				SpriteTexture;
	GridUVs						UVs[GridTextures::Count];
};
