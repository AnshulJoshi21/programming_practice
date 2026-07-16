from enum import Enum, auto

import pyray as p


class OriginType(Enum):
    CENTER = auto()
    TOP_LEFT = auto()


def center_and_draw_text(
    origin_type: OriginType,
    text: str,
    bounds: p.Rectangle,
    font_size: float,
    spacing: float,
    tint: p.Color,
) -> None:
    font: p.Font = p.get_font_default()
    text_size: p.Vector2 = p.measure_text_ex(font, text, font_size, spacing)
    pos: p.Vector2 = p.Vector2(0, 0)

    if origin_type == OriginType.CENTER:
        pos = p.Vector2(
            bounds.x - text_size.x / 2.0,
            bounds.y - text_size.y / 2.0,
        )
    elif origin_type == OriginType.TOP_LEFT:
        pos = p.Vector2(
            bounds.x + (bounds.width - text_size.x) / 2.0,
            bounds.y + (bounds.height - text_size.y) / 2.0,
        )

    p.draw_text_ex(font, text, pos, font_size, spacing, tint)


def draw_progress_bar(
    min_: int,
    max_: int,
    bounds: p.Rectangle,
    line_thickness: float,
    line_color: p.Color,
    bg_color: p.Color,
    fill_color: p.Color,
) -> None:
    # background rect
    p.draw_rectangle_rec(bounds, bg_color)

    # progress rect
    progress_width: float = min_ / max_ * bounds.width
    progress_rect: p.Rectangle = p.Rectangle(
        bounds.x, bounds.y, progress_width, bounds.height
    )

    p.draw_rectangle_rec(progress_rect, fill_color)

    # line rect
    p.draw_rectangle_lines_ex(bounds, line_thickness, line_color)
