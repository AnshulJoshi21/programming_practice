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
#define RECTANGLE_OUTLINE_THICKNESS 10.0f

// FUNCTION DECLARATIONS
void
draw_board();
void
draw_pieces(char board_pieces[BOARD_SIZE][BOARD_SIZE],
            Texture2D* loaded_textures_array,
            int* piece_to_index,
            int padding);
void
drag_and_drop_piece(char board_pieces[BOARD_SIZE][BOARD_SIZE],
                    Texture2D* loaded_textures_array,
                    int* piece_to_index,
                    int padding,
                    int* move_count);
Vector2*
get_legal_moves(char current_piece, int current_row, int current_col, int* move_count);
void
show_legal_moves(Vector2* level_moves, int move_count);

// MAIN
int
main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, SCREEN_TITLE);
    SetTargetFPS(GAME_FPS);

    int padding = 20;
    int move_count = 0;

    char board_pieces[BOARD_SIZE][BOARD_SIZE] = {
        { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' }, { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { '_', '_', '_', '_', '_', '_', '_', '_' }, { '_', '_', '_', '_', '_', '_', '_', '_' },
        { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' }, { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' },
    };

    Texture2D loaded_textures_array[PIECE_COUNT] = {
        LoadTexture("./assets/b_king_1x_ns.png"),   LoadTexture("./assets/b_queen_1x_ns.png"),
        LoadTexture("./assets/b_rook_1x_ns.png"),   LoadTexture("./assets/b_knight_1x_ns.png"),
        LoadTexture("./assets/b_bishop_1x_ns.png"), LoadTexture("./assets/b_pawn_1x_ns.png"),
        LoadTexture("./assets/w_king_1x_ns.png"),   LoadTexture("./assets/w_queen_1x_ns.png"),
        LoadTexture("./assets/w_rook_1x_ns.png"),   LoadTexture("./assets/w_knight_1x_ns.png"),
        LoadTexture("./assets/w_bishop_1x_ns.png"), LoadTexture("./assets/w_pawn_1x_ns.png"),
    };

    int piece_to_index[ASCII_SIZE];
    piece_to_index['k'] = 0;
    piece_to_index['q'] = 1;
    piece_to_index['r'] = 2;
    piece_to_index['n'] = 3;
    piece_to_index['b'] = 4;
    piece_to_index['p'] = 5;

    piece_to_index['K'] = 6;
    piece_to_index['Q'] = 7;
    piece_to_index['R'] = 8;
    piece_to_index['N'] = 9;
    piece_to_index['B'] = 10;
    piece_to_index['P'] = 11;

    while (!WindowShouldClose())
    {
        // print board
        system("clear");
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                printf(" %c ", board_pieces[i][j]);
            }
            printf("\n\n");
        }

        BeginDrawing();
        ClearBackground(SCREEN_BACKGROUND);

        draw_board();
        draw_pieces(board_pieces, loaded_textures_array, piece_to_index, padding);
        drag_and_drop_piece(
          board_pieces, loaded_textures_array, piece_to_index, padding, &move_count);

        EndDrawing();
    }

    // unload all textures
    for (int i = 0; i < PIECE_COUNT; i++)
    {
        UnloadTexture(loaded_textures_array[i]);
    }

    CloseWindow();

    return 0;
}

// FUNCTION DEFINITIONS
void
draw_board()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            Color color = (i + j) % 2 == 0 ? LIGHTGRAY : DARKGRAY;

            DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
        }
    }
}

void
draw_pieces(char board_pieces[BOARD_SIZE][BOARD_SIZE],
            Texture2D* loaded_textures_array,
            int* piece_to_index,
            int padding)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            char current_piece = board_pieces[row][col];

            if (current_piece != '_')
            {
                int index = piece_to_index[current_piece];
                Texture2D current_texture = loaded_textures_array[index];
                Rectangle source =
                  (Rectangle){ 0, 0, current_texture.width, current_texture.height };
                Rectangle dest = (Rectangle){ col * TILE_SIZE + padding,
                                              row * TILE_SIZE + padding,
                                              TILE_SIZE - padding * 2,
                                              TILE_SIZE - padding * 2 };
                Vector2 origin = (Vector2){ 0, 0 };
                float rotation = 0.0f;
                Color tint = WHITE;

                DrawTexturePro(current_texture, source, dest, origin, rotation, tint);
            }
        }
    }
}

