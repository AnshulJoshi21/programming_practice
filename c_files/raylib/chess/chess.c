#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_SIZE 800
#define SCREEN_TITLE "CHESS"
#define SCREEN_BACKGROUND RAYWHITE
#define GAME_FPS 60

#define BOARD_SIZE 8
#define TILE_SIZE (SCREEN_SIZE / BOARD_SIZE)

#define PIECE_COUNT 12
#define ASCII_SIZE 128

void
texture_arr_init(Texture2D* texture_arr)
{
    texture_arr[0] = LoadTexture("./assets/b_king_1x_ns.png");
    texture_arr[1] = LoadTexture("./assets/b_queen_1x_ns.png");
    texture_arr[2] = LoadTexture("./assets/b_rook_1x_ns.png");
    texture_arr[3] = LoadTexture("./assets/b_knight_1x_ns.png");
    texture_arr[4] = LoadTexture("./assets/b_bishop_1x_ns.png");
    texture_arr[5] = LoadTexture("./assets/b_pawn_1x_ns.png");
    texture_arr[6] = LoadTexture("./assets/w_king_1x_ns.png");
    texture_arr[7] = LoadTexture("./assets/w_queen_1x_ns.png");
    texture_arr[8] = LoadTexture("./assets/w_rook_1x_ns.png");
    texture_arr[9] = LoadTexture("./assets/w_knight_1x_ns.png");
    texture_arr[10] = LoadTexture("./assets/w_bishop_1x_ns.png");
    texture_arr[11] = LoadTexture("./assets/w_pawn_1x_ns.png");
}

void
piece_index_map_init(int* piece_index_map)
{
    // small_case is black
    piece_index_map['k'] = 0;
    piece_index_map['q'] = 1;
    piece_index_map['r'] = 2;
    piece_index_map['n'] = 3;
    piece_index_map['b'] = 4;
    piece_index_map['p'] = 5;

    // upper_case is white
    piece_index_map['K'] = 6;
    piece_index_map['Q'] = 7;
    piece_index_map['R'] = 8;
    piece_index_map['N'] = 9;
    piece_index_map['B'] = 10;
    piece_index_map['P'] = 11;
}

void
draw_board(char board[BOARD_SIZE][BOARD_SIZE],
           Texture2D* texture_arr,
           int* piece_index_map,
           int piece_padding)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            // row and col is board value from (0, 0) to (7, 7)

            // draw background tiles
            Color color = (row + col) % 2 == 0 ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);

            // draw pieces on tiles
            char current_piece = board[row][col];
            if (current_piece != '_')
            {
                int index = piece_index_map[( int ) current_piece];

                Texture2D current_texture = texture_arr[index];
                Rectangle source =
                  (Rectangle){ 0, 0, current_texture.width, current_texture.height };
                Rectangle dest = (Rectangle){ col * TILE_SIZE + piece_padding,
                                              row * TILE_SIZE + piece_padding,
                                              TILE_SIZE - piece_padding * 2,
                                              TILE_SIZE - piece_padding * 2 };
                Vector2 origin = (Vector2){ 0, 0 };
                float rotation = 0.0f;
                Color tint = WHITE;

                DrawTexturePro(current_texture, source, dest, origin, rotation, tint);
            }
        }
    }
}

typedef struct PiecePosition
{
    int x;
    int y;

} PiecePosition;

PiecePosition*
available_moves(char current_piece, int current_row, int current_col)
{
    switch (current_piece)
    {
        case 'k':
            PiecePosition black_king_moves[] = { (PiecePosition){ current_row++, current_col },
                                                 (PiecePosition){ current_row, current_col++ },
                                                 (PiecePosition){ current_row--, current_col },
                                                 (PiecePosition){ current_row, current_col-- },
                                                 (PiecePosition){ current_row++, current_col++ },
                                                 (PiecePosition){ current_row++, current_col-- },
                                                 (PiecePosition){ current_row--, current_col++ },
                                                 (PiecePosition){ current_row--, current_col-- } };
            return black_king_moves;
            break;
        case 'q':
            break;
        case 'r':
            break;
        case 'n':
            break;
        case 'b':
            break;
        case 'p':
            break;
        case 'K':
            break;
        case 'Q':
            break;
        case 'R':
            break;
        case 'N':
            break;
        case 'B':
            break;
        case 'P':
            break;
    }
}

void
drag_and_drop(char board[BOARD_SIZE][BOARD_SIZE],
              Texture2D* texture_arr,
              int* piece_index_map,
              int piece_padding)
{
    static bool is_dragging = false;
    static int start_row = -1;
    static int start_col = -1;
    static char current_piece = '_';
    static Vector2 current_piece_offset = (Vector2){ 0, 0 };
    static Vector2 current_piece_pos;

    Vector2 mouse_pos = GetMousePosition();
    // row and col is board value from (0, 0) to (7, 7)
    int row = ( int ) (mouse_pos.y / TILE_SIZE);
    int col = ( int ) (mouse_pos.x / TILE_SIZE);

    current_piece_pos =
      (Vector2){ col * TILE_SIZE + piece_padding, row * TILE_SIZE + piece_padding };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !is_dragging)
    {
        if (board[row][col] != '_')
        {
            current_piece = board[row][col];
            start_row = row;
            start_col = col;
            board[start_row][start_col] = '_';
            is_dragging = true;

            current_piece_offset.x = mouse_pos.x - current_piece_pos.x;
            current_piece_offset.y = mouse_pos.y - current_piece_pos.y;
        }
    }

    if (is_dragging)
    {
        current_piece_pos.x = mouse_pos.x - current_piece_offset.x;
        current_piece_pos.y = mouse_pos.y - current_piece_offset.y;

        // draw piece
        int index = piece_index_map[( int ) current_piece];
        Texture2D current_texture = texture_arr[index];

        Rectangle source = (Rectangle){ 0, 0, current_texture.width, current_texture.height };
        Rectangle dest = (Rectangle){ current_piece_pos.x,
                                      current_piece_pos.y,
                                      TILE_SIZE - piece_padding * 2,
                                      TILE_SIZE - piece_padding * 2 };
        Vector2 origin = (Vector2){ 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;

        DrawTexturePro(current_texture, source, dest, origin, rotation, tint);
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && is_dragging)
    {
        if (board[row][col] == '_')
        {
            is_dragging = false;
            board[row][col] = current_piece;
        }
    }
}

int
main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int piece_padding = 20;

    Texture2D texture_arr[PIECE_COUNT];
    texture_arr_init(texture_arr);

    int piece_index_map[ASCII_SIZE];
    piece_index_map_init(piece_index_map);

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' }, { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' }, { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' }
    };

    while (!WindowShouldClose())
    {
        // current board check
        system("clear");
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                printf(" %c ", board[i][j]);
            }
            printf("\n\n");
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        draw_board(board, texture_arr, piece_index_map, piece_padding);
        drag_and_drop(board, texture_arr, piece_index_map, piece_padding);

        EndDrawing();
    }

    // unload textures
    for (int i = 0; i < PIECE_COUNT; i++)
    {
        UnloadTexture(texture_arr[i]);
    }

    CloseWindow();

    return 0;
}