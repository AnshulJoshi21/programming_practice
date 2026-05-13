import random

import pyray as p

BASE_WIDTH: int = 1280
BASE_HEIGHT: int = 720


class Ball:
    def __init__(self) -> None:
        self.radius: float = random.uniform(5, 50)
        self.center: p.Vector2 = p.Vector2(
            random.uniform(self.radius, p.get_screen_width() - self.radius),
            random.uniform(self.radius, p.get_screen_height() - self.radius),
        )
        self.speed: float = random.uniform(100, 1000)
        self.direction: p.Vector2 = p.Vector2(
            random.choice([-1, 1]),
            random.choice([-1, 1]),
        )
        self.color: p.Color = p.Color(
            random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 255
        )

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        self.direction = p.vector2_normalize(self.direction)

        # move
        self.center.x += self.direction.x * self.speed * dt
        self.center.y += self.direction.y * self.speed * dt

        # bounds
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
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Bouncing Balls")

    balls: list[Ball] = [Ball() for _ in range(200)]

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
