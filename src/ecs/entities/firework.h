#pragma once

#include "../entity_builder.h"


EntityBuilder FireworkCreate
(
    Vector2 position,
    Vector2 initialVelocity,
    Vector2 acceleration,
    f32 lifetime
);
