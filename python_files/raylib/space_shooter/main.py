import pyray as p
from game_manager import GameManager
from settings import (
    SCREEN_BACKGROUND,
    SCREEN_HEIGHT,
    SCREEN_TITLE,
    SCREEN_WIDTH,
)
from spritesheet_xml_parser import spritesheet_xml_parser


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    spritesheet: p.Texture = p.load_texture(
        "/home/anonymous/Downloads/programming_practice/python_files/raylib/space_shooter/assets/spritesheet/sheet.png"
    )

    sprite_data: dict[str, p.Rectangle] = spritesheet_xml_parser(
        "/home/anonymous/Downloads/programming_practice/python_files/raylib/space_shooter/assets/spritesheet/sheet.xml"
    )

    background_texture: p.Texture = p.load_texture(
        "/home/anonymous/Downloads/programming_practice/python_files/raylib/space_shooter/assets/backgrounds/purple.png"
    )

    game_manager: GameManager = GameManager(
        background_texture, spritesheet, sprite_data
    )

    while not p.window_should_close():
        dt: float = p.get_frame_time()
        mouse_pos_world: p.Vector2 = p.get_screen_to_world_2d(
            p.get_mouse_position(), game_manager.camera
        )

        game_manager.update(dt, mouse_pos_world)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        game_manager.draw()

        p.end_drawing()

    p.unload_texture(spritesheet)
    p.unload_texture(background_texture)

    p.close_window()


if __name__ == "__main__":
    main()
