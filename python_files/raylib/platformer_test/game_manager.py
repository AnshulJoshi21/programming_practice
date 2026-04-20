import pyray as p

from player import Player
from settings import MAP_SIZE


def draw_background_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 50

    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thickness, color)
    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thickness, color)


class GameManager:
    def __init__(self, sprite_dict: dict[str, p.Rectangle]) -> None:

        self.player: Player = Player(sprite_dict)

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self, sheet: p.Texture) -> None:
        p.begin_mode_2d(self.camera)

        draw_background_grid()

        self.player.draw(sheet)

        p.end_mode_2d()

    def update_camera(self) -> None:
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(half_w, min(self.player.dest.x, MAP_SIZE - half_w))
        self.camera.target.y = max(half_h, min(self.player.dest.y, MAP_SIZE - half_h))

    def update(self, dt: float) -> None:
        self.player.update(dt)

        self.update_camera()
