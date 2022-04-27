#pragma once

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef size_t usize;
typedef float f32;
typedef double f64;

#define MAX(mA,mB) (((mA)>(mB))?(mA):(mB))
#define MIN(mA,mB) (((mA)<(mB))?(mA):(mB))

#define VECTOR2_ZERO (Vector2) { .x = 0, .y = 0 }

#define COLOR_TRANSPARENT (Color) { 0, 0, 0, 0 }
#define COLOR_BLACK (Color) { 0, 0, 0, 255 }
#define COLOR_WHITE (Color) { 255, 255, 255, 255 }
#define COLOR_RED (Color) { 255, 0, 0, 255 }
#define COLOR_GREEN (Color) { 0, 255, 0, 255 }
#define COLOR_BLUE (Color) { 0, 0, 255, 255 }

Vector2 Vector2Create(f32 x, f32 y);

f32 RectangleLeft(Rectangle rectangle);
f32 RectangleRight(Rectangle rectangle);
f32 RectangleBottom(Rectangle rectangle);
f32 RectangleTop(Rectangle rectangle);
