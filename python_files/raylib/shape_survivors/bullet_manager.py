from math import sqrt

import pyray as p

import settings as s
import utils as u


class Bullet:
    def __init__(self, start_pos: p.Vector2, target_pos: p.Vector2) -> None:
        self.center: p.Vector2 = start_pos
        self.radius: float = 4.0
        self.color: p.Color = p.RED

        self.speed: float = 350.0

        dx: float = target_pos.x - start_pos.x
        dy: float = target_pos.y - start_pos.y
        distance: float = sqrt(dx**2 + dy**2)
        if distance > 0:
            self.direction: p.Vector2 = p.Vector2(dx / distance, dy / distance)

        self.damage: int = 1
        self.lifetime: float = s.BULLET_MAX_LIFETIME

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def move(self, dt: float) -> None:
        self.center.x += self.direction.x * self.speed * dt
        self.center.y += self.direction.y * self.speed * dt

    def update(self, dt: float) -> None:
        self.move(dt)

        # update lifetime
        self.lifetime -= dt


class BulletManager:
    def __init__(self) -> None:
        self.bullets: list[Bullet] = []

        self.spawn_rate: float = s.BULLET_SPAWN_RATE
        self.interval_timer: u.IntervalTimer = u.IntervalTimer(self.spawn_rate)

    def draw(self) -> None:
        for bullet in self.bullets:
            bullet.draw()

    def update(self, dt: float, start_pos: p.Vector2, target_pos: p.Vector2) -> None:
        # spawn
        if len(self.bullets) < s.MAX_BULLETS:
            if self.interval_timer.update():
                self.bullets.append(Bullet(start_pos, target_pos))

        target_to_delete_indices: list[int] = []
        for i, bullet in enumerate(self.bullets):
            bullet.update(dt)

            # despawn
            if bullet.lifetime <= 0:
                target_to_delete_indices.append(i)

        for i in target_to_delete_indices:
            self.bullets[i] = self.bullets[len(self.bullets) - 1]
            self.bullets.pop()
