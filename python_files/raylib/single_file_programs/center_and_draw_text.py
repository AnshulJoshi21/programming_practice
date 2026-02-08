import pyray as p


def center_and_draw_text(
    text: str,
    layout_rect: p.Rectangle,
    font_size: float = 30.0,
    spacing: float = 2.0,
    color: p.Color = p.DARKGRAY,
):
    font: p.Font = p.get_font_default()
    text_size: p.Vector2 = p.measure_text_ex(font, text, font_size, spacing)
    pos: p.Vector2 = p.Vector2(
        layout_rect.x + layout_rect.width / 2.0 - text_size.x / 2.0,
        layout_rect.y + layout_rect.height / 2.0 - text_size.y / 2.0,
    )

    p.draw_text_ex(font, text, pos, font_size, spacing, color)
