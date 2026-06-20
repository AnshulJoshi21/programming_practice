#include "animation_manager.hpp"
#include <cassert>

static void animation_config_init(std:: < std::unordered_map<AnimationType, AnimationConfig>
                                  & config) {}

AnimationManager::AnimationManager()
    : current_type(AnimationType::idle), current_frame(0), frame_timer(0.0f), is_finished(false) {}
