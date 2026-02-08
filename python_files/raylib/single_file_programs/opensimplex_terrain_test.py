import numpy as np
import pyray as p
from opensimplex import OpenSimplex

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Opensimplex Generation Test"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    noise: OpenSimplex = OpenSimplex()

    value: float = noise.noise2(1, 2)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
