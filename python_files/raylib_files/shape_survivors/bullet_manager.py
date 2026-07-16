import pyray as p

from bullet import Bullet, BulletConfig

BULLETS_MAX: int = 200


class BulletManager:
    def __init__(self) -> None:
        self.bullets: list[Bullet] = []

    def spawn(
        self, config: BulletConfig, start_pos: p.Vector2, target_pos: p.Vector2
    ) -> None:
        if len(self.bullets) >= BULLETS_MAX:
            return

        self.bullets.append(Bullet(config, start_pos, target_pos))

    def despawn(self, index: int) -> None:
        if index < 0 or index >= len(self.bullets):
            return

        self.bullets[index] = self.bullets[len(self.bullets) - 1]
        self.bullets.pop()

    def update(self, dt: float) -> None:
        bullet_removal_list: list[int] = []
        for index, bullet in enumerate(self.bullets):
            bullet.update(dt)

            if bullet.lifetime.current <= 0:
                bullet_removal_list.append(index)

        for index in bullet_removal_list:
            self.despawn(index)

    def draw(self) -> None:
        for bullet in self.bullets:
            bullet.draw()
