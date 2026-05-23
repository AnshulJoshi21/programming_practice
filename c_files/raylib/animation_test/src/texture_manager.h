#pragma once

#include <raylib.h>

#define MAX_TEXTURES 13

typedef struct {
    Texture2D textures[MAX_TEXTURES];

} TextureManager;

void texture_manager_load(TextureManager* tm);
void texture_manager_unload(TextureManager* tm);
