import pyray as p


def center_and_draw_text(
    text: str,
    font_size: int,
    layout_rect: p.Rectangle,
    color: p.Color = p.BLACK,
) -> None:
    text_width: int = p.measure_text(text, font_size)
    text_x: int = int(layout_rect.x + layout_rect.width / 2 - text_width / 2)
    text_y: int = int(layout_rect.y + layout_rect.height / 2 - font_size / 2)

    p.draw_text(text, text_x, text_y, font_size, color)
