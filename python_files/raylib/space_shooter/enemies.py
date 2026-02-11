import pyray as p
from settings import ROTATION_OFFSET


class Enemy:
    def __init__(
        self, spritesheet: p.Texture, sprite_data: dict[str, p.Rectangle]
    ) -> None:
        self.current_sprite: str = "enemyBlack1.png"

        self.texture: p.Texture = spritesheet
        self.source: p.Rectangle = sprite_data[self.current_sprite]
        self.dest: p.Rectangle = p.Rectangle()
        self.origin: p.Vector2 = p.Vector2(
            self.dest.width / 2.0, self.dest.height / 2.0
        )
        self.rotation: float = ROTATION_OFFSET
        self.tint: p.Color = p.WHITE

    def draw(self) -> None:
        p.draw_texture_pro(
            self.texture,
            self.source,
            self.dest,
            self.origin,
            self.rotation,
            self.tint,
        )
