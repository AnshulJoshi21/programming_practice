import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 800
SCREEN_TITLE: str = "SNAKE"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

ROWS: int = 20
COLS: int = 20
MARGIN: int = 100
BLOCK_WIDTH: int = (SCREEN_WIDTH - MARGIN * 2) // ROWS
BLOCK_HEIGHT: int = (SCREEN_HEIGHT - MARGIN * 2) // COLS


def draw_grid() -> None:
    for x in range(MARGIN, SCREEN_WIDTH - MARGIN - BLOCK_WIDTH, BLOCK_WIDTH):
        p.draw_line_ex(
            p.Vector2(x, MARGIN),
            p.Vector2(x, SCREEN_HEIGHT - MARGIN - BLOCK_HEIGHT),
            2.0,
            p.BLACK,
        )
    for y in range(MARGIN, SCREEN_WIDTH - MARGIN - BLOCK_WIDTH, BLOCK_WIDTH):
        p.draw_line_ex(
            p.Vector2(x, MARGIN),
            p.Vector2(x, SCREEN_HEIGHT - MARGIN - BLOCK_HEIGHT),
            2.0,
            p.BLACK,
        )


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)
        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
