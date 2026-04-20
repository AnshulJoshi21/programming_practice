from dataclasses import dataclass

import pyray as p

import components as c
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
        self.position: c.PositionComponent = c.PositionComponent(
            x=start_pos.x, y=start_pos.y
        )
        self.circle: c.CircleComponent = c.CircleComponent(radius=4.0)
        self.color: c.ColorComponent = c.ColorComponent(tint=p.RED)
        self.move: c.MoveComponent = c.MoveComponent(
            speed=config.speed, direction=p.Vector2(0, 0)
        )
        self.damage: c.DamageComponent = c.DamageComponent(amount=config.damage)
        self.lifetime: c.LifetimeComponent = c.LifetimeComponent(
            max=config.lifetime, remaining=config.lifetime
        )

        systems.set_direction(self.position, self.move, target_pos)

    def draw(self) -> None:
        systems.draw_circle(self.position, self.circle, self.color)

    def update(self, dt: float) -> None:
        systems.move_entity(self.position, self.move, dt)
        systems.update_lifetime(self.lifetime, dt)
