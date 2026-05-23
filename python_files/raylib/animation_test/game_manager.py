import pyray as p

from asset_manager import AssetManager
from player import Player
from settings import BASE_HEIGHT, BASE_WIDTH, MAP_HEIGHT, MAP_WIDTH


def draw_background_grid() -> None:
    thick: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_width: int = MAP_WIDTH // 4
    block_height: int = MAP_HEIGHT // 4

    for x in range(0, MAP_WIDTH, block_width):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_HEIGHT), thick, color)
    for y in range(0, MAP_HEIGHT, block_height):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_WIDTH, y), thick, color)


class GameManager:
    def __init__(self) -> None:
        self.asset_manager: AssetManager = AssetManager()

        self.player: Player = Player(self.asset_manager)

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(BASE_WIDTH / 2.0, BASE_HEIGHT / 2.0)
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def update_camera(self) -> None:
        half_w: float = BASE_WIDTH / 2.0
        half_h: float = BASE_HEIGHT / 2.0

        self.camera.target.x = max(half_w, min(self.player.dest.x, MAP_WIDTH - half_w))
        self.camera.target.y = max(half_h, min(self.player.dest.y, MAP_HEIGHT - half_h))

    def update(self, dt: float) -> None:
        self.player.update(dt)

        self.update_camera()

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        draw_background_grid()

        self.player.draw()

        p.end_mode_2d()

    def shutdown(self) -> None:
        self.asset_manager.unload()
