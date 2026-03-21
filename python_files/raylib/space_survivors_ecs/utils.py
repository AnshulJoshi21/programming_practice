import pyray as p

from settings import MAP_SIZE


def utils_draw_tiled_background(background: p.Texture) -> None:
    for y in range(0, MAP_SIZE, background.height):
        for x in range(0, MAP_SIZE, background.width):
            p.draw_texture(background, x, y, p.WHITE)


def utils_get_dest_rect(
    pos: p.Vector2, scale: p.Vector2, source: p.Rectangle
) -> p.Rectangle:
    return p.Rectangle(pos.x, pos.y, source.width * scale.x, source.height * scale.y)


# interval timer
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
