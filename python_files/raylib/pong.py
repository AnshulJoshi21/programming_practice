import pyray as p

SCREEN_WIDTH: int = 800
SCREEN_HEIGHT: int = 600
SCREEN_TITLE: str = "PONG"
SCREEN_BACKGROUND: p.Color = p.LIGHTGRAY


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
        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )
        self.color: p.Color = p.RED
        self.is_active: bool = False

    def reset(self) -> None:
        self.x = self.initial_x
        self.y = self.initial_y
        self.speed = self.initial_speed
        self.direction = p.Vector2(
            -1 if p.get_random_value(0, 1) == 0 else 1,
            -1 if p.get_random_value(0, 1) == 0 else 1,
        )
        self.is_active = False

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

        # normalize direction vector
        if self.direction.x != 0 and self.direction.y != 0:
            self.direction = p.vector2_normalize(self.direction)

        # ball bounds
        if self.y < self.radius or self.y > p.get_screen_height() - self.radius:
            self.direction.y *= -1


class Paddle:
    def __init__(self, x: float) -> None:
        self.width: float = 10.0
        self.height: float = 100.0
        self.initial_x: float = x
        self.initial_y: float = p.get_screen_height()/2 - self.height/2
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

    def update_player(self) -> None:
        if p.is_key_down(p.KeyboardKey.KEY_UP) and self.y > 0:
            self.y -= self.speed * p.get_frame_time()
        if p.is_key_down(p.KeyboardKey.KEY_DOWN) and self.y < p.get_screen_height() - self.height:
            self.y += self.speed * p.get_frame_time()

    def update_ai(self, ball_y: float) -> None:
        if ball_y < self.y + self.height/2 and self.y > 0:
            self.y -= self.speed * p.get_frame_time()
        if ball_y > self.y + self.height/2 and self.y < p.get_screen_height() - self.height:
            self.y += self.speed * p.get_frame_time()


def main() -> None:
    p.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE)

    score_left: int = 0
    score_right: int = 0

    ball: Ball = Ball()
    player: Paddle = Paddle(10.0)
    ai: Paddle = Paddle(p.get_screen_width() - player.width - 10.0)

    while not p.window_should_close():

        ball.update()
        player.update_player()
        ai.update_ai(ball.y)

        # ball collision  paddle
        if p.check_collision_circle_rec(p.Vector2(ball.x, ball.y), ball.radius, p.Rectangle(player.x, player.y, player.width, player.height)):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment
        if p.check_collision_circle_rec(p.Vector2(ball.x, ball.y), ball.radius, p.Rectangle(ai.x, ai.y, ai.width, ai.height)):
            ball.direction.x *= -1
            ball.speed += ball.speed_increment

        # update scores
        if ball.x < ball.radius:
            score_right += 1
            ball.reset()
            player.reset()
            ai.reset()
        if ball.x > p.get_screen_width() - ball.radius:
            score_left += 1
            ball.reset()
            player.reset()
            ai.reset()

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        # draw scores
        p.draw_text(str(score_left), 200, 30, 40, p.DARKGRAY)
        p.draw_text(str(score_right), p.get_screen_width() -
                    200, 30, 40, p.DARKGRAY)

        ball.draw()
        player.draw()
        ai.draw()

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
