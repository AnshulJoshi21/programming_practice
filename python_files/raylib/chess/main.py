import pyray as p

SCREEN_SIZE: int = 800
SCREEN_TITLE: str = "CHESS"
SCREEN_BACKGROUND: p.Color = p.RAYWHITE
GAME_FPS: int = 60

BOARD_SIZE: int = 8
TILE_SIZE: int = SCREEN_SIZE // BOARD_SIZE

RECTANGLE_OUTLINE_THICKNESS: float = 10.0


def draw_board() -> None:
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            x: int = j * TILE_SIZE
            y: int = i * TILE_SIZE

            color: p.Color = p.LIGHTGRAY if (i + j) % 2 == 0 else p.DARKGRAY

            p.draw_rectangle(x, y, TILE_SIZE, TILE_SIZE, color)


def draw_pieces(
    board_pieces: list[list[str]],
    loaded_textures_array: dict[str, p.Texture],
    padding: int,
) -> None:
    for row in range(BOARD_SIZE):
        for col in range(BOARD_SIZE):
            if board_pieces[row][col] != "_":
                current_piece: str = board_pieces[row][col]

                current_texture: p.Texture = loaded_textures_array[current_piece]
                source: p.Rectangle = p.Rectangle(
                    0, 0, current_texture.width, current_texture.height
                )
                dest: p.Rectangle = p.Rectangle(
                    col * TILE_SIZE + padding,
                    row * TILE_SIZE + padding,
                    TILE_SIZE - padding * 2,
                    TILE_SIZE - padding * 2,
                )
                origin: p.Vector2 = p.Vector2(0, 0)
                rotation: float = 0.0
                tint: p.Color = p.WHITE

                p.draw_texture_pro(
                    current_texture, source, dest, origin, rotation, tint
                )


