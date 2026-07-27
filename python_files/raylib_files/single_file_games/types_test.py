import math

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
MAX_BULLETS: int = 500
MAX_ORBITAL_BULLETS: int = 10


class Timer:
    def __init__(self, duration: float) -> None:
        self.elapsed: float = p.get_time()
        self.duration: float = duration

    def tick(self) -> bool:
        current_time: float = p.get_time()
        if current_time - self.elapsed >= self.duration:
            self.elapsed = current_time
            return True
        return False


class Bullet:
    def __init__(
        self,
        start_pos: p.Vector2,
        radius: float,
        color: p.Color,
        lifetime: float,
        damage: float,
    ) -> None:
        self.center: p.Vector2 = p.Vector2(start_pos.x, start_pos.y)
        self.radius: float = radius
        self.color: p.Color = color
        self.lifetime: float = lifetime
        self.damage: float = damage

    def update_lifetime(self, dt: float) -> None:
        self.lifetime -= dt
        if self.lifetime <= 0:
            self.lifetime = 0

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)


class ProjectileBullet(Bullet):
    def __init__(self, start_pos: p.Vector2, target_pos: p.Vector2) -> None:
        super().__init__(start_pos, 5.0, p.RED, 1.0, 1.0)

        dx: float = target_pos.x - start_pos.x
        dy: float = target_pos.y - start_pos.y
        distance: float = math.sqrt(dx**2 + dy**2)

        self.direction: p.Vector2 = p.Vector2(0, 0)
        if distance > 0:
            self.direction = p.Vector2(dx / distance, dy / distance)

        self.speed: float = 300.0

    def update(self, dt: float) -> None:
        super().update_lifetime(dt)

        if self.lifetime <= 0:
            return

        # move
        self.center.x += self.direction.x * self.speed * dt
        self.center.y += self.direction.y * self.speed * dt


class OrbitalBullet(Bullet):
    def __init__(self, start_pos: p.Vector2) -> None:
        super().__init__(start_pos, 10.0, p.BLUE, 5.0, 5.0)

        self.orbital_radius: float = 100.0
        self.orbital_speed: float = 1.0
        self.angle: float = 0.0

    def update(self, dt: float, bullet_index: int, bullet_count: int) -> None:
        super().update_lifetime(dt)

        self.angle += self.orbital_speed * dt
        origin: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        angle_step: float = (math.pi * 2) / bullet_count

        self.center = p.Vector2(
            origin.x
            + math.cos(self.angle + (bullet_index * angle_step)) * self.orbital_radius,
            origin.y
            + math.sin(self.angle + (bullet_index * angle_step)) * self.orbital_radius,
        )


class BulletManager:
    def __init__(self) -> None:
        self.bullets: list[Bullet] = []
        self.orbiting_orbs_count: int = 0

    def spawn(self) -> None:
        if len(self.bullets) >= MAX_BULLETS:
            return

    def despawn(self, index: int) -> None:
        assert index >= 0 and index < len(self.bullets)

        self.bullets[index] = self.bullets[len(self.bullets) - 1]
        self.bullets.pop()

    def update(self, dt: float) -> None:
        if self.orbiting_orbs_count >= MAX_ORBITAL_BULLETS:
            self.orbiting_orbs_count = MAX_ORBITAL_BULLETS - 1

        removal_indices: list[int] = []
        for index, bullet in enumerate(self.bullets):
            if isinstance(bullet, ProjectileBullet):
                bullet.update(dt)
            elif isinstance(bullet, OrbitalBullet):
                bullet.update(dt, index, self.orbiting_orbs_count)

            if bullet.lifetime <= 0:
                removal_indices.append(index)

        for index in removal_indices:
            self.despawn(index)

    def draw(self) -> None:
        for bullet in self.bullets:
            bullet.draw()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "")
    p.set_target_fps(60)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(p.RAYWHITE)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
