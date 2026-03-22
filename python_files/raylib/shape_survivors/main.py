import pyray as p

import settings as s
from game_manager import GameManager


def main() -> None:
    p.init_window(s.SCREEN_WIDTH, s.SCREEN_HEIGHT, s.SCREEN_TITLE)

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(s.SCREEN_BACKGROUND)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
