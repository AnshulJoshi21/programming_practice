from dataclasses import dataclass

import pyray as p

import components
import systems


@dataclass(slots=True)
class BulletConfig:
    speed: float
    damage: int
    lifetime: float


class Bullet:
    def __init__(
        self, config: BulletConfig, start_pos: p.Vector2, target_pos: p.Vector2
    ) -> None:
        self.position: components.Position = components.Position(
            start_pos.x, start_pos.y
        )
        self.circle: components.Circle = components.Circle(radius=4.0)
        self.color: components.Color = components.Color(tint=p.RED)
        self.move: components.Move = components.Move(
            speed=config.speed, direction=p.Vector2(0, 0)
        )
        self.damage: components.Damage = components.Damage(amount=config.damage)
        self.lifetime: components.Lifetime = components.Lifetime(
            max=config.lifetime, remaining=config.lifetime
        )

        systems.set_direction(self.position, self.move, target_pos)

    def draw(self) -> None:
        systems.draw_circle(self.position, self.circle, self.color)

    def update(self, dt: float) -> None:
        systems.move(self.position, self.move, dt)
        systems.update_lifetime(self.lifetime, dt)
