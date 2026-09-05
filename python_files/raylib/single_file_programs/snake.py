from collections import deque
from enum import IntEnum, auto

import pyray as p

import utils

SCREEN_SIZE: int = 800
MARGIN: int = 100
GRID_SIZE: int = 20
BLOCK_SIZE: int = (SCREEN_SIZE - (MARGIN * 2)) // GRID_SIZE


def draw_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY

    for x in range(MARGIN, SCREEN_SIZE - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(x, MARGIN), p.Vector2(x, SCREEN_SIZE - MARGIN), thickness, color
        )

    for y in range(MARGIN, SCREEN_SIZE - MARGIN, BLOCK_SIZE):
        p.draw_line_ex(
            p.Vector2(MARGIN, y), p.Vector2(SCREEN_SIZE - MARGIN, y), thickness, color
        )

    # draw outer rect
    p.draw_rectangle_lines_ex(
        p.Rectangle(
            MARGIN, MARGIN, SCREEN_SIZE - (MARGIN * 2), SCREEN_SIZE - (MARGIN * 2)
        ),
        5.0,
        p.GRAY,
    )


class Direction(IntEnum):
    RIGHT = auto()
    LEFT = auto()
    UP = auto()
    DOWN = auto()


class Snake:
    def __init__(self) -> None:
        self.x: int = MARGIN
        self.y: int = MARGIN
        self.direction: Direction = Direction.RIGHT

        self.body: deque[tuple[int, int]] = deque()
        self.body.append((self.x, self.y))

        self.elapsed_time: float = 0.0
        self.move_interval: float = 0.09

    def handle_input(self) -> None:
        if p.is_key_pressed(p.KeyboardKey.KEY_A) and self.direction != Direction.RIGHT:
            self.direction = Direction.LEFT
        if p.is_key_pressed(p.KeyboardKey.KEY_D) and self.direction != Direction.LEFT:
            self.direction = Direction.RIGHT
        if p.is_key_pressed(p.KeyboardKey.KEY_W) and self.direction != Direction.DOWN:
            self.direction = Direction.UP
        if p.is_key_pressed(p.KeyboardKey.KEY_S) and self.direction != Direction.UP:
            self.direction = Direction.DOWN

    def move(self) -> None:
        match self.direction:
            case Direction.LEFT:
                self.x -= BLOCK_SIZE
            case Direction.RIGHT:
                self.x += BLOCK_SIZE
            case Direction.UP:
                self.y -= BLOCK_SIZE
            case Direction.DOWN:
                self.y += BLOCK_SIZE

    def check_collision_walls(self) -> bool:
        return (
            self.x < MARGIN
            or self.x > p.get_screen_width() - MARGIN - BLOCK_SIZE
            or self.y < MARGIN
            or self.y > p.get_screen_height() - MARGIN - BLOCK_SIZE
        )

    def check_collision_itself(self) -> bool:
        for segment in self.body:
            if self.x == segment[0] and self.y == segment[1]:
                return True

        return False

    def update(self, dt: float) -> bool:
        self.handle_input()

        self.elapsed_time += dt
        if self.elapsed_time >= self.move_interval:
            self.elapsed_time = 0.0

            self.move()

            if self.check_collision_itself() or self.check_collision_walls():
                return True

            self.body.appendleft((self.x, self.y))
            self.body.pop()

        return False

    def draw(self) -> None:
        for i, segment in enumerate(self.body):
            color: p.Color = p.BLUE if i == 0 else p.SKYBLUE
            p.draw_rectangle(segment[0], segment[1], BLOCK_SIZE, BLOCK_SIZE, color)


class Food:
    def gen_random_food(self) -> None:
        for _ in range(10000):
            snake_collision: bool = False
            random_x: int = p.get_random_value(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN
            random_y: int = p.get_random_value(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN

            for segment in self.snake.body:
                if segment[0] == random_x and segment[1] == random_y:
                    snake_collision = True
                    break

            if not snake_collision:
                self.x = random_x
                self.y = random_y
                return

    def __init__(self, snake: Snake) -> None:
        self.snake: Snake = snake
        self.x: int = 0
        self.y: int = 0
        self.color: p.Color = p.RED

        self.gen_random_food()

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE, self.color)


class GameManager:
    def reset(self) -> None:
        self.score: int = 0
        self.game_over: bool = False

        self.snake: Snake = Snake()
        self.food: Food = Food(self.snake)

    def __init__(self) -> None:
        self.reset()

    def update(self, dt: float) -> None:
        if not self.game_over:
            self.game_over = self.snake.update(dt)

            # snake vs food
            snake_head: tuple[int, int] = self.snake.body[0]
            if snake_head[0] == self.food.x and snake_head[1] == self.food.y:
                self.food.gen_random_food()
                self.snake.body.append(self.snake.body[-1])
                self.score += 1

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                self.reset()

    def draw(self) -> None:
        # draw score
        utils.draw_centered_text(
            utils.OriginType.TOP_LEFT,
            f"Score: {self.score}",
            p.Rectangle(0, 0, p.get_screen_width(), MARGIN),
        )

        self.snake.draw()
        self.food.draw()

        draw_grid()

        if self.game_over:
            width: float = 300.0
            height: float = 150.0
            rect: p.Rectangle = p.Rectangle(
                (p.get_screen_width() - width) / 2.0,
                (p.get_screen_height() - height) / 2.0,
                width,
                height,
            )
            text: str = "GAME OVER"

            utils.draw_centered_text(utils.OriginType.TOP_LEFT, text, rect, 30)
            utils.draw_centered_text(
                utils.OriginType.TOP_LEFT,
                "press ENTER to restart",
                p.Rectangle(0, 0, p.get_screen_width(), p.get_screen_height() + 200),
            )

            p.draw_rectangle_lines_ex(rect, 5.0, p.BLACK)


def main() -> None:
    p.init_window(SCREEN_SIZE, SCREEN_SIZE, "Snake")
    p.set_target_fps(60)

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
