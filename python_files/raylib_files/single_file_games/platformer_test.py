from random import choice, randint

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600

MAX_HEIGHT: float = SCREEN_HEIGHT / 2.0

RECT_SIZE: float = 10.0


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "")
    p.set_target_fps(60)

    player: p.Rectangle = p.Rectangle(0.0, MAX_HEIGHT, 10.0, 10.0)

    rect_list: list[p.Rectangle] = []
    x: float = 0.0
    y: float = MAX_HEIGHT + RECT_SIZE

    while x < SCREEN_WIDTH:
        rect_list.append(p.Rectangle(x, y, RECT_SIZE, RECT_SIZE))

        x += RECT_SIZE
        pos: str = choice(["top", "same", "bottom"])

        if pos == "top":
            y -= RECT_SIZE
        elif pos == "same":
            pass  # y remains same
        elif pos == "bottom":
            y += RECT_SIZE

        if y >= SCREEN_HEIGHT:
            y -= RECT_SIZE * randint(1, 2)
        if y <= MAX_HEIGHT:
            y += RECT_SIZE * randint(1, 2)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        for rect in rect_list:
            p.draw_rectangle_rec(rect, p.GRAY)

        p.draw_rectangle_rec(player, p.BLUE)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
