import pyray as p
from center_and_draw_text import center_and_draw_text


SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "BREAKOUT"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY

ROWS: int = 5
COLS: int = 10
BRICK_WIDTH: int = 79
BRICK_HEIGHT: int = 30
BRICK_GAP: int = 2


class Brick:
    def __init__(self, x: int, y: int) -> None:
        self.x: int = x
        self.y: int = y
        self.color: p.Color = p.DARKGRAY

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BRICK_WIDTH, BRICK_HEIGHT, self.color)


class Paddle:
    def __init__(self) -> None:
        self.width: float = 100.0
        self.height: float = 10.0
        self.initial_x: float = p.get_screen_width()/2 - self.width/2
        self.initial_y: float = p.get_screen_height() - self.height * 2
        self.x: float = self.initial_x
        self.y: float = self.initial_y
        self.speed: float = 300.0
        self.color: p.Color = p.BLACK

    def reset(self) -> None:
        self.x = self.initial_x
        self.y = self.initial_y

    def draw(self) -> None:
        p.draw_rectangle_rec(p.Rectangle(
            self.x, self.y, self.width, self.height), self.color)

    def update(self) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_LEFT) and self.x > 0:
            self.x -= self.speed * p.get_frame_time()
        if p.is_key_down(p.KeyboardKey.KEY_RIGHT) and self.x < p.get_screen_width() - self.width:
            self.x += self.speed * p.get_frame_time()


class Ball:
    def __init__(self) -> None:
        self.initial_x: float = p.get_screen_width()/2
        self.initial_y: float = p.get_screen_height()/2
        self.x: float = self.initial_x
        self.y: float = self.initial_y
        self.radius: float = 10.0
        self.initial_speed: float = 300.0
        self.speed: float = self.initial_speed
        self.speed_increment: float = 10.0
        self.color: p.Color = p.RED
        self.is_active: bool = False

        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            1
        )

    def reset(self) -> None:
        self.x = self.initial_x
        self.y = self.initial_y
        self.speed = self.initial_speed
        self.is_active = False
        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            1
        )

    def draw(self) -> None:
        p.draw_circle_v(p.Vector2(self.x, self.y), self.radius, self.color)

    def update(self) -> None:
        # activate/deactivate ball
        if p.is_key_pressed(p.KeyboardKey.KEY_SPACE):
            self.is_active = not self.is_active

        # move ball
        if self.is_active:
            self.x += self.direction.x * self.speed * p.get_frame_time()
            self.y += self.direction.y * self.speed * p.get_frame_time()

        # normalize ball direction
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if self.x < self.radius or self.x > p.get_screen_width() - self.radius:
            self.direction.x *= -1
        if self.y < self.radius:
            self.direction.y *= -1


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    lives: int = 5
    game_over: bool = False
    game_won: bool = False

    bricks: list[Brick] = []
    for i in range(ROWS):
        for j in range(COLS):
            x: int = j * (BRICK_WIDTH + BRICK_GAP)
            y: int = i * (BRICK_HEIGHT + BRICK_GAP)

            brick: Brick = Brick(x, y)

            bricks.append(brick)

    paddle: Paddle = Paddle()
    ball: Ball = Ball()

    while not p.window_should_close():

        if len(bricks) <= 0:
            game_won = True

        if lives <= 0:
            game_over = True

        if not game_over and not game_won:
            paddle.update()
            ball.update()

            # ball collision paddle
            if p.check_collision_circle_rec(p.Vector2(ball.x, ball.y), ball.radius, p.Rectangle(paddle.x, paddle.y, paddle.width, paddle.height)):
                ball.direction.y *= -1
                ball.speed += ball.speed_increment

            # ball collision bricks
            for brick in bricks[:]:
                if p.check_collision_circle_rec(p.Vector2(ball.x, ball.y), ball.radius, p.Rectangle(brick.x, brick.y, BRICK_WIDTH, BRICK_HEIGHT)):
                    ball.direction.y *= -1
                    bricks.remove(brick)

            # update lives
            if ball.y > p.get_screen_height() + ball.radius:
                lives -= 1
                ball.reset()
                paddle.reset()

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                lives = 5
                game_over = False
                game_won = False

                for i in range(ROWS):
                    for j in range(COLS):
                        x = j * (BRICK_WIDTH + BRICK_GAP)
                        y = i * (BRICK_HEIGHT + BRICK_GAP)

                        brick = Brick(x, y)

                        bricks.append(brick)

                paddle = Paddle()
                ball = Ball()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw lives
        p.draw_text(str(lives), 20, p.get_screen_height() - 50, 40, p.DARKGRAY)

        if not game_over and not game_won:
            paddle.draw()
            ball.draw()

            for brick in bricks:
                brick.draw()

        if game_over:
            center_and_draw_text("GAME OVER", 40, p.Rectangle(
                0, 0, p.get_screen_width(), p.get_screen_height()), p.DARKGRAY)
            center_and_draw_text("press ENTER to restart", 30, p.Rectangle(
                0, 0, p.get_screen_width(), p.get_screen_height() + 100), p.DARKGRAY)
        if game_won:
            center_and_draw_text("YOU WIN", 40, p.Rectangle(
                0, 0, p.get_screen_width(), p.get_screen_height()), p.DARKGRAY)
            center_and_draw_text("press ENTER to restart", 30, p.Rectangle(
                0, 0, p.get_screen_width(), p.get_screen_height() + 100), p.DARKGRAY)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
