from random import randint

import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Breakout"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

BRICK_ROWS: int = 5
BRICK_COLS: int = 10
BRICK_WIDTH: int = 79
BRICK_HEIGHT: int = 30
BRICK_GAP: int = 2


class Brick:
    def __init__(self, x: int, y: int) -> None:
        self.x: int = x
        self.y: int = y
        self.is_active: bool = True
        self.color: p.Color = p.GRAY

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BRICK_WIDTH, BRICK_HEIGHT, self.color)


def bricks_init() -> list[Brick]:
    bricks: list[Brick] = []

    for i in range(BRICK_ROWS):
        for j in range(BRICK_COLS):
            x: int = j * (BRICK_WIDTH + BRICK_GAP)
            y: int = i * (BRICK_HEIGHT + BRICK_GAP)

            bricks.append(Brick(x, y))

    return bricks


class Paddle:
    def __init__(self) -> None:
        width: float = 100.0
        height: float = 10.0
        x: float = p.get_screen_width() / 2.0 - width / 2.0
        y: float = p.get_screen_height() - height - 10.0

        self.rect: p.Rectangle = p.Rectangle(x, y, width, height)
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.x = p.get_screen_width() / 2.0 - self.rect.width / 2.0

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)

    def update(self, dt: float) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_A) and self.rect.x > 0:
            self.rect.x -= self.speed * dt
        if (
            p.is_key_down(p.KeyboardKey.KEY_D)
            and self.rect.x < SCREEN_WIDTH - self.rect.width
        ):
            self.rect.x += self.speed * dt


class Ball:
    def __init__(self, paddle_rect: p.Rectangle) -> None:
        self.radius: float = 10.0
        self.center: p.Vector2 = p.Vector2(
            paddle_rect.x + paddle_rect.width / 2.0,
            paddle_rect.y - self.radius - 5.0,
        )
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.RED
        self.speed: float = 400.0
        self.speed_increment: float = 10.0
        self.is_active: bool = False

    def reset(self, paddle_rect: p.Rectangle) -> None:
        self.center: p.Vector2 = p.Vector2(
            paddle_rect.x + paddle_rect.width / 2.0,
            paddle_rect.y - self.radius - 5.0,
        )
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1,
            -1 if randint(0, 1) == 0 else 1,
        )
        self.speed: float = 400.0
        self.is_active: bool = False

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float, paddle_rect: p.Rectangle) -> None:
        # update position when inactive
        if not self.is_active:
            self.center: p.Vector2 = p.Vector2(
                paddle_rect.x + paddle_rect.width / 2.0,
                paddle_rect.y - self.radius - 5.0,
            )

        # activate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.is_active = True

        if self.is_active:
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


def ball_collision_paddle(ball: Ball, paddle: Paddle, dt: float) -> None:
    if p.check_collision_circle_rec(ball.center, ball.radius, paddle.rect):
        ball.direction.y *= -1
        ball.speed += ball.speed_increment * dt


def ball_collision_bricks(ball: Ball, bricks: list[Brick]) -> None:
    for brick in bricks:
        if brick.is_active:
            if p.check_collision_circle_rec(
                ball.center,
                ball.radius,
                p.Rectangle(brick.x, brick.y, BRICK_WIDTH, BRICK_HEIGHT),
            ):
                ball.direction.y *= -1
                brick.is_active = False


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    lives: int = 5
    game_over: bool = False
    game_win: bool = False

    bricks: list[Brick] = bricks_init()

    paddle: Paddle = Paddle()
    ball: Ball = Ball(paddle.rect)

    while not p.window_should_close():
        if not game_over and not game_win:
            dt: float = p.get_frame_time()

            paddle.update(dt)
            ball.update(dt, paddle.rect)

            ball_collision_paddle(ball, paddle, dt)
            ball_collision_bricks(ball, bricks)

            # update lives
            if ball.center.y > SCREEN_HEIGHT + ball.radius:
                lives -= 1
                paddle.reset()
                ball.reset(paddle.rect)

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                lives = 5
                game_over = False
                game_win = False

                paddle.reset()
                ball.reset(paddle.rect)

                for brick in bricks:
                    brick.is_active = True

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        paddle.draw()
        ball.draw()

        # draw lives
        p.draw_text(str(lives), 20, p.get_screen_height() - 50, 30, p.BLACK)

        for brick in bricks:
            if brick.is_active:
                brick.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
