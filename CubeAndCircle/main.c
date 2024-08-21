#include "stdlib.h"
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5
#define ENEMY_SPEED 2
#define BULLET_SPEED 10

typedef struct {
    Vector2 position;
    Vector2 velocity;
} Entity;

Entity player;
Entity enemies[10];
Entity bullets[10];

int enemy_count = 10;
int bullet_count = 10;

void UpdatePlayer() {
    if (IsKeyDown(KEY_W)) {
        player.velocity.y = -PLAYER_SPEED;
    } else if (IsKeyDown(KEY_S)) {
        player.velocity.y = PLAYER_SPEED;
    } else {
        player.velocity.y = 0;
    }

    player.position.y += player.velocity.y;

    if (player.position.y < 0) {
        player.position.y = 0;
    }
    if (player.position.y > SCREEN_HEIGHT) {
        player.position.y = SCREEN_HEIGHT;
    }
}

void UpdateBullets() {
    for (int i = 0; i < bullet_count; i++) {
        bullets[i].position.x += BULLET_SPEED;

        if (bullets[i].position.x > SCREEN_WIDTH) {
            for (int j = i; j < bullet_count - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            bullet_count--;
            i--;
        }
    }
}

void CheckCollisions() {
    for (int j = 0; j < bullet_count; j++) {
        Rectangle bullet_rect = { bullets[j].position.x, bullets[j].position.y, 10, 10 };
        for (int i = 0; i < enemy_count; i++) {
            Rectangle enemy_rect = { enemies[i].position.x, enemies[i].position.y, 10, 10 };
            if (CheckCollisionRecs(bullet_rect, enemy_rect)) {
                for (int k = i; k < enemy_count - 1; k++) {
                    enemies[k] = enemies[k + 1];
                }
                enemy_count--;

                for (int k = j; k < bullet_count - 1; k++) {
                    bullets[k] = bullets[k + 1];
                }
                bullet_count--;

                printf("Data:\nEnemy:%d\nBullet: %d\n", enemy_count, bullet_count);
                break;
            }
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");

    player.position = (Vector2){ 50, SCREEN_HEIGHT/2 };
    player.velocity = (Vector2){ 0, 90 };
    printf("Data:\nEnemy:%d\nBullet: %d\n", enemy_count, bullet_count);

    for (int i = 0; i < 10; i++) {
        enemies[i].position.x = SCREEN_WIDTH/2 + 350;
        enemies[i].position.y = GetRandomValue(0, SCREEN_HEIGHT);
        enemies[i].velocity.y = 2;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdatePlayer();
        UpdateBullets();
        CheckCollisions();
        if (IsKeyPressed(KEY_SPACE) && bullet_count <= 10) {
            bullets[bullet_count].position = (Vector2){ player.position.x, player.position.y + 25};
            bullets[bullet_count].velocity = (Vector2){ 0, -BULLET_SPEED };
            bullet_count++;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(player.position.x, player.position.y, 50, 50, WHITE);

            for (int i = 0; i < 10; i++) {
                enemies[i].position.y += enemies[i].velocity.y;
                if (enemies[i].position.y < 0 || enemies[i].position.y > SCREEN_HEIGHT) {
                    enemies[i].velocity.y = -enemies[i].velocity.y;
                }
            }

            for (int i = 0; i < enemy_count; i++) {
                DrawCircle(enemies[i].position.x, enemies[i].position.y, 10, RED);
            }

            for (int i = 0; i < bullet_count; i++) {
                DrawCircle(bullets[i].position.x, bullets[i].position.y, 10, WHITE);
            }

            printf("Data:\nEnemy:%d\nBullet: %d\n", enemy_count, bullet_count);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
