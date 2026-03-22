import pyray as p

import utils as u
from enemy_manager import EnemyManager
from player import Player
from settings import MAP_SIZE


class GameManager:
    def __init__(self) -> None:
        self.player: Player = Player()
        self.enemy_manager: EnemyManager = EnemyManager()

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        u.utils_draw_grid_background()
        self.player.draw()
        self.enemy_manager.draw()

        p.end_mode_2d()

    def update(self, dt: float) -> None:
        self.player.update(dt, target_pos=p.get_mouse_position())

        player_origin: p.Vector2 = u.utils_get_rect_origin(self.player.rect)

        self.enemy_manager.update(dt, target_pos=player_origin)

        # update camera target
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(half_w, min(player_origin.x, MAP_SIZE - half_w))
        self.camera.target.y = max(half_h, min(player_origin.y, MAP_SIZE - half_h))
