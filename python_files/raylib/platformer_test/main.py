import pyray as p

from game_manager import GameManager
from settings import BASE_HEIGHT, BASE_WIDTH
from xml_parser import xml_parser


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Platformer Test")
    p.set_target_fps(60)

    sheet: p.Texture = p.load_texture("./sheet.png")
    p.is_texture_valid(sheet)

    sprite_dict: dict[str, p.Rectangle] = xml_parser("./sheet.xml")

    game_manager: GameManager = GameManager(sprite_dict)

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        game_manager.draw(sheet)

        p.end_drawing()

    p.unload_texture(sheet)

    p.close_window()


if __name__ == "__main__":
    main()
