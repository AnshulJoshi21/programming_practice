from math import cos, pi, sin, sqrt
from random import choice, randint, uniform

import pyray as p

import settings as s
import utils as u


class Enemy:
    def __init__(self, target_pos: p.Vector2) -> None:
        random_angle: float = uniform(0, 2 * pi)
        start_pos: p.Vector2 = p.Vector2(
            cos(random_angle) * s.ENEMY_SPAWN_DISTANCE + target_pos.x,
            sin(random_angle) * s.ENEMY_SPAWN_DISTANCE + target_pos.y,
        )

        size: float = 50.0
        self.rect: p.Rectangle = p.Rectangle(start_pos.x, start_pos.y, size, size)
        self.color: p.Color = choice(
            [p.DARKBLUE, p.DARKBROWN, p.DARKGRAY, p.DARKGREEN, p.DARKPURPLE]
        )
        self.speed: float = 100.0

        self.max_hp: int = 10
        self.hp: int = self.max_hp
        self.damage: int = randint(1, 3)

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

        u.utils_center_and_draw_text("E", self.rect)

    def move(self, dt: float) -> None:
        self.rect.x += self.direction.x * self.speed * dt
        self.rect.y += self.direction.y * self.speed * dt

    def bounds(self) -> None:

        self.rect.x = max(0.0, min(self.rect.x, s.MAP_SIZE - self.rect.width))
        self.rect.y = max(0.0, min(self.rect.y, s.MAP_SIZE - self.rect.height))

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        dx: float = target_pos.x - self.rect.x
        dy: float = target_pos.y - self.rect.y
        distance: float = sqrt(dx**2 + dy**2)
        if distance > 0:
            self.direction: p.Vector2 = p.Vector2(dx / distance, dy / distance)
            self.move(dt)
            self.bounds()


class EnemyManager:
    def __init__(self) -> None:
        self.enemies: list[Enemy] = []
        self.spawn_rate: float = s.ENEMY_SPAWN_RATE

        self.interval_timer: u.IntervalTimer = u.IntervalTimer(self.spawn_rate)

    def draw(self) -> None:
        for enemy in self.enemies:
            enemy.draw()

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        # spawn
        if len(self.enemies) < s.MAX_ENEMIES:
            if len(self.enemies) <= 0 or self.interval_timer.update():
                self.enemies.append(Enemy(target_pos))

        target_to_delete_indices: list[int] = []
        for i, enemy in enumerate(self.enemies):
            enemy.update(dt, target_pos)

            if enemy.hp <= 0:
                target_to_delete_indices.append(i)

        for i in target_to_delete_indices:
            self.enemies[i] = self.enemies[len(self.enemies) - 1]
            self.enemies.pop()
