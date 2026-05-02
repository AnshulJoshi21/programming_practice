import pyray as p

from game_manager import GameManager
from settings import BASE_HEIGHT, BASE_WIDTH


def main() -> None:
    p.set_config_flags(p.ConfigFlags.FLAG_WINDOW_RESIZABLE)
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Shape Survivors")
    p.set_target_fps(60)

    canvas: p.RenderTexture = p.load_render_texture(BASE_WIDTH, BASE_HEIGHT)
    assert p.is_render_texture_valid(canvas)

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_texture_mode(canvas)
        p.clear_background(p.RAYWHITE)

        game_manager.draw()

        p.end_texture_mode()

        scale: float = min(
            float(p.get_screen_width()) / float(BASE_WIDTH),
            float(p.get_screen_height()) / float(BASE_HEIGHT),
        )
        offset: p.Vector2 = p.Vector2(
            (p.get_screen_width() - (BASE_WIDTH * scale)) / 2.0,
            (p.get_screen_height() - (BASE_HEIGHT * scale)) / 2.0,
        )

        source: p.Rectangle = p.Rectangle(0, 0, BASE_WIDTH, -BASE_HEIGHT)
        dest: p.Rectangle = p.Rectangle(
            offset.x, offset.y, BASE_WIDTH * scale, BASE_HEIGHT * scale
        )

        p.begin_drawing()
        p.clear_background(p.BLACK)

        p.draw_texture_pro(canvas.texture, source, dest, p.Vector2(0, 0), 0.0, p.WHITE)

        p.end_drawing()

    p.unload_render_texture(canvas)

    p.close_window()


if __name__ == "__main__":
    main()
