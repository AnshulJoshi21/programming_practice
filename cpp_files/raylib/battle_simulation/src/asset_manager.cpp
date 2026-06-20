#include "asset_manager.hpp"
#include <cassert>

AssetManager::AssetManager() : spritesheet({LoadTexture("../character_spritesheet.png")}) {
    assert(IsTextureValid(spritesheet));
}

AssetManager::~AssetManager() {
    UnloadTexture(spritesheet);
}
