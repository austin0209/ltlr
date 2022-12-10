#include "../components.h"
#include "common.h"
#include "firework.h"

EntityBuilder FireworkCreate
(
    const Vector2 position,
    const Vector2 initialVelocity,
    const Vector2 acceleration,
    const f32 lifetime
)
{
    Deque components = DEQUE_OF(Component);

    const u64 tags =
        TAG_POSITION
        | TAG_KINETIC
        | TAG_SMOOTH
        | TAG_FLEETING;

    ADD_COMPONENT(CPosition, ((CPosition)
    {
        .value = position
    }));

    ADD_COMPONENT(CKinetic, ((CKinetic)
    {
        .velocity = initialVelocity,
        .acceleration = acceleration,
    }));

    ADD_COMPONENT(CSmooth, ((CSmooth)
    {
        .previous = position,
    }));

    ADD_COMPONENT(CFleeting, ((CFleeting)
    {
        .lifetime = lifetime,
        .age = 0,
    }));

    return (EntityBuilder)
    {
        .tags = tags,
        .components = components,
    };
}
