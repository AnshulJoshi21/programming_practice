import pyray as p
from random import randint

from utils import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Pong"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY


class Ball:
    def __init__(self) -> None:
        self.radius: float = 10.0
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.speed: float = 400.0
        self.speed_increment: float = 10.0
        self.color: p.Color = p.RED
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.is_active: bool = False

    def reset(self) -> None:
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.is_active: bool = False

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        # active ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.is_active = True

        if self.is_active:
            self.direction = p.vector2_normalize(self.direction)

            # move
            self.center.x += self.direction.x * self.speed * dt
            self.center.y += self.direction.y * self.speed * dt

            # bounds
            if (
                self.center.y < self.radius
                or self.center.y > p.get_screen_height() - self.radius
            ):
                self.direction.y *= -1


class Paddle:
    def __init__(self, x: float) -> None:
        width: float = 10.0
        height: float = 100.0
        y: float = p.get_screen_height() / 2.0 - height / 2.0

        self.rect: p.Rectangle = p.Rectangle(x, y, width, height)
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.y = p.get_screen_height() / 2.0 - self.rect.height / 2.0

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update_player(self, dt: float) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_W) and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            p.is_key_down(p.KeyboardKey.KEY_S)
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * dt

    def update_ai(self, ball_y: float, dt: float) -> None:
        if ball_y < self.rect.y + self.rect.height / 2.0 and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            ball_y > self.rect.y + self.rect.height / 2.0
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * dt


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score_left: int = 0
    score_right: int = 0

    ball: Ball = Ball()
    player: Paddle = Paddle(10.0)
    ai: Paddle = Paddle(p.get_screen_width() - player.rect.width - 10.0)

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        ball.update(dt)
        player.update_player(dt)
        ai.update_ai(ball.center.y, dt)

        # ball collision paddles
        if p.check_collision_circle_rec(ball.center, ball.radius, player.rect):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment * dt
        if p.check_collision_circle_rec(ball.center, ball.radius, ai.rect):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment * dt

        # update scores
        if ball.center.x < -ball.radius:
            score_right += 1
            ball.reset()
            player.reset()
            ai.reset()
        if ball.center.x > p.get_screen_width() + ball.radius:
            score_left += 1
            ball.reset()
            player.reset()
            ai.reset()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw scores
        p.draw_text(str(score_left), 200, 30, 30, p.BLACK)
        p.draw_text(str(score_right), p.get_screen_width() - 200, 30, 30, p.BLACK)

        ball.draw()
        player.draw()
        ai.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
