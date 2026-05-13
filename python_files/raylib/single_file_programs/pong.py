import random

import pyray as p

BASE_WIDTH: int = 1280
BASE_HEIGHT: int = 720


class Ball:
    def __init__(self) -> None:
        self.radius: float = 10.0
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(
            random.choice([-1, 1]), random.choice([-1, 1])
        )
        self.color: p.Color = p.RED
        self.active: bool = False

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = True

        if self.active:
            self.direction = p.vector2_normalize(self.direction)

            self.center.x += self.direction.x * self.speed * dt
            self.center.y += self.direction.y * self.speed * dt

            if (
                self.center.x < self.radius
                or self.center.x > p.get_screen_width() - self.radius
            ):
                self.direction.x *= -1
            if (
                self.center.y < self.radius
                or self.center.y > p.get_screen_height() - self.radius
            ):
                self.direction.y *= -1


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Pong")

    ball: Ball = Ball()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        ball.update(dt)

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        ball.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
