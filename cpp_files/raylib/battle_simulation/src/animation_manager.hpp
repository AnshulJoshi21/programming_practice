#pragma once

#include <raylib.h>
#include <unordered_map>
#include <vector>

enum class AnimationType {
    none,

    spellcast,
    thrust,
    walk,
    slash,
    shoot,
    hurt,
    climb,
    idle,
    jump,
    sit,
    emote,
    run,
    watering,
    combat_idle,
    one_handed_slash,
    one_handed_backslash,
    one_handed_halfslash,

    max
};

struct AnimationConfig {
    std::vector<Rectangle> frames;
    float                  frame_duration;
    bool                   loops;
};

class AnimationManager {
  public:
    std::unordered_map<AnimationType, AnimationConfig> configs;

    AnimationType current_type;
    int           current_frame;
    float         frame_timer;
    bool          is_finished;

    AnimationManager();
};