def drag_and_drop_piece(
    board_pieces: list[list[str]],
    loaded_textures_array: dict[str, p.Texture],
    padding: int,
) -> None:
    if not hasattr(drag_and_drop_piece, "current_piece"):
        drag_and_drop_piece.current_piece = "_"
    if not hasattr(drag_and_drop_piece, "is_dragging"):
        drag_and_drop_piece.is_dragging = False
    if not hasattr(drag_and_drop_piece, "start_row"):
        drag_and_drop_piece.start_row = -1
    if not hasattr(drag_and_drop_piece, "start_col"):
        drag_and_drop_piece.start_col = -1
    if not hasattr(drag_and_drop_piece, "current_piece_pos"):
        drag_and_drop_piece.current_piece_pos = p.Vector2(0, 0)
    if not hasattr(drag_and_drop_piece, "current_piece_offset"):
        drag_and_drop_piece.current_piece_offset = p.Vector2(0, 0)

    mouse_pos: p.Vector2 = p.get_mouse_position()

    col: int = int(mouse_pos.x // TILE_SIZE)
    row: int = int(mouse_pos.y // TILE_SIZE)

    if p.is_mouse_button_pressed(0) and not drag_and_drop_piece.is_dragging:
        if board_pieces[row][col] != "_":
            drag_and_drop_piece.is_dragging = True
            drag_and_drop_piece.current_piece = board_pieces[row][col]
            drag_and_drop_piece.start_row = row
            drag_and_drop_piece.start_col = col
            board_pieces[drag_and_drop_piece.start_row][
                drag_and_drop_piece.start_col
            ] = "_"

            drag_and_drop_piece.current_piece_pos = p.Vector2(
                col * TILE_SIZE + padding, row * TILE_SIZE + padding
            )
            drag_and_drop_piece.current_piece_offset.x = (
                mouse_pos.x - drag_and_drop_piece.current_piece_pos.x
            )
            drag_and_drop_piece.current_piece_offset.y = (
                mouse_pos.y - drag_and_drop_piece.current_piece_pos.y
            )

    if drag_and_drop_piece.is_dragging:
        drag_and_drop_piece.current_piece_pos.x = (
            mouse_pos.x - drag_and_drop_piece.current_piece_offset.x
        )
        drag_and_drop_piece.current_piece_pos.y = (
            mouse_pos.y - drag_and_drop_piece.current_piece_offset.y
        )

        current_texture: p.Texture = loaded_textures_array[
            drag_and_drop_piece.current_piece
        ]
        source: p.Rectangle = p.Rectangle(
            0, 0, current_texture.width, current_texture.height
        )
        dest: p.Rectangle = p.Rectangle(
            drag_and_drop_piece.current_piece_pos.x,
            drag_and_drop_piece.current_piece_pos.y,
            TILE_SIZE - padding * 2,
            TILE_SIZE - padding * 2,
        )
        origin: p.Vector2 = p.Vector2(0, 0)
        rotation: float = 0.0
        tint: p.Color = p.WHITE

        p.draw_texture_pro(current_texture, source, dest, origin, rotation, tint)

    if p.is_mouse_button_released(0) and drag_and_drop_piece.is_dragging:
        if board_pieces[row][col] == "_":
            drag_and_drop_piece.is_dragging = False
            board_pieces[row][col] = drag_and_drop_piece.current_piece


def get_legal_moves(
    current_piece: str, current_row: int, current_col: int
) -> list[tuple[int, int]]:
    legal_moves: list[tuple[int, int]] = []

    directions: list[tuple[int, int]] = [
        (1, 0),
        (-1, 0),
        (0, 1),
        (0, -1),
        (1, 1),
        (-1, -1),
        (1, -1),
        (-1, 1),
    ]

    knight_directions: list[tuple[int, int]] = [
        (2, 1),
        (2, -1),
        (-2, 1),
        (-2, -1),
        (1, 2),
        (-1, 2),
        (1, -2),
        (-1, -2),
    ]

    if current_piece == "k" or current_piece == "K":
        for dc, dr in directions:
            if (
                0 <= current_row + dr <= BOARD_SIZE
                and 0 <= current_col + dr <= BOARD_SIZE
            ):
                legal_moves.append((current_row + dr, current_col + dc))
    elif current_piece == "q" or current_piece == "Q":
        for dc, dr in directions:
            new_row: int = current_row
            new_col: int = current_col

            while 0 <= new_row <= BOARD_SIZE and 0 <= new_col <= BOARD_SIZE:
                new_row += dr
                new_col += dc

                legal_moves.append((new_row, new_col))
    elif current_piece == "r" or current_piece == "R":
        for dc, dr in directions[:4]:
            new_row: int = current_row
            new_col: int = current_col

            while 0 <= new_row <= BOARD_SIZE and 0 <= new_col <= BOARD_SIZE:
                new_row += dr
                new_col += dc

                legal_moves.append((new_row, new_col))
    elif current_piece == "n" or current_piece == "N":
        for dr, dc in knight_directions:
            new_row: int = current_row
            new_col: int = current_col

            if 0 <= new_row <= BOARD_SIZE and 0 <= new_col <= BOARD_SIZE:
                new_row += dr
                new_col += dc

                legal_moves.append((new_row, new_col))
    elif current_piece == "b" or current_piece == "B":
        for dc, dr in directions[4:]:
            new_row: int = current_row
            new_col: int = current_col

            while 0 <= new_row <= BOARD_SIZE and 0 <= new_col <= BOARD_SIZE:
                new_row += dr
                new_col += dc

                legal_moves.append((new_row, new_col))
    elif current_piece == "p":
        if current_row + 1 < BOARD_SIZE:
            legal_moves.append((current_row + 1, current_col))
    elif current_piece == "P":
        if current_row - 1 >= 0:
            legal_moves.append((current_row - 1, current_col))
    else:
        raise ValueError("Invalid piece")

    return legal_moves


def draw_legal_moves(legal_moves: list[tuple[int, int]]) -> None:
    pass


def main() -> None:
    p.init_window(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE)

    padding: int = 20

    board_pieces: list[list[str]] = [
        ["r", "n", "b", "q", "k", "b", "n", "r"],
        ["p", "p", "p", "p", "p", "p", "p", "p"],
        ["_", "_", "_", "_", "_", "_", "_", "_"],
        ["_", "_", "_", "_", "_", "_", "_", "_"],
        ["_", "_", "_", "_", "_", "_", "_", "_"],
        ["_", "_", "_", "_", "_", "_", "_", "_"],
        ["P", "P", "P", "P", "P", "P", "P", "P"],
        ["R", "N", "B", "Q", "K", "B", "N", "R"],
    ]

    loaded_textures_array: dict[str, p.Texture] = {
        "k": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_king_1x_ns.png"
        ),
        "q": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_queen_1x_ns.png"
        ),
        "r": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_rook_1x_ns.png"
        ),
        "n": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_knight_1x_ns.png"
        ),
        "b": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_bishop_1x_ns.png"
        ),
        "p": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/b_pawn_1x_ns.png"
        ),
        "K": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_king_1x_ns.png"
        ),
        "Q": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_queen_1x_ns.png"
        ),
        "R": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_rook_1x_ns.png"
        ),
        "N": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_knight_1x_ns.png"
        ),
        "B": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_bishop_1x_ns.png"
        ),
        "P": p.load_texture(
            "/home/anonymous/Downloads/programming_practice/python_files/raylib/chess/assets/w_pawn_1x_ns.png"
        ),
    }

    while not p.window_should_close():
        p.begin_drawing()
        p.clear_background(SCREEN_BACKGROUND)

        draw_board()
        draw_pieces(board_pieces, loaded_textures_array, padding)
        drag_and_drop_piece(board_pieces, loaded_textures_array, padding)

        p.end_drawing()

    for texture in loaded_textures_array.values():
        p.unload_texture(texture)

    p.close_window()


if __name__ == "__main__":
    main()
