#include "stdlib.h"
#include "raylib.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 450
#define HUD_GAP 50
#define EMPTY 0
#define CROSS 1
#define CIRCLE 2

typedef struct {
    int type;
    int x;
    int y;
} Move;

Move moves[9];
int move_count = 0;
int current_player = CROSS;

int board[3][3];

void drawTextLose() {
    DrawText("YOU LOSE!", 120, 30, 30, LIGHTGRAY);
    DrawText("PRESS R to restart!", 90, 60, 20, LIGHTGRAY);
}
void drawTextWin() {
    DrawText("YOU WIN!", 130, 30, 30, LIGHTGRAY);
    DrawText("PRESS R to restart!", 90, 60, 20, LIGHTGRAY);
}

void drawLineTic() {
    DrawRectangle(160, 80 + HUD_GAP, 2, 240, LIGHTGRAY);
    DrawRectangle(240, 80 + HUD_GAP, 2, 240, LIGHTGRAY);

    DrawRectangle(80, 160 + HUD_GAP, 240, 2, LIGHTGRAY);
    DrawRectangle(80, 240 + HUD_GAP, 240, 2, LIGHTGRAY);
}

void drawMove(int type, int x, int y) {
    if (type == CROSS) {
        DrawLine(x - 20, y - 20, x + 20, y + 20, LIGHTGRAY);
        DrawLine(x - 20, y + 20, x + 20, y - 20, LIGHTGRAY);
    } else if (type == CIRCLE) {
        DrawCircle(x, y, 20, LIGHTGRAY);
    }
}

void drawMoves() {
    for (int i = 0; i < move_count; i++) {
        Move move = moves[i];
        drawMove(move.type, move.x, move.y);
    }
}

void checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            if (board[i][0] == CROSS) {
                DisableCursor();
                drawTextWin();
            }
            else {
                DisableCursor();
                drawTextLose();
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY) {
            if (board[0][i] == CROSS) {
                drawTextWin();
                DisableCursor();
            } else {
                drawTextLose();
                DisableCursor();
            }
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        if (board[0][0] == CROSS) {
            drawTextWin();
            DisableCursor();
        } else {
            drawTextLose();
            DisableCursor();
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        if (board[0][2] == CROSS) {
            drawTextWin();
            DisableCursor();
        } else {
            drawTextLose();
            DisableCursor();
        }
    }
}
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
    SetTargetFPS(60);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = EMPTY;
        }
    }

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int x = GetMouseX();
            int y = GetMouseY();

            int cell_x = (x - 80) / 80;
            int cell_y = (y - 80 - HUD_GAP) / 80;

            if (cell_x >= 0 && cell_x < 3 && cell_y >= 0 && cell_y < 3 && board[cell_x][cell_y] == EMPTY) {
                board[cellX][cellY] = current_player;
                Move move;
                move.type = current_player;
                move.x = 80 + cellX * 80 + 40;
                move.y = 80 + cellY * 80 + 40 + HUD_GAP;
                moves[move_count] = move;
                move_count++;

                current_player = (current_player == CROSS) ? CIRCLE : CROSS;
            }
        }

        if (IsKeyPressed(KEY_R)) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    board[x][y] = EMPTY;
                }
            }
            move_count = 0;
            current_player = CROSS;
            EnableCursor();
        }

        BeginDrawing();
        ClearBackground(WHITE);

        drawLineTic();
        drawMoves();
        checkWin();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
