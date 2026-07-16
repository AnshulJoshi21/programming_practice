#ifndef ANIMATION_DATA_H
#define ANIMATION_DATA_H

#include <raylib.h>

typedef enum Entity {
    ENTITY_WARRIOR,
} Entity;

typedef enum WarriorAnimation {
    WARRIOR_ANIMATION_IDLE,
    WARRIOR_ANIMATION_RUN,
    WARRIOR_ANIMATION_TWO_COMBO_ATTACK,
    WARRIOR_ANIMATION_DEATH,
    WARRIOR_ANIMATION_HURT,
    WARRIOR_ANIMATION_JUMP,
    WARRIOR_ANIMATION_UPTO_FALL,
    WARRIOR_ANIMATION_FALL,
    WARRIOR_ANIMATION_EDGE_GRAB,
    WARRIOR_ANIMATION_EDGE_IDLE,
    WARRIOR_ANIMATION_WALL_SLIDE,
    WARRIOR_ANIMATION_CROUCH,
    WARRIOR_ANIMATION_DASH,
    WARRIOR_ANIMATION_DASH_ATTACK,
    WARRIOR_ANIMATION_SLIDE,
    WARRIOR_ANIMATION_LADDER_GRAB,

    WARRIOR_ANIMATION_MAX
} WarriorAnimation;

typedef struct AnimationConfig {
    const Rectangle* frames;
    int              count;
    float            duration;
    bool             loops;
} AnimationConfig;

extern const AnimationConfig warrior_animation_configs[WARRIOR_ANIMATION_MAX];

#endif // ANIMATION_DATA_H
