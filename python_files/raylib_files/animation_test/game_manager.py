import pyray as p

from settings import BASE_HEIGHT, BASE_WIDTH, MAP_SIZE


def draw_background_grid() -> None:
    thick: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 100

    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thick, color)
    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thick, color)


class GameManager:
    def __init__(self) -> None:
        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(BASE_WIDTH / 2.0, BASE_HEIGHT / 2.0)
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def update(self, dt: float) -> None:
        pass

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        draw_background_grid()

        p.end_mode_2d()
