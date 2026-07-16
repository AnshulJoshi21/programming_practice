#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <raylib.h>

typedef struct AssetManager {
    Texture2D warrior_sheet;
} AssetManager;

void asset_manager_load(AssetManager* am);
void asset_manager_unload(AssetManager* am);

#endif // ASSET_MANAGER_H
