import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Drag and Drop"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

ROWS: int = 2
COLS: int = 5
MARGIN_TOP: float = 50.0
MARGIN_HORIZONTAL: float = 50.0

def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    rect: p.Rectangle = p.Rectangle(
        p.get_screen_width() - 80, p.get_screen_height() - 80, 80.0, 80.0
    )
    color: p.Color = p.BLUE

    dragging: bool = False
    offset_x: float = 0.0
    offset_y: float = 0.0

    inventory: list[p.Rectangle] = []

    slots: list[p.Rectangle] = []
    slot_size: float = 100.0
    slot_gap: float = 10.0

    for i in range(ROWS):
        for j in range(COLS):
            x: float = j * (slot_size + slot_gap) + MARGIN_TOP
            y: float = i * (slot_size + slot_gap) + MARGIN_TOP

            slots.append(p.Rectangle(x, y, slot_size, slot_size))

    # for i in range(ROWS * COLS):
    #     x: int = (i % COLS) * (slot_size + slot_gap) + MARGIN_TOP
    #     y: int = (i // COLS) * (slot_size + slot_gap) + MARGIN_TOP

    #     slots.append(p.Rectangle(x, y, slot_size, slot_size))

    slot_thickness: float = 5.0
    slot_color: p.Color = p.BLACK

    while not p.window_should_close():
        mouse_pos: p.Vector2 = p.get_mouse_position()

        # dragging
        if p.is_mouse_button_pressed(p.MOUSE_LEFT_BUTTON):
            dragging = True
            offset_x = mouse_pos.x - rect.x
            offset_y = mouse_pos.y - rect.y

        if dragging:
            rect.x = mouse_pos.x - offset_x
            rect.y = mouse_pos.y - offset_y

        if p.is_mouse_button_released(p.MOUSE_LEFT_BUTTON):
            dragging = False

            for slot_rect in slots:
                if p.check_collision_recs(rect, slot_rect):
                    offset_x = (slot_rect.width - rect.width) / 2.0
                    offset_y = (slot_rect.height - rect.height) / 2.0

                    rect.x = slot_rect.x + offset_x
                    rect.y = slot_rect.y + offset_y

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        p.draw_text(
            f"Inventory size: {len(inventory)}",
            10,
            p.get_screen_height() - 200,
            20,
            p.BLACK,
        )

        center_and_draw_text(
            "Drag rectangle",
            p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height()),
            20.0,
        )

        for slot_rect in slots:
            slot_color = (
                p.RED if p.check_collision_recs(rect, slot_rect) else p.BLACK
            )
            p.draw_rectangle_lines_ex(slot_rect, slot_thickness, slot_color)

        p.draw_rectangle_rec(rect, color)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
