#pragma once

enum GridTextures
{
	None = -1,

	Blank,
	Highlighted,
	TeamA,
	TeamB,
	Turn1TeamA,
	Turn1TeamACounter,
	Turn1TeamB,
	Turn1TeamBCounter,
	Turn2TeamA,
	Turn2TeamACounter,
	Turn2TeamB,
	Turn2TeamBCounter,
	Turn3TeamA,
	Turn3TeamACounter,
	Turn3TeamB,
	Turn3TeamBCounter,
	Turn4TeamA,
	Turn4TeamACounter,
	Turn4TeamB,
	Turn4TeamBCounter,

	LastPlusOne,

	First = None + 1,
	Last = LastPlusOne - 1,
	Count = LastPlusOne - First,
	NumRows = Count / 2,
	NumCols = 2,
};

VARIANT_ENUM_CAST(GridTextures);
