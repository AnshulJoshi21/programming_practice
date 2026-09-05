import random

import pyray as p

import utils

SCREEN_WIDTH: int = 1280
SCREEN_HEIGHT: int = 720

BRICK_ROWS: int = 5
BRICK_COLS: int = 10
BRICK_HEIGHT: float = 30.0
BRICK_GAP: float = 5.0
BRICK_MARGIN: float = 50.0


def get_brick_width() -> float:
    available_width = (
        p.get_screen_width() - (BRICK_MARGIN * 2) - (BRICK_GAP * (BRICK_COLS - 1))
    )

    return available_width / BRICK_COLS


class Brick:
    def __init__(self, x: float, y: float) -> None:
        self.rect: p.Rectangle = p.Rectangle(x, y, get_brick_width(), BRICK_HEIGHT)
        self.color: p.Color = p.GRAY

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class BrickManager:
    def __init__(self) -> None:
        self.bricks: list[Brick] = []

        brick_width: float = get_brick_width()

        for i in range(BRICK_ROWS):
            for j in range(BRICK_COLS):
                x: float = j * (brick_width + BRICK_GAP) + BRICK_MARGIN
                y: float = i * (BRICK_HEIGHT + BRICK_GAP) + BRICK_MARGIN

                self.bricks.append(Brick(x, y))

    def draw(self) -> None:
        for brick in self.bricks:
            brick.draw()


class Paddle:
    def reset(self) -> None:
        self.rect.x = (p.get_screen_width() - self.rect.width) / 2.0

    def __init__(self) -> None:
        width: float = 100.0
        height: float = 15.0
        self.rect: p.Rectangle = p.Rectangle(
            0, p.get_render_height() - (height * 2), width, height
        )

        self.color: p.Color = p.BLACK
        self.speed: float = 300.0

        self.reset()

    def update(self, dt: float) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_A) and self.rect.x > 0:
            self.rect.x -= self.speed * dt

        if (
            p.is_key_down(p.KeyboardKey.KEY_D)
            and self.rect.x < p.get_screen_width() - self.rect.width
        ):
            self.rect.x += self.speed * dt

    def draw(self) -> None:
        p.draw_rectangle_rec(self.rect, self.color)


class Ball:
    def update_pos(self) -> None:
        self.center = p.Vector2(
            self.paddle.rect.x + self.paddle.rect.width / 2.0,
            self.paddle.rect.y - (self.radius * 2),
        )

    def reset(self) -> None:
        self.update_pos()
        self.speed: float = 400.0
        self.direction: p.Vector2 = p.Vector2(random.choice([-1, 1]), -1)
        self.active: bool = False

    def __init__(self, paddle: Paddle) -> None:
        self.paddle: Paddle = paddle

        self.radius: float = 10.0
        self.color: p.Color = p.RED
        self.speed_increment: float = 10.0

        self.reset()

    def update(self, dt: float) -> None:
        if not self.active:
            self.update_pos()

        # activate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.active = True

        if self.active:
            self.direction = p.vector2_normalize(self.direction)

            # move
            self.center.x += self.direction.x * self.speed * dt
            self.center.y += self.direction.y * self.speed * dt

            # set bounds
            if self.center.x < self.radius:
                self.center.x = self.radius
                self.direction.x *= -1

            if self.center.x > p.get_screen_width() - self.radius:
                self.center.x = p.get_screen_width() - self.radius
                self.direction.x *= -1

            if self.center.y < self.radius:
                self.center.y = self.radius
                self.direction.y *= -1

    def draw(self) -> None:

        p.draw_circle_v(self.center, self.radius, self.color)


class GameManager:
    def reset(self) -> None:
        self.lives: int = 1
        self.game_over: bool = False
        self.game_won: bool = False

        self.brick_manager: BrickManager = BrickManager()
        self.paddle: Paddle = Paddle()
        self.ball: Ball = Ball(self.paddle)

    def __init__(self) -> None:
        self.reset()

    def update(self, dt: float) -> None:
        if len(self.brick_manager.bricks) == 0:
            self.game_won = True

        if self.lives == 0:
            self.game_over = True

        if not self.game_over and not self.game_won:
            self.paddle.update(dt)
            self.ball.update(dt)

            # collisions
            # self.ball vs self.paddle

            if p.check_collision_circle_rec(
                self.ball.center, self.ball.radius, self.paddle.rect
            ):
                self.ball.direction.y *= -1
                self.ball.speed += self.ball.speed_increment * dt

            # bricks vs self.ball
            for brick in self.brick_manager.bricks:
                if p.check_collision_circle_rec(
                    self.ball.center, self.ball.radius, brick.rect
                ):
                    self.ball.direction.y *= -1
                    self.brick_manager.bricks.remove(brick)
                    break

            # update self.lives
            if self.ball.center.y > p.get_screen_height() + self.ball.radius:
                self.lives -= 1
                self.paddle.reset()
                self.ball.reset()

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                self.reset()

    def draw(self) -> None:
        # draw lives
        p.draw_text(str(self.lives), 20, p.get_screen_height() - 50, 30, p.BLACK)

        self.brick_manager.draw()

        if not self.ball.active and not self.game_over and not self.game_won:
            utils.draw_centered_text(
                utils.OriginType.TOP_LEFT,
                "press SPACE to begin",
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height() + 200),
                20,
            )

        self.ball.draw()
        self.paddle.draw()

        if self.game_over or self.game_won:
            width: float = 300.0
            height: float = 150.0
            rect: p.Rectangle = p.Rectangle(
                (p.get_screen_width() - width) / 2.0,
                (p.get_screen_height() - height) / 2.0,
                width,
                height,
            )

            text: str = "GAME OVER" if self.game_over else "YOU WIN"

            utils.draw_centered_text(utils.OriginType.TOP_LEFT, text, rect, 30)
            utils.draw_centered_text(
                utils.OriginType.TOP_LEFT,
                "press ENTER to restart",
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height() + 200),
            )

            p.draw_rectangle_lines_ex(rect, 5.0, p.BLACK)


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout")

    game_manager: GameManager = GameManager()

    while not p.window_should_close():
        dt: float = p.get_frame_time()

        game_manager.update(dt)

        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        game_manager.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
