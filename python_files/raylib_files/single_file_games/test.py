import random

import pyray as pr

# -----------------------
# Constants
# -----------------------

ROWS = 15
COLS = 20

TILE_SIZE = 32

TOP = 0
RIGHT = 1
BOTTOM = 2
LEFT = 3

MAP_WIDTH = COLS * 2 + 1
MAP_HEIGHT = ROWS * 2 + 1

SCREEN_WIDTH = MAP_WIDTH * TILE_SIZE
SCREEN_HEIGHT = MAP_HEIGHT * TILE_SIZE


# -----------------------
# Cell
# -----------------------


class Cell:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.visited = False

        # top, right, bottom, left
        self.walls = [True, True, True, True]


# -----------------------
# Create Grid
# -----------------------

grid = [[Cell(r, c) for c in range(COLS)] for r in range(ROWS)]


# -----------------------
# Get Unvisited Neighbors
# -----------------------


def get_unvisited_neighbors(cell):

    neighbors = []

    r = cell.row
    c = cell.col

    if r > 0:
        n = grid[r - 1][c]
        if not n.visited:
            neighbors.append((n, TOP))

    if c < COLS - 1:
        n = grid[r][c + 1]
        if not n.visited:
            neighbors.append((n, RIGHT))

    if r < ROWS - 1:
        n = grid[r + 1][c]
        if not n.visited:
            neighbors.append((n, BOTTOM))

    if c > 0:
        n = grid[r][c - 1]
        if not n.visited:
            neighbors.append((n, LEFT))

    return neighbors


# -----------------------
# Remove Wall
# -----------------------


def remove_wall(current, neighbor, direction):

    if direction == TOP:
        current.walls[TOP] = False
        neighbor.walls[BOTTOM] = False

    elif direction == RIGHT:
        current.walls[RIGHT] = False
        neighbor.walls[LEFT] = False

    elif direction == BOTTOM:
        current.walls[BOTTOM] = False
        neighbor.walls[TOP] = False

    elif direction == LEFT:
        current.walls[LEFT] = False
        neighbor.walls[RIGHT] = False


# -----------------------
# Generate Maze
# -----------------------

stack = []

current = grid[0][0]
current.visited = True

while True:
    neighbors = get_unvisited_neighbors(current)

    if neighbors:
        neighbor, direction = random.choice(neighbors)

        stack.append(current)

        remove_wall(current, neighbor, direction)

        neighbor.visited = True
        current = neighbor

    elif stack:
        current = stack.pop()

    else:
        break


# -----------------------
# Build Tile Map
# -----------------------

# 1 = wall
# 0 = floor

tiles = [[1 for _ in range(MAP_WIDTH)] for _ in range(MAP_HEIGHT)]

for row in grid:
    for cell in row:
        tx = cell.col * 2 + 1
        ty = cell.row * 2 + 1

        tiles[ty][tx] = 0

        if not cell.walls[TOP]:
            tiles[ty - 1][tx] = 0

        if not cell.walls[RIGHT]:
            tiles[ty][tx + 1] = 0

        if not cell.walls[BOTTOM]:
            tiles[ty + 1][tx] = 0

        if not cell.walls[LEFT]:
            tiles[ty][tx - 1] = 0


# Entrance
tiles[1][0] = 0

# Exit
tiles[MAP_HEIGHT - 2][MAP_WIDTH - 1] = 0


# -----------------------
# Draw
# -----------------------

pr.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generator")

pr.set_target_fps(60)

while not pr.window_should_close():
    pr.begin_drawing()

    pr.clear_background(pr.BLACK)

    for y in range(MAP_HEIGHT):
        for x in range(MAP_WIDTH):
            color = pr.DARKGRAY if tiles[y][x] == 0 else pr.GRAY

            pr.draw_rectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color)

    pr.end_drawing()

pr.close_window()
