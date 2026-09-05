import math
import random

import pyray as p

SCREEN_WIDTH: int = 1280
SCREEN_HEIGHT: int = 720
MAX_BALLS: int = 400


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 40)
        self.center: p.Vector2 = p.Vector2(
            random.uniform(self.radius, p.get_screen_width() - self.radius),
            random.uniform(self.radius, p.get_screen_height() - self.radius),
        )
        speed: float = random.uniform(100, 300)
        angle: float = random.uniform(0, 2 * math.pi)
        self.velocity: p.Vector2 = p.Vector2(
            math.cos(angle) * speed,
            math.sin(angle) * speed,
        )
        self.color: p.Color = p.Color(
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
            255,
        )

    def update(self, dt: float) -> None:
        # move
        self.center.x += self.velocity.x * dt
        self.center.y += self.velocity.y * dt

        # set bounds
        if self.center.x < self.radius:
            self.center.x = self.radius
            self.velocity.x *= -1

        if self.center.x > p.get_screen_width() - self.radius:
            self.center.x = p.get_screen_width() - self.radius
            self.velocity.x *= -1

        if self.center.y < self.radius:
            self.center.y = self.radius
            self.velocity.y *= -1

        if self.center.y > p.get_screen_height() - self.radius:
            self.center.y = p.get_screen_height() - self.radius
            self.velocity.y *= -1

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncing Balls")

    balls: list[Ball] = [Ball() for _ in range(MAX_BALLS)]

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        for ball in balls:
            ball.update(dt)

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        for ball in balls:
            ball.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
