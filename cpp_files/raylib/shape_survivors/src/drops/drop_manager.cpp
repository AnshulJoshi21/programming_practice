#include "drop_manager.hpp"

DropManager::DropManager() {}

void DropManager::draw(void) const
{
    for (const Drop &drop : drops) {
        drop.draw();
    }
}

void DropManager::spawn(const DropType type, const Vector2 start_pos)
{
    drops.push_back(Drop({type, start_pos}));
}

void DropManager::despawn(const size_t index)
{
    if (index >= drops.size())
        return;

    drops[index] = drops.back();
    drops.pop_back();
}

void DropManager::update(void)
{
    // update
    for (size_t i = 0; i < drops.size(); i++) {
        Drop &drop = drops[i];

        if (!drop.state.active) {
            despawn(i);
        }
    }
}
