import pyray as p
from random import uniform
from math import radians, cos, sin

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "BOUNCING BALLS"
SCREEN_BACKGROUND: p.Color = p.SKYBLUE

NUM_OF_BALLS: int = 200


class Ball:
    def __init__(self) -> None:
        self.radius: float = uniform(10, 30)
        self.pos: p.Vector2 = p.Vector2(
            uniform(self.radius, SCREEN_WIDTH - self.radius),
            uniform(self.radius, SCREEN_HEIGHT - self.radius),
        )
        self.color: p.Color = p.Color(
            p.get_random_value(0, 255),
            p.get_random_value(0, 255),
            p.get_random_value(0, 255),
            225,
        )
        speed: float = uniform(100, 300)
        angle: float = radians(uniform(0, 360))
        self.velocity: p.Vector2 = p.Vector2(
            cos(angle) * speed,
            sin(angle) * speed,
        )

    def draw(self) -> None:
        p.draw_circle_v(self.pos, self.radius, self.color)

    def udpate(self) -> None:
        self.pos.x += self.velocity.x * p.get_frame_time()
        self.pos.y += self.velocity.y * p.get_frame_time()

        if self.pos.x < self.radius or self.pos.x > SCREEN_WIDTH - self.radius:
            self.velocity.x *= -1
        if (
            self.pos.y < self.radius
            or self.pos.y > SCREEN_HEIGHT - self.radius
        ):
            self.velocity.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    balls: list[Ball] = []
    for i in range(NUM_OF_BALLS):
        balls.append(Ball())

    while not p.window_should_close():
        for ball in balls:
            ball.udpate()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        for ball in balls:
            ball.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
