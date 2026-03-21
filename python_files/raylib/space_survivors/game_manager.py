import pyray as p

from enemy_manager import EnemyManager
from player import Player
from settings import MAP_SIZE


class GameManager:
    def __init__(self, sprite_dict: dict[str, p.Rectangle]) -> None:
        self.player: Player = Player(sprite_dict)
        self.enemy_manager: EnemyManager = EnemyManager()

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(
            self.player.entity.dest.x, self.player.entity.dest.y
        )
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw_tiled_background(self, background: p.Texture) -> None:
        for y in range(0, MAP_SIZE, background.height):
            for x in range(0, MAP_SIZE, background.width):
                p.draw_texture(background, x, y, p.WHITE)

    def draw(
        self,
        background: p.Texture,
        spritesheet: p.Texture,
    ) -> None:
        p.begin_mode_2d(self.camera)

        self.draw_tiled_background(background)
        self.player.draw(spritesheet)
        self.enemy_manager.draw(spritesheet)

        p.end_mode_2d()

    def update(
        self,
        sprite_dict: dict[str, p.Rectangle],
        delta_time: float,
        mouse_pos_world: p.Vector2,
    ) -> None:

        self.player.update(sprite_dict, delta_time, mouse_pos_world)
        player_pos: p.Vector2 = p.Vector2(
            self.player.entity.dest.x, self.player.entity.dest.y
        )
        self.enemy_manager.update(sprite_dict, delta_time, player_pos)

        # update camera target
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(half_w, min(player_pos.x, MAP_SIZE - half_w))
        self.camera.target.y = max(half_h, min(player_pos.y, MAP_SIZE - half_h))
