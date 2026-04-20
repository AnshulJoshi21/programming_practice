import pyray as p

import utils
from player import Player


def draw_player_xp_bar(player: Player) -> None:
    margin: float = 50.0
    width: float = p.get_screen_width() - (margin * 2)
    height: float = 30.0
    rx: float = margin
    ry: float = 10

    # progress bar
    utils.draw_progress_bar(
        min_value=player.xp.xp,
        max_value=player.xp.xp_next,
        bounds_rect=p.Rectangle(rx, ry, width, height),
        border_thickness=5.0,
        border_color=p.BLACK,
        background_color=p.LIGHTGRAY,
        fill_color=p.SKYBLUE,
    )

    # player level
    p.draw_text(
        f"LV {player.level.current}",
        int(rx + width - 100),
        int(ry + 5),
        20,
        p.BLACK,
    )
