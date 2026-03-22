import pyray as p

from settings import MAP_SIZE


def utils_get_rect_origin(rect: p.Rectangle) -> p.Vector2:
    return p.Vector2(rect.x + rect.width / 2.0, rect.y + rect.height / 2.0)


def utils_draw_grid_background() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY
    block_size: int = 30

    # vertical lines
    for x in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(x, 0), p.Vector2(x, MAP_SIZE), thickness, color)

    # horizontal lines
    for y in range(0, MAP_SIZE, block_size):
        p.draw_line_ex(p.Vector2(0, y), p.Vector2(MAP_SIZE, y), thickness, color)


def utils_center_and_draw_text(
    text: str, layout_rect: p.Rectangle, font_size: int = 20, color: p.Color = p.WHITE
) -> None:
    text_width: float = p.measure_text(text, font_size)
    x: int = int(layout_rect.x + (layout_rect.width - text_width) / 2.0)
    y: int = int(layout_rect.y + (layout_rect.height - font_size) / 2.0)

    p.draw_text(text, x, y, font_size, color)


class IntervalTimer:
    def __init__(self, duration: float) -> None:
        self.duration: float = duration
        self.last_time: float = p.get_time()

    def update(self) -> bool:
        current_time: float = p.get_time()
        if current_time - self.last_time >= self.duration:
            self.last_time = current_time

            return True

        return False
