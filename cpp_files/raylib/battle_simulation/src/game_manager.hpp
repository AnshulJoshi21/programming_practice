#pragma once

#include "asset_manager.hpp"
#include <raylib.h>

class GameManager {
  public:
    AssetManager asset_manager;

    Camera2D camera;

    GameManager();
    ~GameManager();

    void draw(void) const;
    void update(const float dt);
};
