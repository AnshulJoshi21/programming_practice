from enum import Enum

import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Inventory System"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

INV_ROWS: int = 2
INV_COLS: int = 2
MAX_INV: int = INV_ROWS * INV_COLS
MAX_STACK: int = 5

SLOT_GAP: float = 10.0
MARGIN_TOP: float = 50.0
MARGIN_HORIZONTAL: float = 160.0


items = {
    1: {"name": "Apple", "price": 0.5, "stock": 100},
    2: {"name": "Banana", "price": 0.3, "stock": 150},
    3: {"name": "Orange", "price": 0.6, "stock": 80},
}


def get_slot_size() -> float:
    # horizontal
    total_gap: float = (INV_COLS - 1) * SLOT_GAP  # remove trailing gap
    total_margin: float = MARGIN_HORIZONTAL * 2
    available_width: float = p.get_screen_width() - total_margin - total_gap

    return available_width / INV_COLS


class Item:
    def __init__(self, x: float, y: float) -> None:
        slot_size: float = get_slot_size()
        item_size: float = slot_size - (slot_size / 4)

        self.rect: p.Rectangle = p.Rectangle(x, y, item_size, item_size)
        self.color: p.Color = p.BLUE
        self.thickness: float = 2.0

    def draw(self) -> None:
        p.draw_rectangle_lines_ex(self.rect, self.thickness, self.color)
        center_and_draw_text()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    slot_size: float = get_slot_size()
    slot_thickness: float = 5.0
    slot_color: p.Color = p.BLACK

    slots: p.Rectangle = []
    for i in range(MAX_INV):
        x: float = (i % INV_COLS) * (slot_size + SLOT_GAP) + MARGIN_HORIZONTAL
        y: float = (i / INV_COLS) * (slot_size + SLOT_GAP) + MARGIN_TOP

        slots.append(p.Rectangle(x, y, slot_size, slot_size))

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw slots
        for slot in slots:
            p.draw_rectangle_lines_ex(slot, slot_thickness, slot_color)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
