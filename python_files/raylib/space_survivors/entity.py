from enum import IntEnum
from math import atan2, degrees, sqrt

import pyray as p

from settings import MAP_SIZE, ROTATION_OFFSET


class EntityType(IntEnum):
    PLAYER = 0
    ENEMY = 1
    LASER = 2


class Entity:
    def __init__(
        self,
        entity_type: EntityType,
        sprite_dict: dict[str, p.Rectangle],
        current_sprite: str,
        start_pos: p.Vector2,
        scale: float,
        speed: float,
    ) -> None:
        self.type: EntityType = entity_type
        self.current_sprite: str = current_sprite
        self.source: p.Rectangle = sprite_dict[current_sprite]
        self.dest: p.Rectangle = p.Rectangle(
            start_pos.x,
            start_pos.y,
            self.source.width * scale,
            self.source.height * scale,
        )
        self.origin: p.Vector2 = p.Vector2(
            self.dest.width / 2.0, self.dest.height / 2.0
        )
        self.rotation: float = 0.0
        self.tint: p.Color = p.WHITE

        self.speed: float = speed
        self.direction: p.Vector2 = p.Vector2(0, 0)

    def draw(self, spritesheet: p.Texture) -> None:
        p.draw_texture_pro(
            spritesheet, self.source, self.dest, self.origin, self.rotation, self.tint
        )

    def handle_input(self) -> None:
        if self.type == EntityType.PLAYER:
            self.direction.x = int(p.is_key_down(p.KeyboardKey.KEY_D)) - int(
                p.is_key_down(p.KeyboardKey.KEY_A)
            )
            self.direction.y = int(p.is_key_down(p.KeyboardKey.KEY_S)) - int(
                p.is_key_down(p.KeyboardKey.KEY_W)
            )

            self.direction = p.vector2_normalize(self.direction)

    def set_direction(self, target_pos: p.Vector2) -> None:
        if self.type == EntityType.PLAYER:
            return

        dx: float = target_pos.x - self.dest.x
        dy: float = target_pos.y - self.dest.y
        distance: float = sqrt(dx**2 + dy**2)
        if distance > 0:
            self.direction = p.Vector2(dx / distance, dy / distance)

    def rotate(self, target_pos: p.Vector2) -> None:
        dx: float = target_pos.x - self.dest.x
        dy: float = target_pos.y - self.dest.y
        self.rotation = degrees(atan2(dy, dx)) + ROTATION_OFFSET

    def move(self, delta_time: float) -> None:
        self.dest.x += self.direction.x * self.speed * delta_time
        self.dest.y += self.direction.y * self.speed * delta_time

    def set_bounds(self) -> None:
        half_w: float = self.dest.width / 2.0
        half_h: float = self.dest.height / 2.0

        self.dest.x = max(half_w, min(self.dest.x, MAP_SIZE - half_w))
        self.dest.y = max(half_h, min(self.dest.y, MAP_SIZE - half_h))
