import pyray as p

from game_manager import GameManager
from settings import BASE_HEIGHT, BASE_WIDTH


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Shape Survivors")

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
