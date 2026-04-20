import math

import pyray as p

import collisions
import ui
from bullet_manager import BulletManager
from drop_manager import DropManager
from enemy_manager import EnemyManager
from game_state import GameState
from player import Player
from settings import MAP_SIZE
from upgrade_manager import UpgradeManager


def draw_background_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 30

    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thickness, color)

    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thickness, color)


class GameManager:
    def __init__(self) -> None:
        self.state: GameState = GameState.combat

        self.player: Player = Player()
        self.enemy_manager: EnemyManager = EnemyManager()
        self.bullet_manager: BulletManager = BulletManager()
        self.drop_manager: DropManager = DropManager()

        self.upgrade_manager: UpgradeManager = UpgradeManager(self.player)

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self) -> None:
        if self.state in [GameState.combat, GameState.upgrade]:
            p.begin_mode_2d(self.camera)

            draw_background_grid()

            self.bullet_manager.draw()
            self.player.draw()
            self.enemy_manager.draw()
            self.drop_manager.draw()

            p.end_mode_2d()

            ui.draw_player_xp_bar(self.player)

        if self.state == GameState.upgrade:
            self.upgrade_manager.draw()

    def update_camera(self) -> None:
        half_w: float = p.get_screen_width() / 2.0
        half_h: float = p.get_screen_height() / 2.0

        self.camera.target.x = max(
            half_w, min(self.player.position.x, MAP_SIZE - half_w)
        )
        self.camera.target.y = max(
            half_h, min(self.player.position.y, MAP_SIZE - half_h)
        )

    def get_player_target(self) -> p.Vector2:
        min_distance: float = float("inf")
        target: p.Vector2 = p.Vector2(0, 0)
        for enemy in self.enemy_manager.enemies:
            dx: float = enemy.position.x - self.player.position.x
            dy: float = enemy.position.y - self.player.position.y

            distance: float = math.sqrt(dx**2 + dy**2)
            if distance < min_distance:
                min_distance = distance
                target = p.Vector2(enemy.position.x, enemy.position.y)

        return target

    def update(self, dt: float) -> None:
        if self.state == GameState.combat:
            if self.player.level.pending > 0:
                self.state = GameState.upgrade

            # update entities
            self.player.update(dt)
            player_pos: p.Vector2 = p.Vector2(
                self.player.position.x, self.player.position.y
            )
            self.enemy_manager.update(
                dt, target_pos=player_pos, spawn_drop=self.drop_manager.spawn
            )
            self.bullet_manager.update(dt)
            self.drop_manager.update()

            self.update_camera()

            # spawn entities

            # spawn player bullet
            if self.player.bullet_timer.tick():
                self.bullet_manager.spawn(
                    self.player.bullet_config,
                    start_pos=player_pos,
                    target_pos=self.get_player_target(),
                )

            # collisions
            collisions.player_collision_enemy(self.player, self.enemy_manager)
            collisions.player_collision_drop(self.player, self.drop_manager)
            collisions.bullet_collision_enemy(self.bullet_manager, self.enemy_manager)
            collisions.enemy_collision_enemy(self.enemy_manager)

        if self.state == GameState.upgrade:
            self.upgrade_manager.update()

            if self.player.level.pending <= 0:
                self.state = GameState.combat
