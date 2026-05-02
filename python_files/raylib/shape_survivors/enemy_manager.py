from typing import Callable

import pyray as p

import components
from drop_type import DropType
from enemy import Enemy


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: list[Enemy] = []

        self.spawner: components.Spawner = components.Spawner(max=200)
        self.timer: components.Timer = components.Timer(
            elapsed=p.get_time(), interval=3.0
        )

    def draw(self) -> None:
        for enemy in self.enemies:
            enemy.draw()

    def spawn(self, target_pos: p.Vector2) -> None:
        if len(self.enemies) >= self.spawner.max:
            return

        if len(self.enemies) == 0 or self.timer.tick():
            self.enemies.append(Enemy(target_pos))

    def despawn(self, index: int) -> None:
        self.enemies[index] = self.enemies[len(self.enemies) - 1]
        self.enemies.pop()

    def update(
        self,
        dt: float,
        target_pos: p.Vector2,
        spawn_drop_func: Callable[[DropType, p.Vector2], None],
    ) -> None:
        self.spawn(target_pos)

        for i, enemy in enumerate(self.enemies):
            enemy.update(dt, target_pos)

            if enemy.health.current <= 0:
                spawn_drop_func(
                    DropType.XP, p.Vector2(enemy.position.x, enemy.position.y)
                )
                self.despawn(index=i)
