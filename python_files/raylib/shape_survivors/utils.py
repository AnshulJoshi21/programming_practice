from enum import IntEnum

import pyray as p


class OriginType(IntEnum):
    CENTER = 0
    TOP_LEFT = 1


def center_and_draw_text(
    origin_type: OriginType,
    text: str,
    bounds_rect: p.Rectangle,
    font_size: float,
    spacing: float,
    tint: p.Color,
) -> None:

    font: p.Font = p.get_font_default()
    text_size: p.Vector2 = p.measure_text_ex(font, text, font_size, spacing)
    pos: p.Vector2

    match origin_type:
        case OriginType.CENTER:
            pos = p.Vector2(
                bounds_rect.x - (text_size.x) / 2.0, bounds_rect.y - (text_size.y) / 2.0
            )
        case OriginType.TOP_LEFT:
            pos = p.Vector2(
                bounds_rect.x + (bounds_rect.width - text_size.x) / 2.0,
                bounds_rect.y + (bounds_rect.height - text_size.y) / 2.0,
            )

    p.draw_text_ex(font, text, pos, font_size, spacing, tint)


def draw_progress_bar(
    current_val: float,
    max_val: float,
    bounds_rect: p.Rectangle,
    bg_color: p.Color,
    fill_color: p.Color,
    border_thickness: float,
    border_color: p.Color,
) -> None:
    # background
    p.draw_rectangle_rec(bounds_rect, bg_color)

    # progress
    progress_width: float = (current_val / max_val) * bounds_rect.width
    p.draw_rectangle_rec(
        p.Rectangle(bounds_rect.x, bounds_rect.y, progress_width, bounds_rect.height),
        fill_color,
    )

    # border
    p.draw_rectangle_lines_ex(bounds_rect, border_thickness, border_color)
