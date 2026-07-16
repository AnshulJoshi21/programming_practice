#include "asset_manager.h"
#include <assert.h>

void asset_manager_load(AssetManager* am) {
    assert(am);

    am->warrior_sheet = LoadTexture("assets/warrior/spritesheet/warrior_sheet_effect.png");
    assert(IsTextureValid(am->warrior_sheet));
}

void asset_manager_unload(AssetManager* am) {
    assert(am);

    UnloadTexture(am->warrior_sheet);
}
