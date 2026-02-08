from random import randint

import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "Breakout"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE

ROWS: int = 8
COLS: int = 10
MARGIN: float = 10.0

BRICK_HEIGHT: float = 25.0
BRICK_GAP: float = 2.0


def get_brick_width() -> float:
    # horizontal
    total_gaps: float = BRICK_GAP * (COLS - 1)
    total_margin: float = MARGIN * 2
    usable_screen_width: float = (
        p.get_screen_width() - total_margin - total_gaps
    )

    return usable_screen_width / COLS


class Brick:
    def __init__(self, x: float, y: float) -> None:
        brick_width: float = get_brick_width()
        self.rect: p.Rectangle = p.Rectangle(x, y, brick_width, BRICK_HEIGHT)
        self.color: p.Color = p.GRAY

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class Paddle:
    def __init__(self) -> None:
        width: float = 100.0
        height: float = 10.0
        x: float = SCREEN_WIDTH / 2.0 - width / 2.0
        y: float = SCREEN_HEIGHT - height - 10.0

        self.rect: p.Rectangle = p.Rectangle(x, y, width, height)
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.rect.x = SCREEN_WIDTH / 2.0 - self.rect.width / 2.0

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
            paddle_rect.y - self.radius - 10.0,
        )
        self.speed_initial: float = 400.0
        self.speed: float = self.speed_initial
        self.speed_increment: float = 10.0
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1, -1
        )
        self.color: p.Color = p.RED
        self.active: bool = False

    def reset(self, paddle_rect: p.Rectangle) -> None:
        self.center: p.Vector2 = p.Vector2(
            paddle_rect.x + paddle_rect.width / 2.0,
            paddle_rect.y - self.radius - 10.0,
        )
        self.speed: float = self.speed_initial
        self.direction: p.Vector2 = p.Vector2(
            -1 if randint(0, 1) == 0 else 1, -1
        )
        self.active: bool = False

    def draw(self) -> None:
        p.draw_circle_v(self.center, self.radius, self.color)

    def update(self, dt: float, paddle_rect: p.Rectangle) -> None:
        # update when inactive
        if not self.active:
            self.center: p.Vector2 = p.Vector2(
                paddle_rect.x + paddle_rect.width / 2.0,
                paddle_rect.y - self.radius - 10.0,
            )

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
                self.center.x < self.radius
                or self.center.x > SCREEN_WIDTH - self.radius
            ):
                self.direction.x *= -1
            if self.center.y < self.radius:
                self.direction.y *= -1


class GameManager:
    def reset(self) -> None:
        self.lives: int = 5
        self.game_over: bool = False
        self.game_won: bool = False

        self.paddle: Paddle = Paddle()
        self.ball: Ball = Ball(self.paddle.rect)

        self.bricks: list[Brick] = []
        brick_width: float = get_brick_width()

        for i in range(ROWS):
            for j in range(COLS):
                x: float = j * (brick_width + BRICK_GAP) + MARGIN
                y: float = i * (BRICK_HEIGHT + BRICK_GAP) + MARGIN

                self.bricks.append(Brick(x, y))

    def __init__(self) -> None:
        self.reset()

    def draw_game_status(self) -> None:
        if self.game_over:
            text: str = "GAME OVER"
        elif self.game_won:
            text: str = "YOU WIN"

        # outline rect
        width: float = 300.0
        height: float = 150.0
        x: float = SCREEN_WIDTH / 2.0 - width / 2.0
        y: float = SCREEN_HEIGHT / 2.0 - height / 2.0
        rect: p.Rectangle = p.Rectangle(x, y, width, height)
        thickness: float = 5.0
        color: p.Color = p.DARKGRAY

        p.draw_rectangle_lines_ex(rect, thickness, color)

        center_and_draw_text(text, rect)

    def draw(self) -> None:
        p.draw_text(str(self.lives), 20, SCREEN_HEIGHT - 50, 30, p.BLACK)

        self.paddle.draw()
        self.ball.draw()
        for brick in self.bricks:
            brick.draw()

        if self.game_over or self.game_won:
            self.draw_game_status()

    def ball_collision_paddle(self, dt: float) -> None:
        if p.check_collision_circle_rec(
            self.ball.center, self.ball.radius, self.paddle.rect
        ):
            self.ball.direction.y *= -1
            self.ball.speed += self.ball.speed_increment * dt

    def update_lives(self) -> None:
        if self.ball.center.y > SCREEN_HEIGHT + self.ball.radius:
            self.lives -= 1
            self.paddle.reset()
            self.ball.reset(self.paddle.rect)

    def ball_collision_bricks(self) -> None:
        for brick in self.bricks:
            if p.check_collision_circle_rec(
                self.ball.center, self.ball.radius, brick.rect
            ):
                self.ball.direction.y *= -1
                self.bricks.remove(brick)
                break

    def update(self, dt: float) -> None:
        if self.lives <= 0:
            self.game_over = True

        if len(self.bricks) <= 0:
            self.game_won = True

        if not self.game_over and not self.game_won:
            self.paddle.update(dt)
            self.ball.update(dt, self.paddle.rect)

            self.ball_collision_paddle(dt)
            self.update_lives()
            self.ball_collision_bricks()
        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
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
