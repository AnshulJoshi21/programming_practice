from enum import IntEnum

import pyray as p


class OriginType(IntEnum):
    center = 0
    top_left = 1


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
    pos: p.Vector2 = p.Vector2(0, 0)

    match origin_type:
        case OriginType.center:
            pos = p.Vector2(
                bounds_rect.x - text_size.x / 2.0,
                bounds_rect.y - text_size.y / 2.0,
            )
        case OriginType.top_left:
            pos = p.Vector2(
                bounds_rect.x + (bounds_rect.width - text_size.x) / 2.0,
                bounds_rect.y + (bounds_rect.height - text_size.y) / 2.0,
            )

    p.draw_text_ex(font, text, pos, font_size, spacing, tint)


def draw_progress_bar(
    min_value: float,
    max_value: float,
    bounds_rect: p.Rectangle,
    border_thickness: float,
    border_color: p.Color,
    background_color: p.Color,
    fill_color: p.Color,
) -> None:

    # background
    p.draw_rectangle_rec(bounds_rect, background_color)

    # progress bar
    width: float = min_value / max_value * bounds_rect.width
    p.draw_rectangle_rec(
        p.Rectangle(bounds_rect.x, bounds_rect.y, width, bounds_rect.height),
        fill_color,
    )

    # border
    p.draw_rectangle_lines_ex(bounds_rect, border_thickness, border_color)
