from collections import deque
from dataclasses import dataclass
from enum import Enum
from random import randint

import pyray as p
from center_and_draw_text import center_and_draw_text

SCREEN_SIZE: int = 600
SCREEN_TITLE: str = "Snake"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

GRID_SIZE: int = 20
MARGIN: int = 50
BLOCK_SIZE: int = (SCREEN_SIZE - MARGIN * 2) // GRID_SIZE


@dataclass
class Point:
    x: int
    y: int


class Direction(Enum):
    RIGHT = 0
    LEFT = 1
    UP = 2
    DOWN = 3


class Snake:
    def __init__(self) -> None:
        self.x: int = MARGIN
        self.y: int = MARGIN
        self.direction: Direction = Direction.RIGHT
        self.body: deque[Point] = deque([Point(self.x, self.y)])

        self.last_time: float = p.get_time()
        self.move_interval: float = 0.09

    def draw(self) -> None:
        for i, segment in enumerate(self.body):
            color: p.Color = p.BLUE if i == 0 else p.SKYBLUE

            p.draw_rectangle(
                segment.x, segment.y, BLOCK_SIZE, BLOCK_SIZE, color
            )

    def handle_input(self) -> None:
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_A)
            and self.direction != Direction.RIGHT
        ):
            self.direction = Direction.LEFT
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_D)
            and self.direction != Direction.LEFT
        ):
            self.direction = Direction.RIGHT
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_W)
            and self.direction != Direction.DOWN
        ):
            self.direction = Direction.UP
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_S)
            and self.direction != Direction.UP
        ):
            self.direction = Direction.DOWN

    def move(self) -> None:
        match self.direction:
            case Direction.RIGHT:
                self.x += BLOCK_SIZE
            case Direction.LEFT:
                self.x -= BLOCK_SIZE
            case Direction.UP:
                self.y -= BLOCK_SIZE
            case Direction.DOWN:
                self.y += BLOCK_SIZE

    def check_collision_walls(self) -> bool:
        return (
            self.x < MARGIN
            or self.x + BLOCK_SIZE > SCREEN_SIZE - MARGIN
            or self.y < MARGIN
            or self.y + BLOCK_SIZE > SCREEN_SIZE - MARGIN
        )

    def check_collision_itself(self) -> bool:
        for segment in self.body:
            if segment.x == self.x and segment.y == self.y:
                return True

        return False

    def update(self) -> bool:
        self.handle_input()

        current_time: float = p.get_time()
        if current_time - self.last_time >= self.move_interval:
            self.last_time = current_time

            self.move()

            if self.check_collision_itself() or self.check_collision_walls():
                return True

            self.body.appendleft(Point(self.x, self.y))
            self.body.pop()

        return False


class Food:
    def gen_random_food(self, snake_body: deque[Point]) -> None:
        max_tries: int = 10000
        for _ in range(max_tries):
            food_collision_body: bool = False

            x: int = randint(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN
            y: int = randint(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN

            for segment in snake_body:
                if segment.x == x and segment.y == y:
                    food_collision_body = True
                    break

            if not food_collision_body:
                self.x: int = x
                self.y: int = y
                break

    def __init__(self, snake_body: deque[Point]) -> None:
        self.color: p.Color = p.RED
        self.gen_random_food(snake_body)

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE, self.color)


class GameManager:
    def reset(self) -> None:
        self.score: int = 0
        self.game_over: bool = False

        self.snake: Snake = Snake()
        self.food: Food = Food(self.snake.body)

    def __init__(self) -> None:
        self.reset()

    def draw_game_status(self) -> None:
        text: str = "GAME OVER"

        # outline rect
        width: float = 300.0
        height: float = 150.0
        x: float = SCREEN_SIZE / 2.0 - width / 2.0
        y: float = SCREEN_SIZE / 2.0 - height / 2.0
        rect: p.Rectangle = p.Rectangle(x, y, width, height)
        thickness: float = 5.0
        color: p.Color = p.DARKGRAY

        p.draw_rectangle_lines_ex(rect, thickness, color)

        center_and_draw_text(text, rect)

    def draw_grid(self) -> None:
        color: p.Color = p.LIGHTGRAY
        thickness: float = 2.0

        # vertical lines
        for x in range(MARGIN + BLOCK_SIZE, SCREEN_SIZE - MARGIN, BLOCK_SIZE):
            p.draw_line_ex(
                p.Vector2(x, MARGIN),
                p.Vector2(x, SCREEN_SIZE - MARGIN),
                thickness,
                color,
            )

        # horizontal lines
        for y in range(MARGIN + BLOCK_SIZE, SCREEN_SIZE - MARGIN, BLOCK_SIZE):
            p.draw_line_ex(
                p.Vector2(MARGIN, y),
                p.Vector2(SCREEN_SIZE - MARGIN, y),
                thickness,
                color,
            )

        # draw outline rect
        thickness = 5.0
        color = p.GRAY
        rect: p.Rectangle = p.Rectangle(
            MARGIN, MARGIN, SCREEN_SIZE - MARGIN * 2, SCREEN_SIZE - MARGIN * 2
        )
        p.draw_rectangle_lines_ex(rect, thickness, color)

    def draw(self) -> None:
        self.snake.draw()
        self.food.draw()

        self.draw_grid()

        center_and_draw_text(
            f"Score: {self.score}",
            p.Rectangle(0, 0, SCREEN_SIZE, MARGIN + 20),
            20.0,
        )

        if self.game_over:
            self.draw_game_status()

    def update(self, dt: float) -> None:
        if not self.game_over:
            self.game_over = self.snake.update()

            # snake eating food
            if (
                self.snake.body[0].x == self.food.x
                and self.snake.body[0].y == self.food.y
            ):
                self.score += 1
                self.snake.body.append(self.snake.body[-1])
                self.food.gen_random_food(self.snake.body)

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                self.reset()


def main() -> None:
    p.init_window(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

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
