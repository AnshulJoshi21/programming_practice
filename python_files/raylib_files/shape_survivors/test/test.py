import pyray as p

BASE_WIDTH: int = 800
BASE_HEIGHT: int = 600


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "")
    p.set_target_fps(60)

    width: float = 300.0
    height: float = 30.0
    rect: p.Rectangle = p.Rectangle(
        BASE_WIDTH / 2.0 - width / 2.0, BASE_HEIGHT / 2.0 - height / 2.0, width, height
    )

    thick: float = 3.0
    line_color: p.Color = p.BLACK
    bg_color: p.Color = p.LIGHTGRAY
    fill_color: p.Color = p.RED

    current: int = 0
    max_: int = 100

    while not p.window_should_close():
        if p.is_key_pressed(p.KeyboardKey.KEY_DOWN):
            current += 5
        if p.is_key_pressed(p.KeyboardKey.KEY_UP):
            current -= 5

        current = max(0, min(current, max_))

        progress_width: float = current / max_ * width
        progress_rect: p.Rectangle = p.Rectangle(
            rect.x, rect.y, progress_width, rect.height
        )

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        p.draw_rectangle_rec(rect, bg_color)
        p.draw_rectangle_rec(progress_rect, fill_color)
        p.draw_rectangle_lines_ex(rect, thick, line_color)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
