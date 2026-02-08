from math import cos, pi, sin

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Radar Sweep"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60


class Ring:
    def __init__(self) -> None:
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.inner_radius: float = 250.0
        self.outer_radius: float = 260.0
        self.start_angle: float = 0.0
        self.end_angle: float = 360.0
        self.segments: int = 64
        self.color: p.Color = p.DARKGREEN

    def draw(self) -> None:
        p.draw_ring(
            self.center,
            self.inner_radius,
            self.outer_radius,
            self.start_angle,
            self.end_angle,
            self.segments,
            self.color,
        )


class Line:
    def __init__(self, ring_center: p.Vector2) -> None:
        self.start_pos: p.Vector2 = p.Vector2(ring_center.x, ring_center.y)
        self.end_pos: p.Vector2 = p.Vector2(ring_center.x, ring_center.y)
        self.thickness: float = 5.0
        self.color: p.Color = p.RED

        self.angle_radians: float = 0.0
        self.angular_speed: float = 1.5

    def draw(self) -> None:
        p.draw_line_ex(
            self.start_pos, self.end_pos, self.thickness, self.color
        )

    def update(
        self, dt: float, ring_center: p.Vector2, ring_inner_radius
    ) -> None:
        self.angle_radians += self.angular_speed * dt
        if self.angle_radians > 2 * pi:
            self.angle_radians = 0.0

        self.end_pos.x = ring_center.x + (
            ring_inner_radius * sin(self.angle_radians)
        )
        self.end_pos.y = ring_center.y - (
            ring_inner_radius * cos(self.angle_radians)
        )


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    ring: Ring = Ring()
    line: Line = Line(ring.center)

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        line.update(dt, ring.center, ring.inner_radius)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        ring.draw()
        line.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
