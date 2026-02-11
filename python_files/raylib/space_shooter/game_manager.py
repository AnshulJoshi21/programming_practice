import pyray as p
from player import Player
from settings import MAP_SIZE


class GameManager:
    def __init__(
        self,
        background_texture: p.Texture,
        spritesheet: p.Texture,
        sprite_data: dict[str, p.Rectangle],
    ) -> None:
        self.background: p.Texture = background_texture
        self.background_source: p.Rectangle = p.Rectangle(
            0, 0, self.background.width, self.background.height
        )
        self.background_scale_offset: p.Vector2 = p.Vector2(
            MAP_SIZE / background_texture.width,
            MAP_SIZE / background_texture.height,
        )
        self.background_dest: p.Rectangle = p.Rectangle(
            0,
            0,
            background_texture.width * self.background_scale_offset.x,
            background_texture.height * self.background_scale_offset.y,
        )
        self.background_origin: p.Vector2 = p.Vector2(0, 0)
        self.background_rotation: float = 0.0
        self.background_tint: p.Color = p.WHITE

        self.player: Player = Player(spritesheet, sprite_data)

        # camera
        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(self.player.dest.x, self.player.dest.y)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        # draw background
        p.draw_texture_pro(
            self.background,
            self.background_source,
            self.background_dest,
            self.background_origin,
            self.background_rotation,
            self.background_tint,
        )

        self.player.draw()

        p.end_mode_2d()

    def update(self, dt: float, mouse_pos_world: p.Vector2) -> None:
        self.player.update(dt, mouse_pos_world)

        # update camera target
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0
        self.camera.target.x = max(
            half_w, min(self.player.dest.x, MAP_SIZE - half_w)
        )
        self.camera.target.y = max(
            half_h, min(self.player.dest.y, MAP_SIZE - half_h)
        )
