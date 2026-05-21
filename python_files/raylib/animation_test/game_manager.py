import pyray as p

from animation import AnimationConfig, AnimationType, load_assets, unload_assets
from settings import MAP_HEIGHT, MAP_WIDTH


def draw_background_grid() -> None:
    thick: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_width: int = MAP_WIDTH // 4
    block_height: int = MAP_HEIGHT // 4

    for x in range(0, MAP_WIDTH, block_width):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_WIDTH), thick, color)
    for y in range(0, MAP_HEIGHT, block_height):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_HEIGHT, y), thick, color)


class GameManager:
    def __init__(self) -> None:
        self.animation_db: dict[AnimationType, AnimationConfig] = load_assets()

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2()
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        draw_background_grid()

        p.end_mode_2d()

    def update(self, dt: float) -> None:
        pass

    def shutdown(self) -> None:
        unload_assets(self.animation_db)
