import random

import pyray as p

from player import Player
from settings import BLOCK_SIZE, MAP_SIZE


class GameManager:
    def __init__(self) -> None:
        self.grid_size: int = MAP_SIZE // BLOCK_SIZE
        self.bars: list[int] = [
            random.randint(1, self.grid_size // 2) for _ in range(self.grid_size)
        ]
        self.map: list[int] = []

        for level in range(self.grid_size):
            for bar in self.bars:
                if bar >= level:
                    self.map.append(1)
                else:
                    self.map.append(0)

        self.player: Player = Player()

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw_background(self) -> None:
        for i in range(self.grid_size):
            for j in range(self.grid_size):
                x: int = j * BLOCK_SIZE
                y: int = i * BLOCK_SIZE

                tile_color: p.Color = (
                    p.BLACK if self.map[j + (i * self.grid_size)] == 1 else p.WHITE
                )

                p.draw_rectangle_rec(
                    p.Rectangle(x, y, BLOCK_SIZE, BLOCK_SIZE), tile_color
                )
                p.draw_rectangle_lines_ex(
                    p.Rectangle(x, y, BLOCK_SIZE, BLOCK_SIZE), 2.0, p.WHITE
                )

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        self.draw_background()

        self.player.draw()

        p.end_mode_2d()

    def update_camera(self) -> None:
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(half_w, min(self.player.rect.x, MAP_SIZE - half_w))
        self.camera.target.y = max(half_h, min(self.player.rect.y, MAP_SIZE - half_h))

    def update(self, dt: float) -> None:
        self.player.update(dt)

        self.update_camera()