void
drag_and_drop_piece(char board_pieces[BOARD_SIZE][BOARD_SIZE],
                    Texture2D* loaded_textures_array,
                    int* piece_to_index,
                    int padding,
                    int* move_count)
{
    static int start_row = -1;
    static int start_col = -1;
    static bool is_dragging = false;
    static char current_piece = '_';

    static Vector2 current_piece_pos = { 0 };
    static Vector2 current_piece_offset = { 0 };

    Vector2 mouse_pos = GetMousePosition();
    int row = ( int ) (mouse_pos.y / TILE_SIZE);
    int col = ( int ) (mouse_pos.x / TILE_SIZE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !is_dragging)
    {

        if (board_pieces[row][col] != '_')
        {
            is_dragging = true;
            start_row = row;
            start_col = col;
            
            current_piece = board_pieces[row][col];
            board_pieces[start_row][start_col] = '_';

            current_piece_pos = (Vector2){ col * TILE_SIZE + padding, row * TILE_SIZE + padding };
            current_piece_offset.x = mouse_pos.x - current_piece_pos.x;
            current_piece_offset.y = mouse_pos.y - current_piece_pos.y;
        }
    }

    if (is_dragging)
    {
        current_piece_pos.x = mouse_pos.x - current_piece_offset.x;
        current_piece_pos.y = mouse_pos.y - current_piece_offset.y;

        // draw piece while dragging
        int index = piece_to_index[current_piece];
        Texture2D current_texture = loaded_textures_array[index];
        Rectangle source = (Rectangle){ 0, 0, current_texture.width, current_texture.height };
        Rectangle dest = (Rectangle){ current_piece_pos.x,
                                      current_piece_pos.y,
                                      TILE_SIZE - padding * 2,
                                      TILE_SIZE - padding * 2 };
        Vector2 origin = (Vector2){ 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;

        DrawTexturePro(current_texture, source, dest, origin, rotation, tint);

        // draw outline of starting rectangle
        DrawRectangleLinesEx(
          (Rectangle){ start_row * TILE_SIZE, start_col * TILE_SIZE, TILE_SIZE, TILE_SIZE },
          RECTANGLE_OUTLINE_THICKNESS,
          RED);

        // draw legal move outlines
        // Vector2* legal_moves = get_legal_moves(current_piece, start_row, start_col, move_count);
        // show_legal_moves(legal_moves, *move_count);
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && is_dragging)
    {
        if (board_pieces[row][col] == '_')
        {
            board_pieces[row][col] = current_piece;
            is_dragging = false;
            current_piece = '_';
            start_row = -1;
            start_col = -1;
        }
    }
}

Vector2*
get_legal_moves(char current_piece, int current_row, int current_col, int* move_count)
{
    // (first 4)cardinal and (later 4)diagonal directions
    const Vector2 directions[] = { (Vector2){ 1, 0 },  (Vector2){ -1, 0 }, (Vector2){ 0, -1 },
                                   (Vector2){ 0, 1 },  (Vector2){ 1, 1 },  (Vector2){ -1, -1 },
                                   (Vector2){ 1, -1 }, (Vector2){ -1, 1 } };

    const Vector2 knight_directions[] = { (Vector2){ 2, 1 },  (Vector2){ 2, -1 },
                                          (Vector2){ -2, 1 }, (Vector2){ -2, -1 },
                                          (Vector2){ 1, 2 },  (Vector2){ -1, 2 },
                                          (Vector2){ 1, -2 }, (Vector2){ -1, -2 } };

    Vector2* moves = ( Vector2* ) malloc(BOARD_SIZE * BOARD_SIZE * sizeof(Vector2));
    if (moves == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    switch (current_piece)
    {
        case 'k':
        case 'K':
            for (int i = 0; i < 4; i++)
            {
                int new_row = current_row + directions[i].x;
                int new_col = current_col + directions[i].y;

                if (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
                    moves[(*move_count)++] = (Vector2){ new_row, new_col };
            }
            break;
        case 'q':
        case 'Q':
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                int new_row = current_row;
                int new_col = current_col;

                while (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
                {
                    new_row += directions[i].x;
                    new_col += directions[i].y;

                    moves[(*move_count)++] = (Vector2){ new_row, new_col };
                }
            }
            break;
        case 'r':
        case 'R':
            for (int i = 0; i < 4; i++)
            {
                int new_row = current_row;
                int new_col = current_col;

                while (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
                {
                    new_row += directions[i].x;
                    new_col += directions[i].y;

                    moves[(*move_count)++] = (Vector2){ new_row, new_col };
                }
            }
            break;
        case 'n':
        case 'N':
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                int new_row = current_row + knight_directions[i].x;
                int new_col = current_col + knight_directions[i].y;

                if (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
                {
                    moves[(*move_count)++] = (Vector2){ new_row, new_col };
                }
            }
            break;
        case 'b':
        case 'B':
            for (int i = 4; i < BOARD_SIZE; i++)
            {
                int new_row = current_row;
                int new_col = current_col;

                while (new_row >= 0 && new_row < BOARD_SIZE && new_col >= 0 && new_col < BOARD_SIZE)
                {
                    new_row += directions[i].x;
                    new_col += directions[i].y;

                    moves[(*move_count)++] = (Vector2){ new_row, new_col };
                }
            }
            break;
        case 'p':
            if (current_row + 1 < BOARD_SIZE)
            {
                moves[(*move_count)++] = (Vector2){ current_row + 1, current_col };
            }
            break;
        case 'P':
            if (current_row - 1 >= 0)
            {
                moves[(*move_count)++] = (Vector2){ current_row - 1, current_col };
            }
            break;
    }

    return moves;
}

// draws rectangle outlines around legal moves
void
show_legal_moves(Vector2* legal_moves, int move_count)
{
    for (int i = 0; i < move_count; i++)
    {
        int x = legal_moves[i].x * TILE_SIZE;
        int y = legal_moves[i].y * TILE_SIZE;

        DrawRectangleLinesEx(
          (Rectangle){ x, y, TILE_SIZE, TILE_SIZE }, RECTANGLE_OUTLINE_THICKNESS, BLACK);
    }
}