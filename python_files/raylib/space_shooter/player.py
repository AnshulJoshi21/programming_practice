import math

import pyray as p
from settings import MAP_SIZE, ROTATION_OFFSET


class Player:
    def __init__(
        self, spritesheet: p.Texture, sprite_dict: dict[str, p.Rectangle]
    ) -> None:
        self.current_sprite: str = "playerShip1_blue.png"

        self.texture: p.Texture = spritesheet
        self.sprite_data: dict[str, p.Rectangle] = sprite_dict

        self.scale: p.Vector2 = p.Vector2(0.7, 0.7)
        self.source: p.Rectangle = sprite_dict[self.current_sprite]
        self.dest: p.Rectangle = p.Rectangle(
            MAP_SIZE / 2.0,
            MAP_SIZE / 2.0,
            self.source.width * self.scale.x,
            self.source.height * self.scale.y,
        )
        self.origin: p.Vector2 = p.Vector2(
            self.dest.width / 2.0, self.dest.height / 2.0
        )
        self.rotation: float = ROTATION_OFFSET
        self.tint: p.Color = p.WHITE

        self.speed: float = 400.0
        self.move_direction: p.Vector2 = p.Vector2(0, 0)
        self.look_direction: p.Vector2 = p.Vector2(0, 0)

    def draw(self) -> None:
        p.draw_texture_pro(
            self.texture,
            self.source,
            self.dest,
            self.origin,
            self.rotation,
            self.tint,
        )

    def update(self, dt: float, mouse_pos_world: p.Vector2) -> None:
        # rotate towards mouse
        self.look_direction.x = mouse_pos_world.x - self.dest.x
        self.look_direction.y = mouse_pos_world.y - self.dest.y
        self.rotation = (
            math.degrees(
                math.atan2(self.look_direction.y, self.look_direction.x)
            )
            + ROTATION_OFFSET
        )

        # handle input
        self.move_direction.x = int(p.is_key_down(p.KeyboardKey.KEY_D)) - int(
            p.is_key_down(p.KeyboardKey.KEY_A)
        )
        self.move_direction.y = int(p.is_key_down(p.KeyboardKey.KEY_S)) - int(
            p.is_key_down(p.KeyboardKey.KEY_W)
        )

        if self.move_direction.x != 0 and self.move_direction.y != 0:
            self.move_direction = p.vector2_normalize(self.move_direction)

        # move
        self.dest.x += self.move_direction.x * self.speed * dt
        self.dest.y += self.move_direction.y * self.speed * dt

        # bounds
        self.dest.x = max(
            self.dest.width / 2.0,
            min(self.dest.x, MAP_SIZE - self.dest.width / 2.0),
        )
        self.dest.y = max(
            self.dest.height / 2.0,
            min(self.dest.y, MAP_SIZE - self.dest.height / 2.0),
        )
