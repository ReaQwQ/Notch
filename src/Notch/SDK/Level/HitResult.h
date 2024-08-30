#pragma once

#include "../../Utils/Memory.h"
#include "../../Utils/HMath.h"

enum struct HitType : int {
	BLOCK = 0,
	ENTITY = 1,
	AIR = 3
};

class HitResult {
public:
	Vec3 start;
	Vec3 end;
	HitType hitType;
	int8_t face;
	Vec3i hitBlock;
	Vec3 hitPos;

	BUILD_ACCESS(this, Vec3i, liquidBlock, 0x54);
	BUILD_ACCESS(this, Vec3, liquidPos, 0x54);
};