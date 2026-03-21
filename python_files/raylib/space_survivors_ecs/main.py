import pyray as p

from game_manager import GameManager
from settings import SCREEN_BACKGROUND, SCREEN_HEIGHT, SCREEN_TITLE, SCREEN_WIDTH
from xml_parser import spritesheet_xml_parser


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    background: p.Texture = p.load_texture("assets/background/purple.png")
    spritesheet: p.Texture = p.load_texture("assets/sheet.png")

    sprite_dict: dict[str, p.Rectangle] = spritesheet_xml_parser("assets/sheet.xml")

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        delta_time: float = p.get_frame_time()
        mouse_pos_world: p.Vector2 = p.get_screen_to_world_2d(
            p.get_mouse_position(), game_manager.camera
        )

        game_manager.update(delta_time, mouse_pos_world, sprite_dict)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        game_manager.draw(background, spritesheet, sprite_dict)

        p.end_drawing()

    p.unload_texture(background)
    p.unload_texture(spritesheet)

    p.close_window()


if __name__ == "__main__":
    main()
