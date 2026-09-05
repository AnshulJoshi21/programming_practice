import random

import pyray as p

SCREEN_WIDTH: int = 1280
SCREEN_HEIGHT: int = 720


class Ball:
    def reset(self) -> None:
        self.center: p.Vector2 = p.Vector2(
            p.get_screen_width() / 2.0, p.get_screen_height() / 2.0
        )
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(
            random.choice([-1, 1]), random.choice([-1, 1])
        )
        self.active: bool = False

    def __init__(self) -> None:
        self.radius: float = 10.0
        self.color: p.Color = p.RED
        self.speed_increment: float = 10.0

        self.reset()

    def update(self, dt: float) -> None:
        # activate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = True

        if self.active:
            self.direction = p.vector2_normalize(self.direction)

            # move
            self.center.x += self.direction.x * self.speed * dt
            self.center.y += self.direction.y * self.speed * dt

            # set bounds
            if self.center.y < self.radius:
                self.center.y = self.radius
                self.direction.y *= -1

            if self.center.y > p.get_screen_height() - self.radius:
                self.center.y = p.get_screen_height() - self.radius
                self.direction.y *= -1

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)


class Paddle:
    def reset(self) -> None:
        self.rect.y = (p.get_screen_height() - self.rect.height) / 2.0

    def __init__(self, x: float) -> None:
        self.rect: p.Rectangle = p.Rectangle(x, 0, 15.0, 100.0)
        self.color: p.Color = p.BLACK
        self.speed: float = 300.0

        self.reset()

    def update_player(self, dt: float) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_W) and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            p.is_key_down(p.KeyboardKey.KEY_S)
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * dt

    def update_ai(self, dt: float, ball_y: float) -> None:
        if ball_y < self.rect.y + self.rect.height / 2.0 and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            ball_y > self.rect.y + self.rect.height / 2.0
            and self.rect.y < p.get_screen_height() - self.rect.height
        ):
            self.rect.y += self.speed * dt

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong")

    score_left: int = 0
    score_right: int = 0

    ball: Ball = Ball()
    player: Paddle = Paddle(10.0)
    ai: Paddle = Paddle(p.get_screen_width() - player.rect.width - 10.0)

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        ball.update(dt)
        player.update_player(dt)
        ai.update_ai(dt, ball.center.y)

        # collision
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
        p.clear_background(p.RAYWHITE)

        # draw scores
        p.draw_text(str(score_left), p.get_screen_width() // 4, 30, 30, p.BLACK)
        p.draw_text(
            str(score_right),
            p.get_screen_width() - p.get_screen_width() // 4,
            30,
            30,
            p.BLACK,
        )

        ball.draw()
        player.draw()
        ai.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
