import pyray as p

import components
from bullet import Bullet, BulletConfig


class BulletManager:
    def __init__(self) -> None:
        self.bullets: list[Bullet] = []

        self.spawner: components.Spawner = components.Spawner(max=200)

    def draw(self) -> None:
        for bullet in self.bullets:
            bullet.draw()

    def spawn(
        self, config: BulletConfig, start_pos: p.Vector2, target_pos: p.Vector2
    ) -> None:
        if len(self.bullets) >= self.spawner.max:
            return

        self.bullets.append(Bullet(config, start_pos, target_pos))

    def despawn(self, index: int) -> None:
        self.bullets[index] = self.bullets[len(self.bullets) - 1]
        self.bullets.pop()

    def update(self, dt: float) -> None:
        for i, bullet in enumerate(self.bullets):
            bullet.update(dt)

            if bullet.lifetime.remaining <= 0:
                self.despawn(index=i)
