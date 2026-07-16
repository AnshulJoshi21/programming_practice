from dataclasses import dataclass

import pyray as p

import components
import systems


@dataclass(slots=True)
class BulletConfig:
    damage: int
    speed: float
    lifetime: float


BULLET_RADIUS: float = 4.0


class Bullet:
    def __init__(
        self, config: BulletConfig, start_pos: p.Vector2, target_pos: p.Vector2
    ) -> None:
        self.position: components.Position = components.Position(
            start_pos.x, start_pos.y
        )

        self.circle: components.Circle = components.Circle(radius=BULLET_RADIUS)

        self.color: components.Color = components.Color(tint=p.RED)

        self.movement: components.Movement = components.Movement(
            speed=config.speed,
            direction=p.Vector2(0, 0),
        )

        self.damage: components.Damage = components.Damage(current=config.damage)

        self.lifetime: components.Lifetime = components.Lifetime(
            max=config.lifetime, current=config.lifetime
        )

        systems.set_direction(self.position, self.movement, target_pos)

    def update(self, dt: float) -> None:
        systems.move(self.position, self.movement, dt)
        systems.update_lifetime(self.lifetime, dt)

    def draw(self) -> None:
        systems.draw_circle(self.position, self.circle, self.color)
