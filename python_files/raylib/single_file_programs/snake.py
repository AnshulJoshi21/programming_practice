from dataclasses import dataclass
from enum import Enum
from random import randint

import pyray as p
from utils import center_and_draw_text

SCREEN_SIZE: int = 600
SCREEN_TITLE: str = "Snake"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

GRID_SIZE: int = 20
MARGIN: int = 50
BLOCK_SIZE: int = (SCREEN_SIZE - MARGIN * 2) // GRID_SIZE


def draw_background_grid() -> None:
    thickness: float = 2.0
    color: p.Color = p.LIGHTGRAY

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

    # outline rect
    rect: p.Rectangle = p.Rectangle(
        MARGIN, MARGIN, SCREEN_SIZE - MARGIN * 2, SCREEN_SIZE - MARGIN * 2
    )
    color = p.GRAY
    thickness = 3.0

    p.draw_rectangle_lines_ex(rect, thickness, color)


class Direction(Enum):
    RIGHT = 0
    LEFT = 1
    UP = 2
    DOWN = 3


@dataclass
class Point:
    x: int
    y: int


class Snake:
    def __init__(self) -> None:
        self.x: int = MARGIN
        self.y: int = MARGIN
        self.direction: Direction = Direction.RIGHT
        self.body: list[Point] = [Point(self.x, self.y)]

        self.start_time: float = 0.0
        self.move_interval: float = 0.09

    def draw(self) -> None:
        for i, segment in enumerate(self.body):
            color: p.Color = p.BLUE if i == 0 else p.SKYBLUE

            p.draw_rectangle(
                segment.x, segment.y, BLOCK_SIZE, BLOCK_SIZE, color
            )

    def handle_input(self) -> None:
        if (
            p.is_key_pressed(p.KeyboardKey.KEY_D)
            and self.direction != Direction.LEFT
        ):
            self.direction = Direction.RIGHT

        if (
            p.is_key_pressed(p.KeyboardKey.KEY_A)
            and self.direction != Direction.RIGHT
        ):
            self.direction = Direction.LEFT

        if (
            p.is_key_pressed(p.KeyboardKey.KEY_S)
            and self.direction != Direction.UP
        ):
            self.direction = Direction.DOWN

        if (
            p.is_key_pressed(p.KeyboardKey.KEY_W)
            and self.direction != Direction.DOWN
        ):
            self.direction = Direction.UP

    def move(self) -> None:
        match self.direction:
            case Direction.RIGHT:
                self.x += BLOCK_SIZE
            case Direction.LEFT:
                self.x -= BLOCK_SIZE
            case Direction.DOWN:
                self.y += BLOCK_SIZE
            case Direction.UP:
                self.y -= BLOCK_SIZE

    def collision_itself(self) -> bool:
        for segment in self.body:
            if self.x == segment.x and self.y == segment.y:
                return True

        return False

    def collision_walls(self) -> bool:
        return (
            self.x < MARGIN
            or self.x > p.get_screen_width() - MARGIN - BLOCK_SIZE
            or self.y < MARGIN
            or self.y > p.get_screen_height() - MARGIN - BLOCK_SIZE
        )

    def update(self) -> bool:
        self.handle_input()

        current_time: float = p.get_time()
        if current_time - self.start_time >= self.move_interval:
            self.start_time = current_time

            self.move()

            if self.collision_itself() or self.collision_walls():
                return True

            self.body.insert(0, Point(self.x, self.y))
            self.body.pop()

        return False


class Food:
    def gen_random_food(self, snake_body: list[Point]) -> None:
        max_tries: int = 1000

        for _ in range(max_tries):
            point_inside_body: bool = False

            x: int = randint(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN
            y: int = randint(0, GRID_SIZE - 1) * BLOCK_SIZE + MARGIN

            for segment in snake_body:
                if x == segment.x and y == segment.y:
                    point_inside_body = True
                    break

            if not point_inside_body:
                self.x: int = x
                self.y: int = y
                break

    def __init__(self, snake_body: list[Point]) -> None:
        self.gen_random_food(snake_body)
        self.color: p.Color = p.RED

    def draw(self) -> None:
        p.draw_rectangle(self.x, self.y, BLOCK_SIZE, BLOCK_SIZE, self.color)


def snake_eating_food(snake: Snake, food: Food, score: int) -> int:
    if snake.body[0].x == food.x and snake.body[0].y == food.y:
        score += 1
        food.gen_random_food(snake.body)
        snake.body.append(snake.body[-1])

    return score


def main() -> None:
    p.init_window(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE)
    p.set_target_fps(GAME_FPS)

    score: int = 0
    game_over: bool = False

    snake: Snake = Snake()
    food: Food = Food(snake.body)

    while not p.window_should_close():
        if not game_over:
            game_over = snake.update()

            score = snake_eating_food(snake, food, score)

        else:
            if p.is_key_pressed(p.KeyboardKey.KEY_ENTER):
                score = 0
                game_over = False

                snake = Snake()
                food = Food(snake.body)

        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        center_and_draw_text(
            f"Score: {score}",
            20.0,
            2.0,
            p.Rectangle(0, 0, p.get_screen_width(), 60),
            p.DARKGRAY,
        )

        snake.draw()
        food.draw()

        draw_background_grid()

        if game_over:
            width: float = 300.0
            height: float = 150.0
            x: float = p.get_screen_width() / 2.0 - width / 2.0
            y: float = p.get_screen_height() / 2.0 - height / 2.0

            rect: p.Rectangle = p.Rectangle(x, y, width, height)
            color: p.Color = p.BLACK
            thickness: float = 5.0

            # draw outline rect
            p.draw_rectangle_lines_ex(rect, thickness, color)

            # draw centered text
            center_and_draw_text("GAME OVER", 40.0, 2.0, rect, color)

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
