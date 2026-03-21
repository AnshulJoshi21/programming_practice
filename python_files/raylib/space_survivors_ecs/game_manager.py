import pyray as p

import systems as S
from ecs import World
from entities import create_enemy, create_player
from settings import ENEMY_SPAWN_RATE, MAP_SIZE, MAX_ENEMIES
from utils import IntervalTimer, utils_draw_tiled_background


class GameManager:
    def __init__(self) -> None:
        self.world: World = World()
        self.player_id: int = create_player(self.world)
        self.enemy_count: int = 0
        self.enemy_timer: IntervalTimer = IntervalTimer(ENEMY_SPAWN_RATE)

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(
        self,
        background: p.Texture,
        spritesheet: p.Texture,
        sprite_dict: dict[str, p.Rectangle],
    ) -> None:
        p.begin_mode_2d(self.camera)

        utils_draw_tiled_background(background)
        S.system_draw(self.world, spritesheet, sprite_dict)

        p.end_mode_2d()

    def update(
        self,
        delta_time: float,
        mouse_pos_world: p.Vector2,
        sprite_dict: dict[str, p.Rectangle],
    ) -> None:
        player_pos: p.Vector2 = self.world.transform_list[self.player_id].pos

        # set player target
        self.world.target_list[self.player_id].pos = mouse_pos_world

        # spawn enemy
        if self.enemy_count < MAX_ENEMIES:
            if self.enemy_count <= 0 or self.enemy_timer.update():
                create_enemy(self.world, player_pos)
                self.enemy_count += 1

        S.system_handle_input(self.world)
        S.system_set_direction(self.world)
        S.system_rotate(self.world)
        S.system_move(self.world, delta_time)
        S.system_set_bounds(self.world, sprite_dict)
        S.system_despawn(self.world)

        # update camera target
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(half_w, min(player_pos.x, MAP_SIZE - half_w))
        self.camera.target.y = max(half_h, min(player_pos.y, MAP_SIZE - half_h))
