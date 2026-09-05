from enum import IntEnum, auto

import pyray as p


class OriginType(IntEnum):
    CENTER = auto()
    TOP_LEFT = auto()


def draw_centered_text(
    origin_type: OriginType,
    text: str,
    bounds: p.Rectangle,
    font_size: float = 20.0,
    spacing: float = 2.0,
    tint: p.Color = p.BLACK,
) -> None:
    font: p.Font = p.get_font_default()
    text_size: p.Vector2 = p.measure_text_ex(font, text, font_size, spacing)
    pos: p.Vector2

    match origin_type:
        case OriginType.CENTER:
            pos = p.Vector2(
                bounds.x - text_size.x / 2.0,
                bounds.y - text_size.y / 2.0,
            )

        case OriginType.TOP_LEFT:
            pos = p.Vector2(
                bounds.x + (bounds.width - text_size.x) / 2.0,
                bounds.y + (bounds.height - text_size.y) / 2.0,
            )

        case _:
            raise ValueError(f"Invalid OriginType: {origin_type}")

    p.draw_text_ex(font, text, pos, font_size, spacing, tint)
