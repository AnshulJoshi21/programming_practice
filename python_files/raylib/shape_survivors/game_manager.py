import math

import pyray as p

import systems
from bullet_manager import BulletManager
from collision_manager import CollisionManager
from drop_manager import DropManager
from enemy_manager import EnemyManager
from player import Player
from settings import BASE_HEIGHT, BASE_WIDTH, MAP_SIZE
from ui_manager import UiManager


class GameManager:
    def __init__(self) -> None:
        self.player: Player = Player()
        self.enemy_manager: EnemyManager = EnemyManager()
        self.bullet_manager: BulletManager = BulletManager()
        self.drop_manager: DropManager = DropManager()
        self.collision_manager: CollisionManager = CollisionManager(
            self.player, self.enemy_manager, self.bullet_manager, self.drop_manager
        )
        self.ui_manager: UiManager = UiManager(self.player)

        self.camera: p.Camera2D = p.Camera2D()
        self.camera.offset = p.Vector2(BASE_WIDTH / 2.0, BASE_HEIGHT / 2.0)
        self.camera.target = p.Vector2(0, 0)
        self.camera.rotation = 0.0
        self.camera.zoom = 1.0

    def draw(self) -> None:
        p.begin_mode_2d(self.camera)

        systems.draw_background_grid()
        self.drop_manager.draw()
        self.bullet_manager.draw()
        self.player.draw()
        self.enemy_manager.draw()

        p.end_mode_2d()

        self.ui_manager.draw()

    def update_camera(self) -> None:
        half_w: float = BASE_WIDTH / 2.0
        half_h: float = BASE_HEIGHT / 2.0

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
        # update entities
        self.player.update(dt)
        self.enemy_manager.update(
            dt,
            target_pos=p.Vector2(self.player.position.x, self.player.position.y),
            spawn_drop_func=self.drop_manager.spawn,
        )
        self.bullet_manager.update(dt)
        self.drop_manager.update()

        self.update_camera()

        # spawn entities
        #
        # player bullets
        if self.player.bullet_timer.tick():
            self.bullet_manager.spawn(
                config=self.player.bullet_config,
                start_pos=p.Vector2(self.player.position.x, self.player.position.y),
                target_pos=self.get_player_target(),
            )

        # collisions
        self.collision_manager.player_vs_enemy()
        self.collision_manager.player_vs_drop()
        self.collision_manager.bullet_vs_enemy()
        self.collision_manager.enemy_vs_enemy()
