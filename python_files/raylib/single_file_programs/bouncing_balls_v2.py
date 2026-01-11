from math import cos, pi, sin
from random import randint, uniform

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Bouncing Balls"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

MAX_BALLS: int = 200


class Ball:
    def __init__(self) -> None:
        self.radius: float = uniform(5, 30)
        self.center: p.Vector2 = p.Vector2(
            uniform(self.radius, p.get_screen_width() - self.radius),
            uniform(self.radius, p.get_screen_height() - self.radius),
        )
        speed: float = uniform(100, 300)
        angle_radians: float = uniform(0, 2 * pi)
        self.velocity: p.Vector2 = p.Vector2(
            cos(angle_radians) * speed, sin(angle_radians) * speed
        )
        self.color: p.Color = p.Color(
            randint(0, 255), randint(0, 255), randint(0, 255), 255
        )

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        # move
        self.center.x += self.velocity.x * dt
        self.center.y += self.velocity.y * dt

        # bounds
        if (
            self.center.x < self.radius
            or self.center.x > p.get_screen_width() - self.radius
        ):
            self.velocity.x *= -1
        if (
            self.center.y < self.radius
            or self.center.y > p.get_screen_height() - self.radius
        ):
            self.velocity.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    balls: list[Ball] = [Ball() for _ in range(MAX_BALLS)]

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        for ball in balls:
            ball.update(dt)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        for ball in balls:
            ball.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
