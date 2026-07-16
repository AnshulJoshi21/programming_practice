import math
import random

import pyray as p

import components
import systems
from settings import BASE_WIDTH, MAP_SIZE

ENEMY_SIZE: float = 45.0
ENEMY_MAX_HEALTH: int = 5
ENEMY_MAX_HIT_TIMER: float = 0.1


class Enemy:
    def __init__(self, target_pos: p.Vector2) -> None:
        random_angle: float = random.uniform(0, 2 * math.pi)
        random_distance: float = random.uniform(
            BASE_WIDTH / 2.0, BASE_WIDTH / 2.0 + 100
        )

        self.position: components.Position = components.Position(
            math.cos(random_angle) * random_distance + target_pos.x,
            math.sin(random_angle) * random_distance + target_pos.y,
        )

        self.rect: components.Rect = components.Rect(
            width=ENEMY_SIZE, height=ENEMY_SIZE
        )

        self.rotation: components.Rotation = components.Rotation(angle=0.0)

        self.color: components.Color = components.Color(
            tint=random.choice(
                [p.DARKBLUE, p.DARKBROWN, p.DARKGRAY, p.DARKGREEN, p.DARKPURPLE]
            )
        )

        self.text: components.Text = components.Text(
            text="E",
            font_size=20.0,
            spacing=0.0,
            tint=p.WHITE,
        )

        self.movement: components.Movement = components.Movement(
            speed=100.0,
            direction=p.Vector2(0, 0),
        )

        self.health: components.Health = components.Health(
            max=ENEMY_MAX_HEALTH,
            current=ENEMY_MAX_HEALTH,
        )

        self.damage: components.Damage = components.Damage(current=random.randint(0, 5))

        self.animation: components.Animation = components.Animation(
            max_hit_timer=ENEMY_MAX_HIT_TIMER,
            hit_timer=0.0,
        )

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        systems.set_direction(self.position, self.movement, target_pos)
        systems.move(self.position, self.movement, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_hit_timer(self.animation, dt)
        systems.update_health(self.health)

    def draw(self) -> None:
        systems.draw_rect(
            self.position, self.rotation, self.rect, self.color, self.animation
        )

        systems.draw_centered_text(
            self.position, self.rect.width, self.rect.height, self.text
        )
