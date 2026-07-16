import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600


def main() -> None:
    p.set_config_flags(p.ConfigFlags.FLAG_WINDOW_RESIZABLE)

    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "")
    p.set_target_fps(60)

    canvas: p.RenderTexture = p.load_render_texture(SCREEN_WIDTH, SCREEN_HEIGHT)
    assert p.is_render_texture_valid(canvas)

    while not p.window_should_close():
        p.begin_texture_mode(canvas)
        p.clear_background(p.RAYWHITE)
        p.end_texture_mode()

        scale: float = min(
            p.get_screen_width() / SCREEN_WIDTH, p.get_screen_height() / SCREEN_HEIGHT
        )
        offset: p.Vector2 = p.Vector2(
            (p.get_screen_width() - (SCREEN_WIDTH * scale)) / 2,
            (p.get_screen_height() - (SCREEN_HEIGHT * scale)) / 2,
        )

        source: p.Rectangle = p.Rectangle(0, 0, SCREEN_WIDTH, -SCREEN_HEIGHT)
        dest: p.Rectangle = p.Rectangle(
            offset.x, offset.y, SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale
        )

        p.begin_drawing()
        p.clear_background(p.BLACK)

        p.draw_texture_pro(canvas.texture, source, dest, p.Vector2(0, 0), 0.0, p.WHITE)

        p.end_drawing()

    p.unload_render_texture(canvas)

    p.close_window()


if __name__ == "__main__":
    main()
