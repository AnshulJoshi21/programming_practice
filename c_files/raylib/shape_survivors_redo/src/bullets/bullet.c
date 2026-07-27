#include "bullet.h"
#include <assert.h>

void bullet_init(Bullet* bullet, const BulletConfig* config) {
    assert(bullet);

    bullet->type         = config->type;
    const BulletDef* def = &bullet_db[bullet->type];

    bullet->center = config->center;
}

void bullet_update(Bullet* bullet, const float dt) {
    assert(bullet);
}

void bullet_draw(const Bullet* bullet) {
    assert(bullet);
}
