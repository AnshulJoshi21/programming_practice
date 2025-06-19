import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "SNAKE"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

ROWS: int = 20
COLS: int = 20


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
