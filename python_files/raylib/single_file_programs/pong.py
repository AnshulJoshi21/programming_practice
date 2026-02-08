from random import randint

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Pong"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE


class Ball:
    def __init__(self) -> None:
        self.radius: float = 10.0
        self.center: p.Vector2 = p.Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
        self.speed_initial: float = 400.0
        self.speed: float = self.speed_initial
        self.speed_increment: float = 10.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.RED

        self.active: bool = False

    def reset(self) -> None:
        self.center: p.Vector2 = p.Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
        self.speed: float = self.speed_initial
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.active: bool = False

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float) -> None:
        # activate
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = True

        # update
        if self.active:
            self.direction = p.vector2_normalize(self.direction)

            # move
            self.center.x += self.direction.x * self.speed * dt
            self.center.y += self.direction.y * self.speed * dt

            # bounds
            if (
                self.center.y < self.radius
                or self.center.y > SCREEN_HEIGHT - self.radius
            ):
                self.direction.y *= -1


class Paddle:
    def __init__(self, x: float) -> None:
        height: float = 100.0
        width: float = 10.0
        y: float = SCREEN_HEIGHT / 2.0 - height / 2.0

        self.rect: p.Rectangle = p.Rectangle(x, y, width, height)
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.y = SCREEN_HEIGHT / 2.0 - self.rect.height / 2.0

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update_player(self, dt: float) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_W) and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            p.is_key_down(p.KeyboardKey.KEY_S)
            and self.rect.y < SCREEN_HEIGHT - self.rect.height
        ):
            self.rect.y += self.speed * dt

    def update_ai(self, dt: float, ball_y: float) -> None:
        if ball_y < self.rect.y + self.rect.height / 2.0 and self.rect.y > 0:
            self.rect.y -= self.speed * dt
        if (
            ball_y > self.rect.y + self.rect.height / 2.0
            and self.rect.y < SCREEN_HEIGHT - self.rect.height
        ):
            self.rect.y += self.speed * dt


class GameManager:
    def __init__(self) -> None:
        self.score_left: int = 0
        self.score_right: int = 0

        self.ball: Ball = Ball()
        self.player: Paddle = Paddle(10.0)
        self.ai: Paddle = Paddle(SCREEN_WIDTH - self.player.rect.width - 10.0)

    def reset(self) -> None:
        self.ball.reset()
        self.player.reset()
        self.ai.reset()

    def draw(self) -> None:
        # draw scores
        p.draw_text(str(self.score_left), 200, 30, 30, p.BLACK)
        p.draw_text(str(self.score_right), SCREEN_WIDTH - 200, 30, 30, p.BLACK)

        self.ball.draw()
        self.player.draw()
        self.ai.draw()

    def update(self, dt: float) -> None:
        self.ball.update(dt)
        self.player.update_player(dt)
        self.ai.update_ai(dt, self.ball.center.y)

        # ball collision paddle
        if p.check_collision_circle_rec(
            self.ball.center, self.ball.radius, self.player.rect
        ):
            self.ball.direction.x *= -1
            self.ball.speed += self.ball.speed_increment * dt
        if p.check_collision_circle_rec(
            self.ball.center, self.ball.radius, self.ai.rect
        ):
            self.ball.direction.x *= -1
            self.ball.speed += self.ball.speed_increment * dt

        # update scores
        if self.ball.center.x < -self.ball.radius:
            self.score_right += 1
            self.reset()
        if self.ball.center.x > SCREEN_WIDTH + self.ball.radius:
            self.score_left += 1
            self.reset()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
