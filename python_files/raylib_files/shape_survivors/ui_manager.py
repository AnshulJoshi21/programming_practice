import pyray as p

import utils
from enemy_manager import EnemyManager
from player import Player
from settings import BASE_WIDTH


class UiManager:
    def __init__(self, player: Player, enemy_manager: EnemyManager) -> None:
        self.player: Player = player
        self.enemy_manager: EnemyManager = enemy_manager

    def draw_player_xp_bar(self) -> None:
        margin: float = 50.0
        bounds: p.Rectangle = p.Rectangle(margin, 10.0, BASE_WIDTH - margin * 2, 30.0)

        utils.draw_progress_bar(
            min_=self.player.xp.current,
            max_=self.player.xp.next,
            bounds=bounds,
            line_thickness=3.0,
            line_color=p.BLACK,
            bg_color=p.LIGHTGRAY,
            fill_color=p.BLUE,
        )

        # draw player level
        offset: float = 5.0
        p.draw_text(
            f"LV {self.player.level.current}",
            int(BASE_WIDTH - margin * 2),
            int(bounds.y + bounds.height + offset),
            20,
            p.BLACK,
        )

    def draw_player_hp_bar(self) -> None:
        width: float = self.player.rect.width + 10
        height: float = 10.0
        x: float = self.player.position.x - width / 2.0
        y: float = self.player.position.y - self.player.rect.height / 2.0 - height * 2

        utils.draw_progress_bar(
            min_=self.player.health.current,
            max_=self.player.health.max,
            bounds=p.Rectangle(x, y, width, height),
            line_thickness=1.0,
            line_color=p.BLACK,
            bg_color=p.LIGHTGRAY,
            fill_color=p.GREEN,
        )

    def draw_enemy_hp_bar(self) -> None:
        for enemy in self.enemy_manager.enemies:
            width: float = enemy.rect.width + 10
            height: float = 10.0
            x: float = enemy.position.x - width / 2.0
            y: float = enemy.position.y - enemy.rect.height / 2.0 - height * 2

            utils.draw_progress_bar(
                min_=enemy.health.current,
                max_=enemy.health.max,
                bounds=p.Rectangle(x, y, width, height),
                line_thickness=1.0,
                line_color=p.BLACK,
                bg_color=p.LIGHTGRAY,
                fill_color=p.RED,
            )
