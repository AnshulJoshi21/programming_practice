import pyray as p

import utils
from player import Player
from settings import BASE_WIDTH


class UiManager:
    def __init__(self, player: Player) -> None:
        self.player: Player = player

    def _draw_player_progress_bar(self) -> None:
        padding: float = 50.0
        width: float = BASE_WIDTH - (padding * 2)
        height: float = 40.0
        x: float = padding
        y: float = 5

        bounds_rect: p.Rectangle = p.Rectangle(x, y, width, height)

        utils.draw_progress_bar(
            current_val=self.player.xp.xp,
            max_val=self.player.xp.xp_next,
            bounds_rect=bounds_rect,
            bg_color=p.WHITE,
            fill_color=p.SKYBLUE,
            border_thickness=4.0,
            border_color=p.BLACK,
        )

        # draw palyer level
        utils.center_and_draw_text(
            utils.OriginType.TOP_LEFT,
            f"LV {self.player.level.level}",
            bounds_rect,
            font_size=20.0,
            spacing=2.0,
            tint=p.BLACK,
        )

    def draw(self) -> None:
        self._draw_player_progress_bar()
