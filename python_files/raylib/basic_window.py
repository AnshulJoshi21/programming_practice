import pyray as p

BASE_WIDTH: int = 1280
BASE_HEIGHT: int = 720


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "")
    p.set_target_fps(60)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
