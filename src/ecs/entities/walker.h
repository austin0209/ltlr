#pragma once

#include "common.h"

typedef struct
{
	usize entity;
	f32 x;
	f32 y;
} WalkerBuilder;

void WalkerBuild(Scene* scene, PageAllocatorID params);
