#include "texture_manager.h"
#include <assert.h>
#include <dirent.h>
#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void texture_manager_load(TextureManager* tm) {
    assert(tm);
    memset(tm->textures, 0, sizeof(tm->textures));

    const char* path = "animations";

    DIR* dir = opendir(path);
    assert(dir);

    struct dirent* entry;

    char full_path[PATH_MAX];

    int count = 0;
    while ((entry = readdir(dir))) {
        assert(count >= 0 && count < MAX_TEXTURES);
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);

        tm->textures[count] = LoadTexture(full_path);
        assert(IsTextureValid(tm->textures[count]));

        count++;
    }

    closedir(dir);

    assert(count == MAX_TEXTURES);
}

void texture_manager_unload(TextureManager* tm) {
    assert(tm);

    for (int i = 0; i < MAX_TEXTURES; i++) {
        UnloadTexture(tm->textures[i]);
    }
}
