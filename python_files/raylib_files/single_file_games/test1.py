import random

import pyray as p

TILE_SIZE: int = 16
ROWS: int = 20
COLS: int = 20

MAP_WIDTH: int = ROWS * 2 + 1
MAP_HEIGHT: int = COLS * 2 + 1

BASE_WIDTH: int = MAP_WIDTH * TILE_SIZE
BASE_HEIGHT: int = MAP_HEIGHT * TILE_SIZE

TOP: int = 0
RIGHT: int = 1
BOTTOM: int = 2
LEFT: int = 3


class Cell:
    def __init__(self, row: int, col: int) -> None:
        self.row: int = row
        self.col: int = col
        self.visited: bool = False

        # top, right, bottom, left
        self.walls: list[bool] = [True, True, True, True]


grid: list[list[Cell]] = [[Cell(r, c) for c in range(COLS)] for r in range(ROWS)]


def get_unvisited_neighbours(cell: Cell) -> list[tuple[Cell, int]]:
    neighbours: list[tuple[Cell, int]] = []

    row: int = cell.row
    col: int = cell.col

    if row > 0:
        top: Cell = grid[row - 1][col]
        if not top.visited:
            neighbours.append((top, TOP))

    if col < COLS - 1:
        right: Cell = grid[row][col + 1]
        if not right.visited:
            neighbours.append((right, RIGHT))

    if row < ROWS - 1:
        bottom: Cell = grid[row + 1][col]
        if not bottom.visited:
            neighbours.append((bottom, BOTTOM))

    if col > 0:
        left: Cell = grid[row][col - 1]
        if not left.visited:
            neighbours.append((left, LEFT))

    return neighbours


def remove_wall(current: Cell, neighbour: Cell, direction: int) -> None:
    if direction == TOP:
        current.walls[TOP] = False
        neighbour.walls[BOTTOM] = False

    if direction == RIGHT:
        current.walls[RIGHT] = False
        neighbour.walls[LEFT] = False

    if direction == BOTTOM:
        current.walls[BOTTOM] = False
        neighbour.walls[TOP] = False

    if direction == LEFT:
        current.walls[LEFT] = False
        neighbour.walls[RIGHT] = False


stack: list[Cell] = []
current: Cell = grid[0][0]
current.visited = True

while True:
    neighbours: list[tuple[Cell, int]] = get_unvisited_neighbours(current)
    if neighbours:
        stack.append(current)
        neighbour: Cell
        direction: int
        neighbour, direction = random.choice(neighbours)
        remove_wall(current, neighbour, direction)

        neighbour.visited = True
        current = neighbour

    elif stack:
        current = stack.pop()

    else:
        break


# wall = 1
# floor = 0
tiles: list[list[int]] = [[1 for _ in range(MAP_WIDTH)] for _ in range(MAP_HEIGHT)]

for row in grid:
    for cell in row:
        tx: int = cell.col * 2 + 1
        ty: int = cell.row * 2 + 1

        tiles[tx][ty] = 0

        if not cell.walls[TOP]:
            tiles[tx][ty - 1] = 0

        if not cell.walls[RIGHT]:
            tiles[tx + 1][ty] = 0

        if not cell.walls[BOTTOM]:
            tiles[tx][ty + 1] = 0

        if not cell.walls[LEFT]:
            tiles[tx - 1][ty] = 0

# entrance
tiles[1][0] = 0

# exit
tiles[MAP_HEIGHT - 1][MAP_WIDTH - 2] = 0


def main() -> None:
    p.init_window(BASE_WIDTH, BASE_HEIGHT, "Backtracking Maze Gen")
    p.set_target_fps(60)

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(p.RAYWHITE)

        for y in range(MAP_HEIGHT):
            for x in range(MAP_WIDTH):
                color: p.Color = p.LIGHTGRAY if tiles[y][x] == 0 else p.BLACK

                p.draw_rectangle(
                    x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color
                )

        p.end_drawing()

    p.close_window()


if __name__ == "__main__":
    main()
