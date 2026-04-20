import math
import random

import pyray as p

import components as c
import systems
from settings import MAP_SIZE


class Enemy:
    def __init__(self, target_pos: p.Vector2) -> None:
        random_angle: float = random.uniform(0, 2 * math.pi)
        random_spawn_distance: float = random.uniform(
            p.get_screen_width() / 2.0 + 100.0, p.get_screen_width() / 2.0 + 200.0
        )

        start_pos: p.Vector2 = p.Vector2(
            math.cos(random_angle) * random_spawn_distance + target_pos.x,
            math.sin(random_angle) * random_spawn_distance + target_pos.y,
        )

        self.position: c.PositionComponent = c.PositionComponent(
            x=start_pos.x, y=start_pos.y
        )
        self.rect: c.RectComponent = c.RectComponent(width=45.0, height=45.0)
        self.rotation: c.RotationComponent = c.RotationComponent(angle=0.0)
        self.color: c.ColorComponent = c.ColorComponent(
            tint=random.choice(
                [p.DARKBLUE, p.DARKBROWN, p.DARKGRAY, p.DARKGREEN, p.DARKPURPLE]
            )
        )
        self.text: c.TextComponent = c.TextComponent(string="E")
        self.move: c.MoveComponent = c.MoveComponent(
            speed=100.0, direction=p.Vector2(0, 0)
        )
        self.health: c.HealthComponent = c.HealthComponent(max_hp=5, hp=5)
        self.damage: c.DamageComponent = c.DamageComponent(amount=random.randint(1, 5))
        self.animation: c.AnimationComponent = c.AnimationComponent(hit_timer=0.0)

    def draw(self) -> None:
        systems.draw_rect(
            self.position, self.rect, self.rotation, self.color, self.animation
        )
        systems.draw_centered_text(
            text=self.text,
            bounds_rect=p.Rectangle(
                self.position.x, self.position.y, self.rect.width, self.rect.height
            ),
            font_size=20,
            spacing=0.0,
            tint=p.WHITE,
        )

    def update(self, dt: float, target_pos: p.Vector2) -> None:
        systems.set_direction(self.position, self.move, target_pos)
        systems.move_entity(self.position, self.move, dt)
        systems.set_bounds(
            self.position,
            self.rect.width / 2.0,
            self.rect.height / 2.0,
            p.Rectangle(0, 0, MAP_SIZE, MAP_SIZE),
        )
        systems.update_hit_timer(self.animation, dt)
