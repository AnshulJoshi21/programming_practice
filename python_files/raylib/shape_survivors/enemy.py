import math
import random

import pyray as p

import components
import systems
from settings import BASE_WIDTH, MAP_SIZE


class Enemy:
    def __init__(self, target_pos: p.Vector2) -> None:
        random_angle: float = random.uniform(0, 2 * math.pi)
        random_distance: float = random.uniform(
            BASE_WIDTH / 2.0 + 100.0, BASE_WIDTH / 2.0 + 200.0
        )
        start_pos: p.Vector2 = p.Vector2(
            math.cos(random_angle) * random_distance + target_pos.x,
            math.sin(random_angle) * random_distance + target_pos.y,
        )

        self.position: components.Position = components.Position(
            start_pos.x, start_pos.y
        )
        size: float = 45.0
        self.rect: components.Rect = components.Rect(width=size, height=size)
        self.rotation: components.Rotation = components.Rotation(angle=0.0)
        self.color: components.Color = components.Color(
            tint=random.choice(
                [p.DARKBLUE, p.DARKBROWN, p.DARKGRAY, p.DARKGREEN, p.DARKPURPLE]
            )
        )
        self.text: components.Text = components.Text(
            text="E", font_size=20.0, spacing=0.0, tint=p.WHITE
        )
        self.move: components.Move = components.Move(
            speed=100.0, direction=p.Vector2(0, 0)
        )
        max_hp: int = 5
        self.health: components.Health = components.Health(max=max_hp, current=max_hp)
        self.damage: components.Damage = components.Damage(amount=random.randint(0, 5))
        self.animation: components.Animation = components.Animation(
            max_hit_timer=0.1, hit_timer=0.0
        )

    def draw(self) -> None:
        systems.draw_rect(
            self.position, self.rect, self.rotation, self.color, self.animation
        )
        systems.draw_centered_text(
            self.text, systems.get_dest_rect(self.position, self.rect)
        )

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        systems.set_direction(self.position, self.move, target_pos)
        systems.move(self.position, self.move, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            bounds_rect=p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_animation(self.animation, dt)
