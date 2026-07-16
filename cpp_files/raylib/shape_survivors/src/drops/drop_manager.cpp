#include "../utils.hpp"
#include "drop_manager.hpp"

DropManager::DropManager() {}

DropType DropManager::get_random_drop_type(void) {
    const float random_num = Utils::randf(0, 100);

    if (random_num >= 90.0f)
        return DropType::HP;
    else if (random_num >= 75.0f)
        return DropType::XP;
    else
        return DropType::NONE;
}

void DropManager::spawn(const DropType type, const Vector2& start_pos) {
    drops.push_back(Drop(type, start_pos));
}

void DropManager::despawn(const int index) {
    const int drops_size = static_cast<int>(drops.size());
    if (index < 0 or index >= drops_size)
        return;

    drops[index] = drops[drops_size - 1];
    drops.pop_back();
}

void DropManager::update(void) {
    const int drops_size = static_cast<int>(drops.size());
    for (int i = 0; i < drops_size; i++) {
        Drop& drop = drops[i];

        if (!drop.state.active) {
            despawn(i);
            i--;
        }
    }
}

void DropManager::draw(void) const {
    for (const Drop& drop : drops) {
        if (!drop.state.active)
            continue;

        drop.draw();
    }
}
