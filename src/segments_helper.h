#pragma once

#define CREATE_SOLID_BLOCK(mX, mY, mWidth, mHeight) \
	{ \
		const Rectangle aabb = (Rectangle) { \
			.x = (mX) + offset.x, \
			.y = (mY) + offset.y, \
			.width = (mWidth), \
			.height = (mHeight), \
		}; \
		BlockBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.aabb = aabb; \
		builder.resolutionSchema = RESOLVE_ALL; \
		builder.layer = LAYER_TERRAIN;                    \
        PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(BlockBuilder));                                            \
		SceneDefer(scene, BlockBuild, id); \
	}

#define CREATE_ONE_WAY_BLOCK(mX, mY, mWidth, mHeight) \
	{ \
		const Rectangle aabb = (Rectangle) { \
			.x = (mX) + offset.x, \
			.y = (mY) + offset.y, \
			.width = (mWidth), \
			.height = (mHeight), \
		}; \
		BlockBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.aabb = aabb; \
		builder.resolutionSchema = RESOLVE_UP; \
		builder.layer = LAYER_TERRAIN;                      \
        PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(BlockBuilder)); \
		SceneDefer(scene, BlockBuild, id); \
	}

#define CREATE_INVISIBLE_BLOCK(mX, mY, mWidth, mHeight) \
	{ \
		const Rectangle aabb = (Rectangle) { \
			.x = (mX) + offset.x, \
			.y = (mY) + offset.y, \
			.width = (mWidth), \
			.height = (mHeight), \
		}; \
		BlockBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.aabb = aabb; \
		builder.resolutionSchema = RESOLVE_ALL; \
		builder.layer = LAYER_INVISIBLE; \
        PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(BlockBuilder));                                            \
		SceneDefer(scene, BlockBuild, id); \
	}

#define CREATE_SPIKE(mX, mY, mRotation) \
	{ \
		const f32 x = (mX) + offset.x; \
		const f32 y = (mY) + offset.y; \
		SpikeBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.x = x; \
		builder.y = y; \
		builder.rotation = (mRotation);      \
    	PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(SpikeBuilder));                                            \
		SceneDefer(scene, SpikeBuild, id); \
	}

#define CREATE_WALKER(mX, mY) \
	{ \
		const f32 x = (mX) + offset.x; \
		const f32 y = (mY) + offset.y; \
		WalkerBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.x = x; \
		builder.y = y;             \
    	PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(WalkerBuilder));                                            \
		SceneDefer(scene, WalkerBuild, id); \
	}

#define CREATE_BATTERY(mX, mY) \
	{ \
		const f32 x = (mX) + offset.x + 1; \
		const f32 y = (mY) + offset.y; \
		BatteryBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.x = x; \
		builder.y = y;              \
    	PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(BatteryBuilder));                                            \
		SceneDefer(scene, BatteryBuild, id); \
	}

#define CREATE_SOLAR_PANEL(mX, mY) \
	{ \
		const f32 x = (mX) + offset.x - 36; \
		const f32 y = (mY) + offset.y - 24; \
		SolarPanelBuilder builder; \
		builder.entity = SceneAllocateEntity(scene); \
		builder.x = x; \
		builder.y = y;                  \
    	PageAllocatorID id = PageAllocatorWrite(&scene->pageAllocator, &builder, sizeof(SolarPanelBuilder));                                            \
		SceneDefer(scene, SolarPanelBuild, id); \
	}

#define DRAW_SPRITE(mSprite, mX, mY) \
	{ \
		const AtlasDrawParams params = (AtlasDrawParams) { \
			.sprite = (mSprite), \
			.position = Vector2Create((mX) + offset.x, (mY) + offset.y), \
			.intramural = (Rectangle) { 0, 0, 0, 0 }, \
			.reflection = REFLECTION_NONE, \
			.tint = COLOR_WHITE, \
		}; \
		AtlasDraw(atlas, &params); \
	}

#define DRAW_COVER_UP(mX, mY, mColor) \
	{ \
		DrawRectangle((mX) + offset.x, (mY) + offset.y, 6, 6, (mColor)); \
	}
