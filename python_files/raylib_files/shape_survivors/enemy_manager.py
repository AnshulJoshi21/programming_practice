import pyray as p

import components
from drop_manager import DropManager, DropType
from enemy import Enemy

ENEMIES_MAX: int = 200


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: list[Enemy] = []
        self.timer: components.Timer = components.Timer(
            elapsed=p.get_time(), interval=5.0
        )

    def spawn(self, target_pos: p.Vector2) -> None:
        if len(self.enemies) >= ENEMIES_MAX:
            return

        if len(self.enemies) <= 0 or self.timer.tick():
            self.enemies.append(Enemy(target_pos))

    def despawn(self, index: int) -> None:
        if index < 0 or index >= len(self.enemies):
            return

        self.enemies[index] = self.enemies[len(self.enemies) - 1]
        self.enemies.pop()

    def update(
        self, dt: float, target_pos: p.Vector2, drop_manager: DropManager
    ) -> None:
        self.spawn(target_pos)

        enemy_removal_list: list[int] = []
        for index, enemy in enumerate(self.enemies):
            enemy.update(dt, target_pos)

            if enemy.health.current <= 0:
                # spawn drop
                drop_manager.spawn(
                    drop_manager.get_random_drop_type(),
                    p.Vector2(enemy.position.x, enemy.position.y),
                )

                enemy_removal_list.append(index)

        for index in enemy_removal_list:
            self.despawn(index)

    def draw(self) -> None:
        for enemy in self.enemies:
            enemy.draw()
